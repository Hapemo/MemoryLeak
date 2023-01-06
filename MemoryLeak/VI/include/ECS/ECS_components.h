/*!*****************************************************************************
\file ECS_components.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
This file contains all the structs of components used in ECS. 
ComponentType starts from 0.
*******************************************************************************/
#pragma once
#include <glm/glm.hpp>
#include "vec2.h"
#include "Graphics/SpriteVariable.h"
#include "AudioVariable.h"
#include "TagVariable.h"

class Prefab;

/*!*****************************************************************************
\brief
Struct that encapsulates general information most component will have, such as
name, tag and isActive flag
*******************************************************************************/
struct General {
	std::string name;
	TAG tag;
	SUBTAG	subtag = SUBTAG::NOSUBTAG;
	bool isActive;
	Prefab* prefab = nullptr; // Nullptr if it's not linked to any prefab
};

/*!*****************************************************************************
\brief
This component encapsulate the entity's lifetime
*******************************************************************************/
struct Lifespan {
	float lifetime; // Duration of entity's existance
	float limit; // Maximum duration of entity's existance

	//Lifespan(float _lifetime, float _limit) : lifetime(_lifetime), limit(_limit) {}
};

/*!*****************************************************************************
\brief
This component encapsulates what is needed in a Transform Component.
*******************************************************************************/
struct Transform
{
	Math::Vec2		scale;
	float			rotation;
	Math::Vec2		translation;
};

/*!*****************************************************************************
\brief
This component encapsulates what is needed in a Sprite Component. 
The sprite variable describes the type of sprite that should be rendered.
The texture variable contains the texture id of the texture to be rendered.
The layer variable contains which layer the sprite is to be rendered in.
*******************************************************************************/
struct Sprite
{
	Color color;
	SPRITE sprite;
	GLuint texture = 0;
	int layer = 0;
};


/*!*****************************************************************************
\brief
This component encapsulates what is needed in an Animation component. 
The images variable stores the texture id of images in the animation.
The currentImageIndex contains the index of the texture in images vector to be
used.
*******************************************************************************/
struct Animation
{
	std::vector<GLuint> images;			//save, edit, see
	std::vector<int> frameCount;		//save, edit, see
	std::vector<float> timePerImage;	//save, edit, see
	int currentImageIndex = 0;			//save, edit, see
	float timeToImageSwap;				//to be deleted
};

/*!*****************************************************************************
\brief
This component encapsulates what is needed in a SheetAnimation. Which is 
animated using spritesheets.
The frameCount variable stores the number of frames in a sprite.
The currFrameIndex stores the index of the frame to be used.
*******************************************************************************/
struct SheetAnimation
{
	short frameCount = 1;
	short currFrameIndex = 0;
	float timePerFrame = 1.f;
	float timeToFrameSwap = 0.f;
};

/*!*****************************************************************************
\brief 
This component encapsulates information regarding dynamic movement of an entity.
The gravityEnabled variable tells the physics manager if the entity should be
 affected by gravity
The mass variable contains how heavy the object is
The speed variable contains how fast the object moves
The moveDirection variable contains the direction the object is moving in terms
 of radian rotations
The forces variable contains the net force acting on the object at frametime
The velocity variable contains the current velocity of the object at frametime
The renderFlag variable contains the flag variable telling the render manager
 whether to render the velocity vector
*******************************************************************************/
struct Physics2D {
	bool gravityEnabled = false;
	float mass = 1.f,
		  speed = 0.f,
		  moveDirection = 0.f;
	Math::Vec2 forces = { 0.f, 0.f },
			   velocity = { 0.f, 0.f };
	bool renderFlag = false;
};

/*!*****************************************************************************
\brief
This component encapsulates information regarding a rectangular collider for
collision detection
The centerOffset variable contains the offset from the entity's transform's 
 translation
The scaleOffset variable contains the offset from the entity's transform's scale
The renderFlag variable contains the flag variable telling the render manager
 whether to render the collider
*******************************************************************************/
struct RectCollider {
	Math::Vec2 centerOffset = { 0.f, 0.f },
			   scaleOffset = {1.f,1.f};
	// float rotationOffset,
	bool renderFlag = false;
};

