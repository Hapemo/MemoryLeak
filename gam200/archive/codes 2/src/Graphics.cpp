/*!
@file			Graphics.cpp
@author		j.teoh@digipen.edu
@date			17/05/2022

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and to extract function pointers
to OpenGL implementations.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <Graphics.h>
#include <Helper.h>
#include <array>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Application.h"

/*                                                   objects with file scope
----------------------------------------------------------------------------- */

static float color[3]{ 0, 1, 0 };
Graphics::GLModel Graphics::mdl;

/*  _________________________________________________________________________ */
/*! GLModel

@param none

@return GLModel

Default constructor for GLModel
*/
Graphics::GLModel::GLModel() : primitive_type(), shdr_pgm(), vaoid(), idx_elem_cnt() {}

/*  _________________________________________________________________________ */
/*! init

@param none

@return none

Initialise the application, such as background color, viewport, VAO and shader program files
*/
void Graphics::init() {
	// Part 1: clear colorbuffer with RGBA value in glClearColor ...
	glClearColor(color[0], color[1], color[2], 1.f);

	// Part 2: use the entire window as viewport ...
	glViewport(0, 0, Application::getWindowWidth(), Application::getWindowHeight());

	// Part 3: initialize VAO and create shader program
	mdl.setup_vao();
	mdl.setup_shdrpgm();
}


/*  _________________________________________________________________________ */
/*! draw

@param none

@return none

Draw models onto viewport
*/
void Graphics::draw() {
	// clear back buffer as before
	glClear(GL_COLOR_BUFFER_BIT);
	// now, render rectangular model from NDC coordinates to viewport
	mdl.draw();
}

/*  _________________________________________________________________________ */
/*! cleanup

@param none

@return none

Unload and reset the components of the application
*/
void Graphics::cleanup() {
	glClear(GL_COLOR_BUFFER_BIT);
}

/*  _________________________________________________________________________ */
/*! setup_vao

@param none

@return none

Setting up VAO, VBO, EBO and primatives
*/
void Graphics::GLModel::setup_vao() {
	// We'll define a rectangle in normalized device coordinates (NDC)
	// coordinates that has one-fourth the area of the window.
	// The NDC coordinates for a window range from [-1, 1] along both
	// both the X- and Y-axes. Therefore, the rectangle's (x, y) position
	// coordinates are in range [-0.5, 0.5]
	// We're using NDC coordinates, because we don't want to specify
	// a "model-to-world-to-view-to-clip" transform to the vertex shader.
	std::array<glm::vec2, 4> pos_vtx{
		glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.5f),
		glm::vec2(-0.5f, 0.5f), glm::vec2(-0.5f, -0.5f)
	};
	std::array<glm::vec3, 4> clr_vtx{
		glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f)
	};

	// VBO
	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl);
	glNamedBufferStorage(vbo_hdl,
		sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec3) * clr_vtx.size(),
		nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(vbo_hdl, 0,
		sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());
	glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(),
		sizeof(glm::vec3) * clr_vtx.size(), clr_vtx.data());

	// VAO
	glCreateVertexArrays(1, &vaoid);
	// for vertex position array, we use vertex attribute index 8
	// and vertex buffer binding point 3
	glEnableVertexArrayAttrib(vaoid, 8);
	glVertexArrayVertexBuffer(vaoid, 3, vbo_hdl, 0, sizeof(glm::vec2));
	glVertexArrayAttribFormat(vaoid, 8, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 8, 3);
	// for vertex color array, we use vertex attribute index 9
	// and vertex buffer binding point 4
	glEnableVertexArrayAttrib(vaoid, 9);
	glVertexArrayVertexBuffer(vaoid, 4, vbo_hdl,
		sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec3));
	glVertexArrayAttribFormat(vaoid, 9, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 9, 4);

	// Primative 
	primitive_type = GL_TRIANGLES;
	// represents indices of vertices that will define 2 triangles with
	// counterclockwise winding
	std::array<GLushort, 6> idx_vtx{
		0, 1, 2, // 1st triangle with counterclockwise winding is specified by
		// vertices in VBOs with indices 0, 1, 2
		2, 3, 0 // 2nd triangle with counterclockwise winding
	};

	idx_elem_cnt = (GLuint)idx_vtx.size();

	// EBO
	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl);
	glNamedBufferStorage(ebo_hdl,
		sizeof(GLushort) * idx_elem_cnt,
		reinterpret_cast<GLvoid*>(idx_vtx.data()),
		GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vaoid, ebo_hdl);
	glBindVertexArray(0);
}

/*  _________________________________________________________________________ */
/*! setup_shdrpgm

@param none

@return none

Set up shader program file
*/
void Graphics::GLModel::setup_shdrpgm() {
	std::vector<std::pair<GLenum, std::string>> shdr_files;
	shdr_files.emplace_back(std::make_pair(
		GL_VERTEX_SHADER,
		"codes/shaders/gam200.vert"));
	shdr_files.emplace_back(std::make_pair(
		GL_FRAGMENT_SHADER,
		"codes/shaders/gam200.frag"));
	shdr_pgm.CompileLinkValidate(shdr_files);
	if (GL_FALSE == shdr_pgm.IsLinked()) {
		std::cout << "Unable to compile/link/validate shader programs" << "\n";
		std::cout << shdr_pgm.GetLog() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

/*  _________________________________________________________________________ */
/*! draw

@param none

@return none

Draw out model
*/
void Graphics::GLModel::draw() {
	// there are many shader programs initialized - here we're saying
	// which specific shader program should be used to render geometry
	shdr_pgm.Use();
	// there are many models, each with their own initialized VAO object
	// here, we're saying which VAO's state should be used to set up pipe
	glBindVertexArray(vaoid);
	// here, we're saying what primitive is to be rendered and how many
	// such primitives exist.
	// the graphics driver knows where to get the indices because the VAO
	// containing this state information has been made current ...
	glDrawElements(primitive_type, idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
	// after completing the rendering, we tell the driver that VAO
	// vaoid and current shader program are no longer current
	glBindVertexArray(0);
	shdr_pgm.UnUse();
}