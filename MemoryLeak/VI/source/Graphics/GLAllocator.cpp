#include "Graphics/GLAllocator.h"

GLAllocator::GLAllocator(size_t no_of_objects, size_t max_vertices_per_object, size_t indices_per_object)
{
	glCreateVertexArrays(1, &vaoid);
	glBindVertexArray(vaoid);

	glCreateBuffers(1, &vboid);
	glNamedBufferStorage(vboid, no_of_objects * max_vertices_per_object * sizeof(Vertex), nullptr, GL_DYNAMIC_STORAGE_BIT);

	glEnableVertexArrayAttrib(vaoid, 0);
	glVertexArrayVertexBuffer(vaoid, 0, vboid, offsetof(Vertex, Vertex::position), sizeof(Vertex));
	glVertexArrayAttribFormat(vaoid, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 0, 0);

	glEnableVertexArrayAttrib(vaoid, 1);
	glVertexArrayVertexBuffer(vaoid, 1, vboid, offsetof(Vertex, Vertex::color), sizeof(Vertex));
	glVertexArrayAttribFormat(vaoid, 1, 4, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 1, 1);

	glEnableVertexArrayAttrib(vaoid, 2);
	glVertexArrayVertexBuffer(vaoid, 2, vboid, offsetof(Vertex, Vertex::texCoords), sizeof(Vertex));
	glVertexArrayAttribFormat(vaoid, 2, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 2, 2);

	glEnableVertexArrayAttrib(vaoid, 3);
	glVertexArrayVertexBuffer(vaoid, 3, vboid, offsetof(Vertex, Vertex::texID), sizeof(Vertex));
	glVertexArrayAttribFormat(vaoid, 3, 1, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 3, 3);

	glCreateBuffers(1, &eboid);
	glNamedBufferStorage(eboid, indices_per_object * no_of_objects * sizeof(GLushort), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vaoid, eboid);
	
	glBindVertexArray(0);
}

void GLAllocator::BindVAO()
{
	glBindVertexArray(vaoid);
}

void GLAllocator::BindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboid);
}

void GLAllocator::UnbindVAO()
{
	glBindVertexArray(0);
}

void GLAllocator::UnbindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//void GLAllocator::BindEBO()
//{
//	glBindBuffer(
//}

void GLAllocator::MapVBO(size_t size_of_vertices, Vertex* vertices)
{
	BindVBO();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size_of_vertices, vertices);
	UnbindVBO();
}