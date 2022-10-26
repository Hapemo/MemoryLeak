/*!*****************************************************************************
\file ECS_components.h
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
This file contains all the structs of components used in ECS
*******************************************************************************/
#pragma once
#include <glm/glm.hpp>
#include "vec2.h"
#include "Graphics/SpriteVariable.h"
#include "AudioVariable.h"
#include "TagVariable.h"
#include "../Physics/Force.h"

struct General {
	std::string name;
	TAG tag;
	SUBTAG	subtag = SUBTAG::NOSUBTAG;
	bool isActive;
};

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
	std::vector<GLuint> images;
	float timePerImage;
	float timeToImageSwap;
	int currentImageIndex;
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

class Force;

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
	bool gravityEnabled;
	double gravityScale;
	bool dynamicsEnabled;

	double mass;
	double invMass;

	double inertia;
	double invInertia;

	// double density;
	double restitution;
	double friction;
	double damping;
	Math::Vec2 accumulatedForce;

	//float speed;
	//float moveDirection;
	
	Math::Vec2 velocity;
	Math::Vec2 acceleration;
	
	double angularVelocity;
	double angularTorque;
	
	std::vector<Force> forceList;

	bool renderFlag;
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
	Math::Vec2 centerOffset;
	Math::Vec2 scaleOffset;
	bool isTrigger;
	bool renderFlag;
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
	Math::Vec2 centerOffset;
	float scaleOffset;
	bool isTrigger;
	bool renderFlag;
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