/*!*****************************************************************************
\brief
This component encapsulates information regarding a circular collider for
collision detection
The centerOffset variable contains the offset from the entity's transform's
 translation
The scaleOffset variable contains the offset from the entity's transform's scale
The renderFlag variable contains the flag variable telling the render manager
 whether to render the collider
*******************************************************************************/
struct CircleCollider {
	Math::Vec2 centerOffset = { 0.f, 0.f };
	float scaleOffset = 1.f;
	bool renderFlag = false;
};

/*!*****************************************************************************
\brief
This component encapsulates information regarding an edge/line collider for
collision detection
The p0Offset variable contains the offset from the entity's first point's 
 transform's translation
The rotationOffset variable contains the offset from the entity's first point's 
 transform's rotation
The scaleOffset variable contains the offset from the entity's transform's scale
The renderFlag variable contains the flag variable telling the render manager
 whether to render the collider
*******************************************************************************/
struct Edge2DCollider {
	Math::Vec2 p0Offset = { 0.f, 0.f };
	float rotationOffset = 0.f,
		  scaleOffset = 1.f;
	bool renderFlag = false;
};

/*!*****************************************************************************
\brief
This component encapsulates information regarding a point collider for
collision detection
The centerOffset variable contains the offset from the entity's transform's
 translation
The renderFlag variable contains the flag variable telling the render manager
 whether to render the collider
*******************************************************************************/
struct Point2DCollider {
	Math::Vec2 centerOffset = { 0.f, 0.f };
	bool renderFlag = false;
};

/*!*****************************************************************************
\brief
This component encapsulates information regarding the player, such as health
*******************************************************************************/
struct PlayerTmp {
	int HP = 1;
};

/*!*****************************************************************************
\brief
	This temporary struct contains the data for AI component
*******************************************************************************/
struct Stuff {
	int	colorChange =0;
	int	movement = 0;
	float	speed = 1.f;
	float range = 10.f;
};
/*!*****************************************************************************
\brief
	This struct contains the data for Audio component
*******************************************************************************/
struct Audio {
	//std::vector<Sound> sound;
	Sound sound;
	bool isSpacial = false;
};
/*!*****************************************************************************
\brief
	This struct contains the data for Text component
*******************************************************************************/
struct Text {
	std::string text;
	int textID;
	int nextTextID;
	GLuint texture = 0; //for dialog box
};

/*!*****************************************************************************
\brief
	This struct contains the data for Script component
*******************************************************************************/
struct Script {
	std::string name;
	//ScriptComponent* script;
};

/*!*****************************************************************************
\brief
This component encapsulates information regarding a lightsource, currently, it
only contains an offset. Later versions will include light intensity.
*******************************************************************************/
struct LightSource
{
	Math::Vec2 centerOffset;
	float radius;
	float intensity; //"whiteness" of the light
};

struct ShadowCaster
{
	Math::Vec2 centerOffset = { 0.f, 0.f },	// save, edit, see
		scaleOffset = { 1.f,1.f };		// save, edit, see
	bool renderFlag{ false };				// save, edit, see
};

//use to index the variant data type, for ditor and serilization to determine type stored
enum class COMPONENTID
{
	GENERAL,		//0
	LIFESPAN,		//1
	TRANSFORM,		//2
	SPRITE,			//3
	ANIMATION,		//4
	SHEETANIMATION,	//5
	PHYSICS2D,		//6
	RECTCOLLIDER,	//7
	CIRCLECOLLIDER, //8
	EDGE2DCOLLIDER, //9
	POINT2DCOLLIDER,//10
	AUDIO,			//11
	TEXT,			//12
	AI,				//13
	SCRIPT,			//14
	DIALOGUE,		//15
	BUTTON,			//16
	LAYERCOLLIDER,	//17
	LIGHTSOURCE,	//18
	SHADOWCASTER	//19
};
typedef std::variant<General, Lifespan, Transform, Sprite, Animation, SheetAnimation,
	Physics2D, RectCollider, CircleCollider, Edge2DCollider,
	Point2DCollider, Audio, Text, AI, Script, Dialogue, Button, LayerCollider, LightSource, ShadowCaster>  COMPONENT;



