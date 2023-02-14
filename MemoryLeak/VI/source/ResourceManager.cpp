/*!*****************************************************************************
\file ResourceManager.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 26-09-2022
\brief
This file contains the class ResourceManager and it's functions declaration.
The ResourceManager class manages the resources, their data and usage.
*******************************************************************************/

#pragma once
#define MultiThread 1 // 1 to multi thread, 0 to not multi thread.

#include <sys/types.h>
#include <sys/stat.h>
#define stat _stat
#include <chrono>
#include <algorithm>
#include "ResourceManager.h"
#include "Serialization.h"
#include "ECSManager.h"

/*!*****************************************************************************
\brief
Loads all the textures in the specified filepath.

\param std::string _filepath
The filepath in string.
*******************************************************************************/
void ResourceManager::LoadTextures(std::string _filepath) {
	const std::filesystem::path tex_dir{ "..\\resources\\Textures\\" + _filepath };
	for (const std::filesystem::path& entry : std::filesystem::directory_iterator(tex_dir)) {
		std::string str = entry.string();
		LoadTexture(str);
	}
}

/*!*****************************************************************************
\brief
Load a specific texture by calling the stbi load function and stores it's data
in a ResourceData struct. Stores the resource in a member vector mResources.

\param const std::string _filepath
The filepath of the texture to be loaded.
*******************************************************************************/
ResourceManager::TextureData ResourceManager::LoadTexture(const std::string _filepath)
{
	struct stat stats;
	ResourceData trackResource;
	const char* filepath = _filepath.c_str();
	//LOG_DEBUG("loading texture:" + _filepath);
	stbi_set_flip_vertically_on_load(true);
	trackResource.texture.data = stbi_load(filepath, &trackResource.texture.width, &trackResource.texture.height, &trackResource.texture.channels, 0);
	trackResource.texture.path = filepath;
	if (stat(trackResource.texture.path.c_str(), &stats) == 0)
		trackResource.lastModified = stats.st_mtime;
	++trackResource.usage;
	mResources.push_back(trackResource);
	spriteManager->InitializeTexture(mResources.back().texture);
	//std::cout << mResources[mResources.size() - 1].texture.path << std::endl;
	return trackResource.texture;
}

ResourceManager::TextureData ResourceManager::LoadTextureWithoutOpenGL(const std::string _filepath) {
	struct stat stats;
	ResourceData trackResource;
	stbi_set_flip_vertically_on_load(true);
	trackResource.texture.data = stbi_load(_filepath.c_str(), &trackResource.texture.width, &trackResource.texture.height, &trackResource.texture.channels, 0);
#if MultiThread
	myLock.lock();
#endif
	trackResource.texture.path = _filepath.c_str();
	if (stat(trackResource.texture.path.c_str(), &stats) == 0)
		trackResource.lastModified = stats.st_mtime;
	++trackResource.usage;
	mResources.push_back(trackResource);
	if (LoadedAll) mReloadedResources.push_back(trackResource);
#if MultiThread
	myLock.unlock();
#endif
	return trackResource.texture;
}

void ResourceManager::InitialiseAllTextures() {
	for (auto& resource : mResources)
		spriteManager->InitializeTexture(resource.texture);
}

void ResourceManager::InitialiseReloadedTextures() {
	for (auto& resource : mReloadedResources)
		spriteManager->InitializeTexture(resource.texture);
	mReloadedResources.clear();
}

/*!*****************************************************************************
\brief
Update a specific texture and it's data by calling the stbi load functon.

\param const size_t _index
The index of the texture to be updated.
*******************************************************************************/
void ResourceManager::UpdateTexture(const size_t _index)
{
	const char* filepath = mResources[_index].texture.path.c_str();
	stbi_set_flip_vertically_on_load(true);
	mResources[_index].texture.data = stbi_load(filepath, &mResources[_index].texture.width, &mResources[_index].texture.height, &mResources[_index].texture.channels, 0);
	//std::cout << mResources[_index].texture.path << std::endl;
}

