#include "Graphics/SpriteManager.h"
#include "ResourceManager.h"
#include "PerformanceVisualiser.h"
#include "Logger.h"

SpriteManager::SpriteManager()
{
	glEnable(GL_TEXTURE_2D);
}

void SpriteManager::SetColor(const Entity& e, const Color& clr)
{
	SetColor(e, clr.r, clr.g, clr.b, clr.a);
}

void SpriteManager::SetColor(const Entity& e, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	e.GetComponent<Sprite>().color = { r, g, b, a };
}

void SpriteManager::SetSprite(const Entity& e, SPRITE sprite)
{
	e.GetComponent<Sprite>().sprite = sprite;
}

void SpriteManager::SetTexture(const Entity& e, const std::string& texture_path)
{
	e.GetComponent<Sprite>().texture = GET_TEXTURE_ID(texture_path);
}

void SpriteManager::InitializeTexture(ResourceManager::TextureData& texData)
{
	if (!texData.data) return;

	glCreateTextures(GL_TEXTURE_2D, 1, &texData.id);

	if (texData.channels == 3)
	{
		glTextureStorage2D(texData.id, 1, GL_RGB8, texData.width, texData.height);
		glTextureSubImage2D(texData.id, 0, 0, 0, texData.width, texData.height, GL_RGB, GL_UNSIGNED_BYTE, texData.data);
	}
	else if (texData.channels == 4)
	{
		glTextureStorage2D(texData.id, 1, GL_RGBA8, texData.width, texData.height);
		glTextureSubImage2D(texData.id, 0, 0, 0, texData.width, texData.height, GL_RGBA, GL_UNSIGNED_BYTE, texData.data);
	}

	UNLOAD_ASSET(texData.data);
}
