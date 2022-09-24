/*!
@file    my-tutorial-1.frag
@author  k.yujun@digipen.edu
@date    17/05/2022

This file contains the implementation of the fragment shader in GLSL.

*//*__________________________________________________________________________*/
#version 450 core

in vec4 vColor;

out vec4 fFragColor;

/**
* @brief main function for fragment shader
* @param none
* @return none
*/
void main (void) 
{
	vec4 temp;		
	temp = vColor;
	if (temp.a <= 0)
		discard;
	fFragColor = vColor;
}
