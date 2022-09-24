#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#define stat _stat

#include <algorithm>
#include "ResourceManager.h"

void ResourceManager::InitializeTextures(std::string _filepath) {
	const std::filesystem::path tex_dir{ "..\\resources\\Textures\\" + _filepath };
	for (const std::filesystem::path& entry : std::filesystem::directory_iterator(tex_dir))
	{
		int height, width, channels;
		std::string str = entry.string();
		size_t pos = str.find_first_of('\\') + 1;
		LoadTexture(str);
	}
}

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

void ResourceManager::UpdateTexture(const size_t _index)
{
	const char* filepath = mResources[_index].texture.path.c_str();
	stbi_set_flip_vertically_on_load(true);
	mResources[_index].texture.data = stbi_load(filepath, &mResources[_index].texture.width, &mResources[_index].texture.height, &mResources[_index].texture.channels, 0);
	std::cout << mResources[_index].texture.path << std::endl;
}

std::vector<ResourceManager::ResourceData>& ResourceManager::GetResources() {
	return mResources;
}

ResourceManager::TextureData& ResourceManager::GetTextureData(size_t _index) {
	return mResources[_index].texture;
}

/*
	check if files have changed/been updated
	> check last updated time
	> container that stores the previous time
		> if different, then unload and reload the image to the same pointer
	> check if filename doesnt exist means file is deleted
		> unload image
*/

std::vector<int> ResourceManager::UpdateTextures() {
	std::vector<int> updatedTextures;
	struct stat stats;
	//std::cout << mResources.size() << std::endl;
	for (size_t index = 0; index < mResources.size(); ++index) {
		if (stat(mResources[index].texture.path.c_str(), &stats) == 0) {
			std::ifstream fopen(mResources[index].texture.path);
			if (!fopen.is_open()) {
				fopen.close();
				mResources.erase(mResources.begin() + index);
				continue;
			}
			time_t lastModifiedTime = stats.st_mtime;
			//if(index == 0) std::cout << mResources[index].texture.path << " last updated time: " << lastModifiedTime << " | stored last updated: " << mResources[index].lastModified << std::endl;
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

GLuint ResourceManager::GetTextureID(const std::string& _texturePath) {
	for (size_t index = 0; index < mResources.size(); ++index)
		if (mResources[index].texture.path == "..\\resources\\" + _texturePath) return mResources[index].texture.id;
	return 0;
}

std::string	ResourceManager::GetTexturePath(GLint _id) {
	for (size_t index = 0; index < mResources.size(); ++index)
		if (mResources[index].texture.id == _id) return mResources[index].texture.path;
	return "";
}

void ResourceManager::UnloadTexture(void* _data) {
	stbi_image_free(_data);
}

float ResourceManager::GetAspectRatio(const GLuint _id) {
	for (size_t index = 0; index < mResources.size(); ++index)
		if (mResources[index].texture.id == _id) return (mResources[index].texture.height / mResources[index].texture.width);
}
