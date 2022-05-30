#pragma once
#include <string>
#include <vector>

#include "GLM.h"

class Object {
private:
	std::vector<triangle> positions;
	//std::vector<vec3d> indices;
public: 
	Object(const std::string& filepath);
	Object() {}
	~Object() {}

	const void LoadFromFile(const std::string& filepath);

	inline std::vector<triangle> GetPositions() { return positions; }
	//inline std::vector<vec3d> GetIndices() { return indices; }
};