#pragma once
//define number of triangles for circle
constexpr int CIRCLE_SLICES = 18;
//modifier for vector.reserve() 
constexpr float MODIFIER = 0.05f;
constexpr size_t NO_OF_OBJECTS = 10000;
constexpr size_t VERTICES_PER_OBJECT = 4;
constexpr size_t INDICES_PER_OBJECT = 6;
//maximum used texture units in 1 draw call
constexpr size_t TEXTURES_PER_DRAW = 16;