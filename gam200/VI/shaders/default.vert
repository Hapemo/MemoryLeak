/*!
@file    my-tutorial-1.vert
@author  k.yujun@digipen.edu
@date    17/05/2022

This file contains the implementation of the vertex shader in GLSL.

*//*__________________________________________________________________________*/
#version 450 core

layout (location=0) in vec2 aVertexPosition;
layout (location=2) in vec2 aVertexTexture;

uniform mat3 uModel_to_NDC;

layout (location=0) out vec2 vTexture;

/**
* @brief main function for vertex shader
* @param none
* @return none
*/
void main(void) {
	gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
	vTexture = aVertexTexture;
}
