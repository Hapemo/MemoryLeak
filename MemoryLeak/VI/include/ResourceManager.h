#pragma once

#include "singleton.h"
#include "pch.h"
#include "Logger.h"
#include "stb_image.h"

#define LOAD_ASSET(...) ResourceManager::GetInstance()->LoadTexture(__VA_ARGS__)
#define UNLOAD_ASSET(...) ResourceManager::GetInstance()->UnloadTexture(__VA_ARGS__)
#define GET_TEXTURE_ID(...) ResourceManager::GetInstance()->GetTextureID(__VA_ARGS__)
#define GET_TEXTURE_IDS(...) ResourceManager::GetInstance()->GetTextureIDS(__VA_ARGS__)
#define GET_TEXTURE_PATH(...) ResourceManager::GetInstance()->GetTexturePath(__VA_ARGS__)
#define GET_TEXTURE_DATA(...) ResourceManager::GetInstance()->GetTextureData(__VA_ARGS__)
#define GET_RESOURCES(...) ResourceManager::GetInstance()->GetResources(__VA_ARGS__)

#define INIT_TEXTURES(...) ResourceManager::GetInstance()->InitializeTextures(__VA_ARGS__)
#define UPDATE_TEXTURES(...) ResourceManager::GetInstance()->UpdateTextures(__VA_ARGS__)

class ResourceManager : public Singleton<ResourceManager> {
public:
	struct TextureData {
		std::string	path = "";
		GLuint		id = 0;
		void* data = NULL;
		GLsizei		width = 0;
		GLsizei		height = 0;
		int			channels = 0;
	};
private:
	struct ResourceData {
		TextureData	texture;
		time_t		lastModified = time(NULL);
		int			usage = 0;
	};

	std::vector<ResourceData> mResources;
public:
	ResourceManager() {};
	~ResourceManager() {};

	ResourceManager(const ResourceManager&) = delete;
	const ResourceManager& operator=(const ResourceManager&) = delete;

	void InitializeTextures(std::string _filepath);
	std::vector<int> UpdateTextures();
	TextureData& GetTextureData(size_t _index);
	std::vector<ResourceData>& GetResources();

	void UpdateTexture(const size_t _index);
	TextureData LoadTexture(const std::string _filepath);
	void UnloadTexture(void* _data);

	float	GetAspectRatio(const GLuint _id);
	GLuint	GetTextureID(const std::string& _texture_path);
	std::vector<GLuint>	GetTextureIDS();
	std::string	GetTexturePath(GLint _id);
};
