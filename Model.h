#pragma once
#include "mat4.h"
#include "mesh.h"

class Model
{
public:

	Model();
	~Model();

	mesh meshData;
	mat4 matrix;
};

