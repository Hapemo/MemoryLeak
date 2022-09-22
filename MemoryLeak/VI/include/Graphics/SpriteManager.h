#pragma once
#include "ECS_components.h"
#include <ECS_systems.h>
#include "ECS_items.h"
#include "pch.h"
#include "SpriteVariable.h"
#include "ResourceManager.h"


class SpriteManager : public System
{
public:
	SpriteManager();

	Color	GetColor			(const Entity& e) { return e.GetComponent<Sprite>().color; }
	void	SetColor			(const Entity& e, const Color& clr);
	void	SetColor			(const Entity& e, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255);

	SPRITE	GetSprite			(const Entity& e) { return e.GetComponent<Sprite>().sprite; }
	void	SetSprite			(const Entity& e, SPRITE sprite);

	GLuint	GetTexture			(const Entity& e) { return e.GetComponent<Sprite>().texture; }
	void	SetTexture			(const Entity& e, const std::string& texture_path);

	//GLuint	GetAspectRatio		(const Entity& e) { return e.GetComponent<Sprite>().texture; }
	
	GLuint	GetTextureID		(const std::string& texture_path) { return GET_TEXTURE_ID(texture_path); }
	std::string	GetTexturePath	(GLint id) { return GET_TEXTURE_PATH(id); }

	void	InitializeTexture	(ResourceManager::TextureData& texData);
private:
};