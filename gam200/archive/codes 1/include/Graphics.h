/*!
@file			Graphics.cpp
@author		j.teoh@digipen.edu
@date			17/05/2022

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and to extract function pointers
to OpenGL implementations.

*//*__________________________________________________________________________*/
#pragma once
#include <glslshader.h>

class Graphics {
public:
	// previous existing declarations
	// encapsulates state required to render a geometrical model
	struct GLModel {
		GLenum primitive_type; // which OpenGL primitive to be rendered?
		GLSLShader shdr_pgm; // which shader program?
		GLuint vaoid; // handle to VAO
		GLuint idx_elem_cnt; // how many elements of primitive of type
		// primitive_type are to be rendered
		// member functions defined in glapp.cpp
		GLModel();
		void setup_vao();
		void setup_shdrpgm();
		void draw();
	};
	// data member to represent geometric model to be rendered
	// C++ requires this object to have a definition in glapp.cpp!!!
	static GLModel mdl;
	static void init();
	static void draw();
	static void cleanup();
};