/*!*****************************************************************************
\brief
Check if files have changed/been updated by checking the last updated time. If
timing is different, then reload the texture. Also check for if the filename
doesn't exist, means the file is deleted, which the function will then remove
the texture from the mResources vector.

\return
Returns a vector of resource id that has been updated.
*******************************************************************************/
std::vector<int> ResourceManager::UpdateTextures() {
	std::vector<int> updatedTextures;
	struct stat stats;
	for (size_t index = 0; index < mResources.size(); ++index) {
		if (stat(mResources[index].texture.path.c_str(), &stats) == 0) {
			std::ifstream fopen(mResources[index].texture.path);
			if (!fopen.is_open()) {
				fopen.close();
				mResources.erase(mResources.begin() + index);
				continue;
			}
			time_t lastModifiedTime = stats.st_mtime;
			if (lastModifiedTime != mResources[index].lastModified) {
				//std::cout << "unloading " << mResources[index].texture.path << std::endl;
				UpdateTexture(index);
				mResources[index].lastModified = lastModifiedTime;
				updatedTextures.push_back((int)index);
			}
			fopen.close();
		}
	}
	return updatedTextures;
}

/*!*****************************************************************************
\brief
Retrieve the texture id of a specific resource. Path starts from "..\\resources\\",

\param const std::string& _texturePath
The filepath of the texture, starting from resources folder's directory

\return
Returns the id of the texture in GLuint.
*******************************************************************************/
GLuint ResourceManager::GetTextureID(const std::string& _texturePath) {
	for (size_t index = 0; index < mResources.size(); ++index)
		if (mResources[index].texture.path == "..\\resources\\" + _texturePath) return mResources[index].texture.id;
	return 0;
}

/*!*****************************************************************************
\brief
Retrieve the texture path of a specific resource.

\param GLint _id
The id of the texture.

\return
Returns the path of the texture in string.
*******************************************************************************/
std::string	ResourceManager::GetTexturePath(GLint _id) {
	std::string path = "";
	for (size_t index = 0; index < mResources.size(); ++index)
		if ((GLint)mResources[index].texture.id == (GLint)_id) {
			path = mResources[index].texture.path;
			path = path.substr(13);
		}
	return path;
}

/*!*****************************************************************************
\brief
Retrieve all the texture ids of the resources.

\return
Returns a vector of the ids in GLuint* of all the texture.
*******************************************************************************/
std::vector<GLuint*> ResourceManager::GetTextureIDs() {
	std::vector<GLuint*> result;
	for (size_t index = 0; index < mResources.size(); ++index)
		result.push_back(&mResources[index].texture.id);
	return result;
}

/*!*****************************************************************************
\brief
Unload a specific texture data by calling stbi image free.

\param void* _data
The void* pointing to the data of the texture to be deleted.
*******************************************************************************/
void ResourceManager::UnloadTexture(void* _data) {
	stbi_image_free(_data);
}

/*!*****************************************************************************
\brief
Gets the aspect ratio of a specific texture.

\param const GLuint _id
The id of the texture.

\return
Returns the aspect ratio of the texture in float.
*******************************************************************************/
float ResourceManager::GetAspectRatio(const GLuint _id) {
	for (size_t index = 0; index < mResources.size(); ++index)
		if (mResources[index].texture.id == _id) return (float)((float)mResources[index].texture.height / (float)mResources[index].texture.width);
	return 0.0f;
}

/*!*****************************************************************************
\brief
Free the resources in the vector.
*******************************************************************************/
//void ResourceManager::FreeResources() {
//	mResources.clear();
//}

// GUID is made with the following format
// GUID is firstly made with total time stamp
// Then replaced the first byte with resource type
// Then replace the second byte with instance of guidCounter

