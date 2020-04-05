#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>

#include "MathUtils.h"


class Mesh
{
public:
	Mesh() {};
	void LoadMesh(const std::string file);
	std::string getName() const;

	std::vector<glm::vec3> getVertices() const { return vertices_; }
	std::vector<glm::vec3> getNormals() const { return normals_; }
	std::vector<unsigned short> getIndices() const { return indices_; }

private:
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::vector<unsigned short> indices_;
	std::string fileName_;
};

#endif