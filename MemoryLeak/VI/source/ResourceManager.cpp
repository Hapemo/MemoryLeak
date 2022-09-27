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

#include <sys/types.h>
#include <sys/stat.h>
#define stat _stat

#include <algorithm>
#include "ResourceManager.h"

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
	stbi_set_flip_vertically_on_load(true);
	trackResource.texture.data = stbi_load(filepath, &trackResource.texture.width, &trackResource.texture.height, &trackResource.texture.channels, 0);
	trackResource.texture.path = filepath;
	if (stat(trackResource.texture.path.c_str(), &stats) == 0)
		trackResource.lastModified = stats.st_mtime;
	++trackResource.usage;
	mResources.push_back(trackResource);
	//std::cout << mResources[mResources.size() - 1].texture.path << std::endl;
	return trackResource.texture;
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
Retrieve the texture id of a specific resource.

\param const std::string& _texturePath
The filepath of the texture.

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
		if (mResources[index].texture.id == _id) return (float)(mResources[index].texture.height / mResources[index].texture.width);
	return 0.0f;
}

/*!*****************************************************************************
\brief
Free the resources in the vector.
*******************************************************************************/
void ResourceManager::FreeResources() {
	mResources.clear();
}