ResourceManager::GUID ResourceManager::GUIDGenerator(std::filesystem::path const& _path) {
	E_RESOURCETYPE resourceType{ CheckResourceType(_path) };
	//ASSERT(resourceType == E_RESOURCETYPE::error, "Unable to determine resource type");
	if (resourceType == E_RESOURCETYPE::error)
		return 0;
	std::chrono::time_point today = std::chrono::system_clock::now();
	std::chrono::duration duration = today.time_since_epoch();
	GUID guid = *static_cast<GUID*>(static_cast<void*>(&duration));
	unsigned char* guidPtr = static_cast<unsigned char*>(static_cast<void*>(&guid));
	*guidPtr = static_cast<unsigned char>(resourceType);
	*(guidPtr + 1) = ++guidCounter; // guidCounter will automatically reset to 0 when overflow, this is intended.
	return guid;
}

bool ResourceManager::FileExist(std::string const& _fileName) {
	std::ifstream file{ _fileName.c_str() };
	return file.good();
}

ResourceManager::GUID ResourceManager::ReadGUIDFromFile(std::string const& _metaPath) {
	std::ifstream file{ _metaPath };
	char buffer [sizeof(GUID)];
	file.read(buffer, sizeof(GUID));
	file.close();
	return *(static_cast<GUID*>(static_cast<void*>(buffer)));
}

void ResourceManager::LoadAllResources() {
	mResources.reserve(1000); // Predict there is going to be at most 1000 textures, for multi threading

	LoadAllResources(std::filesystem::path{resourceFolder});

//#if MultiThread
	for (std::thread& t : mResourceLoadingThreads)
		t.join();
	mResourceLoadingThreads.clear();
//#endif

	// Initialise resources that haven't been initialised before
	if (!LoadedAll) InitialiseAllTextures();
	else InitialiseReloadedTextures();

	LoadedAll = true;
}

void ResourceManager::LoadResource(std::filesystem::path const& entry) {
	// Skip any meta files
	const std::string fileName{ entry.filename().string() };
	if (fileName.find(".meta") != std::string::npos) return;

	// Check for existing meta file
	std::string metaPath{ entry.string() + ".meta" };
	GUID guid{};
	if (FileExist(metaPath))// If exist, get it's guid
		guid = ReadGUIDFromFile(metaPath);
	else {									// else make one and get it's guid
		guid = GUIDGenerator(entry);
		std::ofstream newMetaFile(metaPath);
		char* data = static_cast<char*>(static_cast<void*>(&guid));
		newMetaFile.write(data, sizeof(guid));
		newMetaFile.close();
	}

	// Skip subsequent duplicate resources
	if (LoadedAll) {
		bool fileLoaded{ false };
		for (auto& [_guid, _fileName] : mAllFilePaths) {
			if (_fileName == entry.string()) {
				fileLoaded = true;
				break;
			}
		}

		if (fileLoaded) return;
		LOG_INFO("RESOURCE MANAGER: loading new resources midway through editor: " + entry.string());
	}

	// Open and store resources, then linking them to their guid
	E_RESOURCETYPE resourceType{ CheckResourceType(entry) };
	//ASSERT(resourceType == E_RESOURCETYPE::error, "Unable to determine resource type");
	if (resourceType == E_RESOURCETYPE::error || resourceType == E_RESOURCETYPE::prefab) return;

	void* dataPointer{};

	switch (resourceType) {
	case E_RESOURCETYPE::texture:
		dataPointer = new TextureData;
		std::cout << guid << '\n';
//#if MultiThread
		*(static_cast<TextureData*>(dataPointer)) = LoadTextureWithoutOpenGL(entry.string());
		//LoadTextureWithoutOpenGL(entry.string());
//#else
		//*(static_cast<TextureData*>(dataPointer)) = LoadTexture(entry.string());
//#endif
		break;

	case E_RESOURCETYPE::audio:
		// entry.string() gives the path of the file. eg. "..\\resources\\Audio\\SHOOT1.wav"
		/*dataPointer = static_cast<void*>*/
		myLock.lock();
		(audioManager->LoadAudio(entry));
		myLock.unlock();
		break;

	case E_RESOURCETYPE::script:

		break;

	case E_RESOURCETYPE::scene:
		//dataPointer = new SceneData;
		//*(static_cast<SceneData*>(dataPointer)) = SerializationManager::LoadSceneData(entry.string());
		break;

	case E_RESOURCETYPE::gamestateEntities:
		//dataPointer = new GameStateData;
		//*(static_cast<GameStateData*>(dataPointer)) = SerializationManager::LoadGameStateData(entry.string());
		break;

	case E_RESOURCETYPE::dialogue:

		break;
	case E_RESOURCETYPE::font:

		break;
	case E_RESOURCETYPE::prefab:

		break;
	}
	(void)dataPointer;
	myLock.lock();
	mAllResources.insert({ guid, dataPointer });
	mAllFilePaths.insert({ guid, entry.string() });
	myLock.unlock();
	//std::cout << "GUID: " << guid << " | File: " << entry.string() << '\n';
}

