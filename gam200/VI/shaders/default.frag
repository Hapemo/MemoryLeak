/*!
@file    my-tutorial-1.frag
@author  k.yujun@digipen.edu
@date    17/05/2022

This file contains the implementation of the fragment shader in GLSL.

*//*__________________________________________________________________________*/
#version 450 core

layout (location=0) in vec2 vTextureCoordinates;

uniform int uType;
uniform vec4 uColor;
uniform sampler2D uTex2d;

layout (location=0) out vec4 fFragColor;
//layout (location=1) out vec2 fTexCoord;

/**
* @brief main function for fragment shader
* @param none
* @return none
*/
void main (void) {
	if (uType == 0)
		fFragColor = uColor;
	else
		fFragColor = texture(uTex2d, vTextureCoordinates);
}
