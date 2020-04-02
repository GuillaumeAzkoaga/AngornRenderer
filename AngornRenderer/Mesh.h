#ifndef MESH_H_
#define MESH_H_

#include <glm/glm.hpp>
#include <string>
#include <vector>

class Mesh
{
public:
	Mesh() {};
	void LoadMesh(const std::string file);
	std::string getName() const;

private:
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::vector<unsigned short> indices_;
	std::string fileName_;
};

#endif