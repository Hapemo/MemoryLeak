/*!*****************************************************************************
\file minimap.frag
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 26-11-2022
\brief
This file contains the fragment shader for rendering "circular viewport".
*******************************************************************************/
#version 450 core

//taking in vertex attributes from vertex shader
in vec4 vColor;
in vec2 vTexCoord;
in float vTexID;

//fragment color
out vec4 fFragColor;

//array of samplers/texture units
uniform sampler2D uTex2D[16];

/*!*****************************************************************************
\brief
Main function of the fragment shader.
*******************************************************************************/
void main (void) {
	if (distance(vec2(0.5, 0.5), vTexCoord) > 0.5)
		return;
	fFragColor =  texture(uTex2D[(int(vTexID) - 1) % 16], vTexCoord);;
}
