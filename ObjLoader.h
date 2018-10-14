#pragma once
#include "mesh.h"

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	void load(const char* filename, mesh* loadTo);
	void dump(const char* filename);
	
private:

	mesh* m_mesh;

	void parse(const std::string& line);
};

