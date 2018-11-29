#include "ObjLoader.h"
#include "v2.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

ObjLoader::ObjLoader() {}
ObjLoader::~ObjLoader() {}


void ObjLoader::load(const char* filename, mesh* loadTo)
{
	if (loadTo == nullptr)
		return;

	m_mesh = loadTo;

	std::ifstream file;
	file.open(filename);

	std::string lineBuff;

	if (file.is_open())
	{
		while (getline(file, lineBuff))
		{
			parse(lineBuff);
		}
		file.close();

	}
	else
	{
		std::cout << "can't open file " << filename << std::endl;
	}
}

void ObjLoader::dump(const char* filename)
{
	if (m_mesh == nullptr)
		return;

	std::ofstream file;
	file.open(filename);

	if (file.is_open())
	{
		for (auto i : m_mesh->vertices)
		{
			file << "v " << i.x << " " << i.y << " " << i.z << std::endl;
		}
		for (auto i : m_mesh->normals)
		{
			file << "vn " << i.x << " " << i.y << " " << i.z << std::endl;
		}
		for (auto i : m_mesh->faces)
		{
			file << "f " << i.vertex[0] << "/" << i.texcoord[0] << "/" << i.normal[0]
				<< " " << i.vertex[1] << "/" << i.texcoord[1] << "/" << i.normal[1]
				<< " " << i.vertex[2] << "/" << i.texcoord[2] << "/" << i.normal[2]
				<< std::endl;
		}
		file.close();

	}
	else
	{
		std::cout << "can't open file " << filename << std::endl;
	}
}

void splitLine(const std::string& str, std::vector<std::string>& tokens, char delim)
{
	unsigned int pos = str.find(delim);
	unsigned int i = 0;
	tokens.clear();

	while (pos != std::string::npos) {
		tokens.push_back(str.substr(i, pos - i + 1));
		i = pos + 1;

		pos = str.find(delim, i);
	}

	tokens.push_back(str.substr(i, std::min(pos, str.size()) - i + 1));

}

void ObjLoader::parse(const std::string& line)
{
	if (line[0] == ' ' || line[0] == '#')
		return;

	std::vector<std::string> tokens;
	splitLine(line, tokens, ' ');

	if (tokens[0] == "v ")
	{
		v3 vertex(
			std::stof(tokens[1]),
			std::stof(tokens[2]),
			std::stof(tokens[3])
		);

		vertex.y *= -1;

		m_mesh->vertices.push_back(vertex);
	}
	else if (tokens[0] == "vt ")
	{
		//wrap uv on import
		v2 uv(
			std::stof(tokens[1]),
			std::stof(tokens[2])
		);
		if (uv.x < 0.0f) uv.x = 1.0f - uv.x;
		if (uv.x > 1.0f) uv.x -= -1.0f;
		if (uv.y < 0.0f) uv.y = 1.0f - uv.y;
		if (uv.y > 1.0f) uv.y -= 1.0f;
		m_mesh->texCoords.push_back(uv);
	}
	else if (tokens[0] == "vn ")
	{
		v3 normal(
			std::stof(tokens[1]),
			std::stof(tokens[2]),
			std::stof(tokens[3])
		);
		normal.y *= -1;

		m_mesh->normals.push_back(normal);
	}
	else if (tokens[0] == "f ")
	{
		std::vector<std::string> ftok1, ftok2, ftok3;
		splitLine(tokens[1], ftok1, '/');
		splitLine(tokens[2], ftok2, '/');
		splitLine(tokens[3], ftok3, '/');

		face f;
		f.vertex[0] = std::stoi(ftok1[0]) - 1;
		f.vertex[1] = std::stoi(ftok2[0]) - 1;
		f.vertex[2] = std::stoi(ftok3[0]) - 1;
		f.texcoord[0] = std::stoi(ftok1[1]) - 1;
		f.texcoord[1] = std::stoi(ftok2[1]) - 1;
		f.texcoord[2] = std::stoi(ftok3[1]) - 1;
		f.normal[0] = std::stoi(ftok1[2]) - 1;
		f.normal[1] = std::stoi(ftok2[2]) - 1;
		f.normal[2] = std::stoi(ftok3[2]) - 1;

		m_mesh->faces.push_back(f);
	}
}