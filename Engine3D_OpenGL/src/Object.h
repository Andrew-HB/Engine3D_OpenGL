#pragma once
#include <string>
#include <vector>

#include "GLM.h"

class Object {
private:
	std::vector<triangle> vertices;
public: 
	std::vector<float> positions;
	std::vector<unsigned int> indices;
	
	Object(const std::string& filepath);
	Object() {}
	~Object() {}

	const void LoadFromFile(const std::string& filepath);
	const void ConvertObject(std::vector<triangle> v);

	inline std::vector<triangle> GetVertices() { return vertices; }
	//inline std::vector<float> GetPositions() { return positions; }
	//inline std::vector<float> GetIndices() { return indices; }
};