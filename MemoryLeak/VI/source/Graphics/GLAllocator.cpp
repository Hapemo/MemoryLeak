/*!*****************************************************************************
\file GLAllocator.cpp
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definitions for GLAllocator, which allocates memory
to a Vertex Buffer Object contained by a Vertex Array Object.
*******************************************************************************/
#include "Graphics/GLAllocator.h"

/*!*****************************************************************************
\brief
Constructor for Animator class.

\param size_t _noOfObjects
Number of objects to allocate memory for.

\param size_t _verticesPerObject
Number of vertices per object.

\param size_t _indicesPerObject
Number of indices per object.
*******************************************************************************/
GLAllocator::GLAllocator(size_t _noOfObjects, size_t _verticesPerObject, size_t _indicesPerObject)
{
	glCreateVertexArrays(1, &mvaoid);
	glBindVertexArray(mvaoid);

	glCreateBuffers(1, &mvboid);
	glNamedBufferStorage(mvboid, _noOfObjects * _verticesPerObject * sizeof(Vertex), nullptr, GL_DYNAMIC_STORAGE_BIT);

	glEnableVertexArrayAttrib(mvaoid, 0);
	glVertexArrayVertexBuffer(mvaoid, 0, mvboid, offsetof(Vertex, Vertex::position), sizeof(Vertex));
	glVertexArrayAttribFormat(mvaoid, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(mvaoid, 0, 0);

	glEnableVertexArrayAttrib(mvaoid, 1);
	glVertexArrayVertexBuffer(mvaoid, 1, mvboid, offsetof(Vertex, Vertex::color), sizeof(Vertex));
	glVertexArrayAttribFormat(mvaoid, 1, 4, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(mvaoid, 1, 1);

	glEnableVertexArrayAttrib(mvaoid, 2);
	glVertexArrayVertexBuffer(mvaoid, 2, mvboid, offsetof(Vertex, Vertex::texCoords), sizeof(Vertex));
	glVertexArrayAttribFormat(mvaoid, 2, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(mvaoid, 2, 2);

	glEnableVertexArrayAttrib(mvaoid, 3);
	glVertexArrayVertexBuffer(mvaoid, 3, mvboid, offsetof(Vertex, Vertex::texID), sizeof(Vertex));
	glVertexArrayAttribFormat(mvaoid, 3, 1, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(mvaoid, 3, 3);

	glCreateBuffers(1, &meboid);
	glNamedBufferStorage(meboid, _indicesPerObject * _noOfObjects * sizeof(GLushort), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(mvaoid, meboid);
	
	glBindVertexArray(0);
}

/*!*****************************************************************************
\brief
Binds the VAO to the OpenGL context.
*******************************************************************************/
void GLAllocator::BindVAO()
{
	glBindVertexArray(mvaoid);
}

/*!*****************************************************************************
\brief
Binds the VBO to the OpenGL context.
*******************************************************************************/
void GLAllocator::BindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, mvboid);
}

/*!*****************************************************************************
\brief
Unbinds the VAO from the OpenGL context.
*******************************************************************************/
void GLAllocator::UnbindVAO()
{
	glBindVertexArray(0);
}

/*!*****************************************************************************
\brief
Unbinds the VAO from the OpenGL context.
*******************************************************************************/
void GLAllocator::UnbindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}