/*!*****************************************************************************
\file ResourceManager.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 26-09-2022
\brief
This file contains the function definition of the class ResourceManager.
The ResourceManager class manages the resources, their data and usage.
*******************************************************************************/

#pragma once

#include "singleton.h"
#include "pch.h"
#include "Logger.h"
#include "stb_image.h"

#define LOAD_ASSET(...) ResourceManager::GetInstance()->LoadTexture(__VA_ARGS__)
#define UNLOAD_ASSET(...) ResourceManager::GetInstance()->UnloadTexture(__VA_ARGS__)

#define GET_TEXTURE_ID(...) ResourceManager::GetInstance()->GetTextureID(__VA_ARGS__)
#define GET_TEXTURE_IDS(...) ResourceManager::GetInstance()->GetTextureIDs(__VA_ARGS__)
#define GET_TEXTURE_PATH(...) ResourceManager::GetInstance()->GetTexturePath(__VA_ARGS__)
#define GET_TEXTURE_DATA(...) ResourceManager::GetInstance()->GetTextureData(__VA_ARGS__)
#define GET_RESOURCES(...) ResourceManager::GetInstance()->GetResources(__VA_ARGS__)

#define LOAD_TEXTURES(...) ResourceManager::GetInstance()->LoadTextures(__VA_ARGS__)
#define UPDATE_TEXTURES(...) ResourceManager::GetInstance()->UpdateTextures(__VA_ARGS__)
#define FREE_RESOURCES(...) ResourceManager::GetInstance()->FreeResources(__VA_ARGS__)

class ResourceManager : public Singleton<ResourceManager> {
public:
	/*!*****************************************************************************
	\brief
	Struct to store all the texture data.
	*******************************************************************************/
	struct TextureData {
		std::string	path = "";
		GLuint		id = 0;
		void* data = NULL;
		GLsizei		width = 0;
		GLsizei		height = 0;
		int			channels = 0;
	};
private:
	/*!*****************************************************************************
	\brief
	Struct to store all the data of a resource.
	*******************************************************************************/
	struct ResourceData {
		TextureData	texture;
		time_t		lastModified = time(NULL);
		int			usage = 0;
	};

	/*!*****************************************************************************
	\brief
	Member vector to store all the loaded resources data.
	*******************************************************************************/
	std::vector<ResourceData> mResources;
public:
	/*!*****************************************************************************
	\brief
	Constructor for ResourceManager.
	*******************************************************************************/
	ResourceManager() {};

	/*!*****************************************************************************
	\brief
	Destructor for ResourceManager.
	*******************************************************************************/
	~ResourceManager() {};

	// Delete the copy constructor
	ResourceManager(const ResourceManager&) = delete;
	const ResourceManager& operator=(const ResourceManager&) = delete;

	/*!*****************************************************************************
	\brief
	Loads all the textures in the specified filepath.

	\param std::string _filepath
	The filepath in string.
	*******************************************************************************/
	void LoadTextures(std::string _filepath);


	/*!*****************************************************************************
	\brief
	Check if files have changed/been updated by checking the last updated time. If
	timing is different, then reload the texture. Also check for if the filename
	doesn't exist, means the file is deleted, which the function will then remove
	the texture from the mResources vector.

	\return
	Returns a vector of resource id that has been updated.
	*******************************************************************************/
	std::vector<int> UpdateTextures();

	/*!*****************************************************************************
	\brief
	Free the resources in the vector.
	*******************************************************************************/
	void FreeResources();

	/*!*****************************************************************************
	\brief
	Update a specific texture and it's data by calling the stbi load functon.

	\param const size_t _index
	The index of the texture to be updated.
	*******************************************************************************/
	void UpdateTexture(const size_t _index);

	/*!*****************************************************************************
	\brief
	Load a specific texture by calling the stbi load function and stores it's data
	in a ResourceData struct. Stores the resource in a member vector mResources.

	\param const std::string _filepath
	The filepath of the texture to be loaded.
	*******************************************************************************/
	TextureData LoadTexture(const std::string _filepath);

	/*!*****************************************************************************
	\brief
	Unload a specific texture data by calling stbi image free.

	\param void* _data
	The void* pointing to the data of the texture to be deleted.
	*******************************************************************************/
	void UnloadTexture(void* _data);

	/*!*****************************************************************************
	\brief
	Retrieve the texture data of a specific texture.

	\param size_t _index
	The index of the texture.

	\return
	Returns the data of the texture in the member vector mResources.
	*******************************************************************************/
	TextureData& GetTextureData(size_t _index) { return mResources[_index].texture; }

	/*!*****************************************************************************
	\brief
	Retrieve the loaded resources stored in the member vector mResources.

	\return
	Returns the member vector mResources.
	*******************************************************************************/
	std::vector<ResourceData>& GetResources() { return mResources; }

	/*!*****************************************************************************
	\brief
	Gets the aspect ratio of a specific texture.

	\param const GLuint _id
	The id of the texture.

	\return
	Returns the aspect ratio of the texture in float.
	*******************************************************************************/
	float GetAspectRatio(const GLuint _id);

	/*!*****************************************************************************
	\brief
	Retrieve the texture id of a specific resource.

	\param const std::string& _texturePath
	The filepath of the texture.

	\param GLuint
	The id of the texture.
	*******************************************************************************/
	GLuint GetTextureID(const std::string& _texture_path);

	/*!*****************************************************************************
	\brief
	Retrieve all the texture ids of the resources.

	\return
	Returns a vector of the ids in GLuint* of all the texture.
	*******************************************************************************/
	std::vector<GLuint*> GetTextureIDs();

	/*!*****************************************************************************
	\brief
	Retrieve the texture path of a specific resource.

	\param GLint _id
	The id of the texture.

	\return
	Returns the path of the texture in string.
	*******************************************************************************/
	std::string	GetTexturePath(GLint _id);
};
