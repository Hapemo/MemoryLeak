/*!
@file    my-tutorial-1.frag
@author  k.yujun@digipen.edu
@date    17/05/2022

This file contains the implementation of the fragment shader in GLSL.

*//*__________________________________________________________________________*/
#version 450 core

in vec4 vColor;
in vec2 vTexCoord;
in float vTexID;

out vec4 fFragColor;

uniform sampler2D uTex2D[16];

/**
* @brief main function for fragment shader
* @param none
* @return none
*/
void main (void) {
	vec4 temp;
	if (int(vTexID) == 0)
		temp = vColor;
	else
		temp = texture(uTex2D[(int(vTexID) - 1) % 16], vTexCoord);

	if (temp.a <= 0)
		discard;
	fFragColor = temp;
}
