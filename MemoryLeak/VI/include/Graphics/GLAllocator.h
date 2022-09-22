#pragma once
#include "Vertex.h"

class GLAllocator
{
public:
	GLAllocator(size_t no_of_objects, size_t max_vertices_per_object, size_t indices_per_object);
	void BindVAO();
	void BindVBO();
	void UnbindVAO();
	void UnbindVBO();
	void MapVBO(size_t size_of_vertices, Vertex* vertices);
	GLuint vaoid;
	GLuint vboid;
	GLuint eboid;
private:
};

