/*!
@file    my-tutorial-1.vert
@author  k.yujun@digipen.edu
@date    17/05/2022

This file contains the implementation of the vertex shader in GLSL.

*//*__________________________________________________________________________*/
#version 450 core

layout (location=0) in vec3 aVertexPosition;
layout (location=1) in vec4 aColor;
layout (location=2) in vec2 aVertexTexture;
layout (location=3) in float aTexID;

out vec4 vColor;
out vec2 vTexCoord;
out float vTexID;


/**
* @brief main function for vertex shader
* @param none
* @return none
*/
void main(void) {
	vec3 temp = vec3(vec2(aVertexPosition), -aVertexPosition.z);
	gl_Position = vec4(temp, 1.0);
	vColor = aColor;
	vTexCoord = aVertexTexture;
	vTexID = aTexID;
}