void ResourceManager::LoadAllResources(std::filesystem::path const& _folder) {
	for (const std::filesystem::path& entry : std::filesystem::directory_iterator(_folder)) {
		// If it's a folder, go into it
		if (std::filesystem::is_directory(entry)) {
			LoadAllResources(entry);
			continue;
		}
#if MultiThread
		mResourceLoadingThreads.push_back(std::thread([this,entry] {LoadResource(entry); }));
#else
		LoadResource(entry);
#endif
	}
	
}

void ResourceManager::UnloadAllResources() {
	for (auto& [guid, dataPtr] : mAllResources) {
		E_RESOURCETYPE resourceType{ static_cast<E_RESOURCETYPE>(guid) };

		switch (resourceType) {
		case E_RESOURCETYPE::texture:
			delete static_cast<TextureData*>(dataPtr);
			break;

		case E_RESOURCETYPE::audio:
			//static_cast<FMOD::Sound*>(dataPtr)->release();
			break;

		case E_RESOURCETYPE::script:

			break;

		case E_RESOURCETYPE::scene: {
			//SceneData* data = static_cast<SceneData*>(dataPtr);
			//if (!data) break;
			//ECS::DestroySomeEntites(data->mEntities);
			//delete data;
			break;
		}

		case E_RESOURCETYPE::gamestateEntities: {
			//GameStateData* data = static_cast<GameStateData*>(dataPtr);
			//if (!data) break;
			//ECS::DestroySomeEntites(data->mEntities);
			//delete data;
			break;
		}

		case E_RESOURCETYPE::dialogue:

			break;
		case E_RESOURCETYPE::font:

			break;
		case E_RESOURCETYPE::prefab:

			break;
		}
	}
	mAllResources.clear();
	mAllFilePaths.clear();
}

void ResourceManager::CheckWrongAudioFile(std::filesystem::path const& _path) {
	if (_path.string().find(".wav") != std::string::npos || 
			_path.string().find(".mp3") != std::string::npos) return; // Nothing wrong with wav file

	// If something wrong with audio file read in, code under here
	LOG_ERROR("Attempted to load in invalid audio file: " + _path.string());
}

void ResourceManager::CheckWrongTextureFile(std::filesystem::path const& _path) {
	if (_path.string().find(".png") != std::string::npos ||
			_path.string().find(".jpg") != std::string::npos) return; // Nothing wrong with tex file

	// If something wrong with audio file read in, code under here
	LOG_ERROR("Attempted to load in invalid texture file: " + _path.string());
}

