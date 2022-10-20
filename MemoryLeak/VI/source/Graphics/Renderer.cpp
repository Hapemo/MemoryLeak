#include <Renderer.h>

//define number of triangles for circle
constexpr int CIRCLE_SLICES = 18;
//modifier for vector.reserve() 
constexpr float MODIFIER = 0.05f;
constexpr size_t NO_OF_OBJECTS = 10000;
constexpr size_t VERTICES_PER_OBJECT = 4;
constexpr size_t INDICES_PER_OBJECT = 6;
//maximum used texture units in 1 draw call
constexpr size_t TEXTURES_PER_DRAW = 16;

Renderer::Renderer() : 
mAllocator(NO_OF_OBJECTS, VERTICES_PER_OBJECT, INDICES_PER_OBJECT),
mfbo(), mDefaultProgram("shaders/default.vert", "shaders/default.frag"),
mTextureProgram("shaders/texture.vert", "shaders/texture.frag")
{
	//set debug mode to true
	mDebug = true;
	mVectorLengthModifier = 50.f;

	//initialize opengl values
	glClearColor(0.537f, 0.812f, 0.941f, 1.f);
	glPointSize(8.f);
	glLineWidth(2.f);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	InitializeShaders();

	//reserve space in vectors
	mVertices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * VERTICES_PER_OBJECT));
	mIndices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * INDICES_PER_OBJECT));
	mTextureVertices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * VERTICES_PER_OBJECT));
	mTextureIndices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * INDICES_PER_OBJECT));
	mDebugPoints.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER));
	mDebugVertices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * VERTICES_PER_OBJECT));
	mDebugIndices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * INDICES_PER_OBJECT));
}

/*!*****************************************************************************
\brief
Initializes the Shader program.
*******************************************************************************/
void Renderer::InitializeShaders()
{
	mDefaultProgram.CompileLinkShaders();
	mTextureProgram.CompileLinkShaders();

	mDefaultProgram.Validate(), mTextureProgram.Validate();
}