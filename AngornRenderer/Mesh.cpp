#include "Mesh.h"
#include "tiny_obj_loader.h"
#include <Windows.h>
#include "RenderView.h"

void Mesh::LoadMesh(const std::string file)
{
	using namespace tinyobj;
	
	std::vector<shape_t> tiny_obj_shapes;
	std::vector<material_t> tiny_obj_mats;
	std::string load_result = LoadObj(tiny_obj_shapes, tiny_obj_mats, file.c_str());
	if (load_result.empty())
	{
		for (const shape_t shape : tiny_obj_shapes)
		{
			std::size_t vertices_num = shape.mesh.positions.size() / 3; //Position are stored as a succession of x,y,z floats
			const std::vector<float> pos = shape.mesh.positions;
			const std::vector<float> normal = shape.mesh.normals;
			const std::vector<unsigned int> indices = shape.mesh.indices;

			for (const unsigned int index : indices)
				indices_.push_back((unsigned short)index);

			for (std::size_t i = 0; i < vertices_num; ++i)
			{
				if(!normal.empty())
					normals_.push_back(glm::vec3(normal[i * 3], normal[i * 3 + 1], normal[i * 3 + 2]));

				if (!pos.empty())
					vertices_.push_back(glm::vec3(pos[3 * i], pos[3 * i + 1], pos[3 * i + 2]));
			}
		}

		fileName_ = file;
	}
	else
		MessageBox(RenderView::getInstance()->getHandle(), ("Error loading mesh from file" + file).c_str() , "Mesh Loading Failed", MB_ICONERROR);
	

}

std::string Mesh::getName() const
{
	return fileName_;
}