ResourceManager::E_RESOURCETYPE ResourceManager::CheckResourceType(std::filesystem::path const& _path) {
	if (_path.string().find("\\Audio\\") != std::string::npos) {
		CheckWrongAudioFile(_path);
		return E_RESOURCETYPE::audio;
	}
	else if (_path.string().find("\\Dialogs\\") != std::string::npos) return E_RESOURCETYPE::dialogue;
	else if (_path.string().find("\\Scene\\") != std::string::npos) return E_RESOURCETYPE::scene;
	else if (_path.string().find("\\Textures\\") != std::string::npos) {
		CheckWrongTextureFile(_path);
		return E_RESOURCETYPE::texture;
	}
	else if (_path.string().find("\\Scripts\\") != std::string::npos) return E_RESOURCETYPE::script;
	else if (_path.string().find("\\GameStates\\") != std::string::npos) return E_RESOURCETYPE::gamestateEntities;
	else if (_path.string().find("\\Fonts\\") != std::string::npos) return E_RESOURCETYPE::font;
	else if (_path.string().find("\\Prefabs\\") != std::string::npos) return E_RESOURCETYPE::prefab;

	LOG_WARN("Attempted to load unknown resource into resource manager. Resource: " + _path.string());
	return E_RESOURCETYPE::error;
}

std::string ResourceManager::GetFilePath(GUID const& _guid) {
	std::string filePath{};
	try {
		filePath = mAllFilePaths.at(_guid);
	} catch (std::out_of_range) {
		LOG_WARN("Attempting to get non-existing filepath from resource manager, using guid: " + std::to_string(_guid));
	}

	return filePath;
}

typename ResourceManager::GUID ResourceManager::GetFileGUID(std::string const& _path) const {
	std::string actualPath{ resourceFolder.string() + "\\" + _path};
	for (auto& [guid, path] : mAllFilePaths)
		if (path == actualPath) return guid;
	LOG_WARN("Unable to identify GUID value of " + _path);
	return GUID();
}


std::filesystem::path ResourceManager::FileTypePath(E_RESOURCETYPE _type) {
	std::string path = resourceFolder.string();
	switch (_type) {
	case E_RESOURCETYPE::texture:
		path += "\\Textures\\";
		break;
	case E_RESOURCETYPE::audio:
		path += "\\Audio\\";
		break;
	case E_RESOURCETYPE::script:
		path += "\\Scripts\\";
		break;
	case E_RESOURCETYPE::scene:
		path += "\\Scene\\";
		break;
	case E_RESOURCETYPE::gamestateEntities:
		path += "\\GameStates\\";
		break;
	case E_RESOURCETYPE::dialogue:
		path += "\\Dialogs\\";
		break;
	case E_RESOURCETYPE::font:
		path += "\\Fonts\\";
		break;
	case E_RESOURCETYPE::prefab:
		path += "\\Prefabs\\";
		break;
	}
	return std::filesystem::path(path);
}


//-----------------------------------------
// For Game Mode
//-----------------------------------------

void ResourceManager::LoadGameStateResources(std::filesystem::path const& _gamestatePath) {
	mResources.reserve(1000); // Predict there is going to be at most 1000 textures, for multi threading
	(void)_gamestatePath;
	mGuidList.insert({ 16679133496476929, 16683718373936641, 16693093095833857, 16679151736062977, 16747942542967041, 16679133496609025, 16679133496674817, 16679133496675073, 16671515798471169, 16692964149364481, 16683718375643137, 16683718375643393, 16692964149430273, 16683718374594305, 16665530912085249, 16682022752616961, 16747534960953345, 16741782613262593, 16747534961019393, 16683718373936897, 16679133496608769, 16679151736194561, 16679151736260353, 16671351933436161, 16669651555061249, 16747534961217281, 16747534961414401, 16747534961414657, 16747534961612289, 16747534961545985, 16669651553160193, 16689637057036545, 16683718377609985, 16691742290151425, 16669651555782401, 16679133496542721, 16683718378134785, 16665530912609793, 16747534961085185, 16747534961085697, 16747534961085441, 16665530913265409, 16683718374068481, 16669651554405633, 16683718374068737, 16669651553094145, 16669651553094401, 16671351934878465, 16671351935337729, 16691742289560577, 16691742289626369, 16747534965741825, 16691742289757953, 16747534962792193, 16679133496411137, 16691742290151681, 16683718377675777, 16665530918443777, 16747534961019137, 16665530935553025, 16665530919492609, 16665530921918209, 16669651557945601, 16665530923622657, 16693623342367745, 16669651558011905, 16665530926375937, 16747568241443073, 16665530928801537, 16665530927687169, 16665530933127681, 16665530934438657, 16691998620975361, 16671351934157313, 16689398516876801, 16665530915887361, 14757395258960776193, 14757395258961366273, 14757395258962677505, 14757395258963661057, 16747534961612033, 14757395258965496833, 14757395258966480385, 16671351935075329, 14757395258967641089, 16747534965873665, 16747534966070529, 16747534966071297, 16747534965610497, 16747534966071553, 16747534966401025, 16747534966401537, 16747534966203137, 16683718373739265, 16747534966334465, 16747534966334721, 16691742290217473, 16691742290217729, 16691998647714561, 16691998649680897, 16691998651122945, 16691998653810433, 16665530942042369, 16665530921197057, 16689398516547841, 16679133496542977, 16665530922901505, 16669651557945857, 16693623342499073, 16728197200552705, 16665530925392641, 16728197198650881, 16728197199437825, 16747534961085953, 16720718956069633, 16720718956528641, 16665530930243585 });

	// mGuidList = /*Serialisation manager's function*/; TODO

	SelectiveLoadAllResources(resourceFolder);

	for (std::thread& t : mResourceLoadingThreads)
		t.join();
	
	InitialiseAllTextures();
	
	mResourceLoadingThreads.clear();
	mGuidList.clear();
}

