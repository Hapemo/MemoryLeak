/* !
@file    my-tutorial-1.vert
@author  j.teoh@digipen.edu
@date    13/05/2022

This file contains specifications of Vertex Shader in GLSL

*//*__________________________________________________________________________*/

#version 450 core

// 8 is vertex attribute index that is associated with per-vertex
// position coordinates in VBO; this association was performed by
// this call: glEnableVertexArrayAttrib(vaoid, 8);
layout (location=8) in vec2 aVertexPosition;

// 9 is vertex attribute index that is associated with per-vertex
// position coordinates in VBO; this association was performed by
// this call: glEnableVertexArrayAttrib(vaoid, 9);
layout (location=9) in vec3 aVertexColor;

layout (location=0) out vec3 vColor;

/*  _________________________________________________________________________ */
/*! main

@param none

@return none

main function for initialising vertex shader program
*/
void main(void) {
	gl_Position = vec4(aVertexPosition, 0.0, 1.0);
	vColor = aVertexColor;
}

