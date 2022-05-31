#include "Object.h"

#include <iostream>
#include <fstream>
#include <strstream>

Object::Object(const std::string& filepath)
{
	LoadFromFile(filepath);
}

const void Object::LoadFromFile(const std::string& filepath)
{
	std::ifstream f(filepath);
	if (!f.is_open()) {
		std::cout << "Can't open file: \"" << filepath << "\"" << std::endl;
		return;
	}

	// Local cache of verts
	std::vector<vec3d> verts;

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v')
		{
			vec3d v;
			s >> junk >> v.x >> v.y >> v.z;
			verts.push_back(v);
		}

		if (line[0] == 'f')
		{
			int f[3];
			s >> junk >> f[0] >> f[1] >> f[2];
			this->vertices.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
		}
	}
}

const void Object::ConvertObject(std::vector<triangle> v)
{
	for (int i = 0; i < v.size(); i++) {
		this->positions.push_back(v[i].p[0].x);
		this->positions.push_back(v[i].p[0].y);
		this->positions.push_back(v[i].p[0].z);
		this->positions.push_back(v[i].gryscale);
		this->indices.push_back(i + 1);
	}
}
