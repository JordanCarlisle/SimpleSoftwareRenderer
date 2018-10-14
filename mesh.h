#pragma once
#include "v3.h"
#include "v2.h"
#include <vector>

struct face
{
	unsigned int vertex[3];
	unsigned int texcoord[3];
	unsigned int normal[3];
};

struct mesh
{
	std::vector<v3> vertices;
	std::vector<face> faces;
	std::vector<v3> normals;
	std::vector<v2> texCoords;
};