void ResourceManager::SelectiveLoadAllResources(std::filesystem::path const& _folderDirectory) {
	for (const std::filesystem::path& entry : std::filesystem::directory_iterator(_folderDirectory)) {
		// If it's a folder, go into it
		if (std::filesystem::is_directory(entry)) {
			SelectiveLoadAllResources(entry);
			continue;
		}
#if MultiThread
		mResourceLoadingThreads.push_back(std::thread([this, entry] {SelectiveLoadResource(entry); }));
#else
		LoadResource(entry);
#endif
	}
}

void ResourceManager::SelectiveLoadResource(std::filesystem::path const& entry) {
	// Skip any non-meta files
	const std::string fileName{ entry.filename().string() };
	if (fileName.find(".meta") == std::string::npos) return;

	// Check meta file to know if resource should be loaded
	bool approvedGUID{ false };
	GUID guid = ReadGUIDFromFile(entry.string());
	for (GUID neededGUID : mGuidList)
		if (guid == neededGUID) {
			approvedGUID = true;
			break;
		}
	if (!approvedGUID) return;


	// Get resource path
	uint64_t fileNameLength{ entry.string().length() - std::strlen(".meta") };
	const std::filesystem::path resourcePath{ entry.string().substr(0, fileNameLength) };

	// Open and store resources, then linking them to their guid
	E_RESOURCETYPE resourceType{ CheckResourceType(resourcePath) };
	if (resourceType == E_RESOURCETYPE::error || resourceType == E_RESOURCETYPE::prefab) return;

	void* dataPointer{};

	switch (resourceType) {
	case E_RESOURCETYPE::texture:
		dataPointer = new TextureData;
		*(static_cast<TextureData*>(dataPointer)) = LoadTextureWithoutOpenGL(resourcePath.string());
		break;

	case E_RESOURCETYPE::audio:
		myLock.lock();
		(audioManager->LoadAudio(resourcePath));
		myLock.unlock();
		break;

	case E_RESOURCETYPE::script:
		break;

	case E_RESOURCETYPE::scene:
		break;

	case E_RESOURCETYPE::gamestateEntities:
		break;

	case E_RESOURCETYPE::dialogue:
		break;

	case E_RESOURCETYPE::font:
		break;

	case E_RESOURCETYPE::prefab:
		break;
	}
	(void)dataPointer;
	myLock.lock();
	mAllResources.insert({ guid, dataPointer });
	mAllFilePaths.insert({ guid, resourcePath.string() });
	myLock.unlock();
	//std::cout << "GUID: " << guid << " | File: " << entry.string() << '\n';
}
