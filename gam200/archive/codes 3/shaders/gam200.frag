/* !
@file    my-tutorial-1.frag
@author  j.teoh@digipen.edu
@date    13/05/2022

This file contains specifications of Fragment Shader in GLSL

*//*__________________________________________________________________________*/
#version 450 core

layout (location=0) in vec3 vInterpColor;

layout (location=0) out vec4 fFragColor;

/*  _________________________________________________________________________ */
/*! main

@param none

@return none

main function for initialising fragment shader program
*/
void main () {
	fFragColor = vec4(vInterpColor, 1.0);
}
