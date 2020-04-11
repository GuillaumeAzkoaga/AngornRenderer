#include "IRenderable.h"
#include "Renderer.h"

IRenderable::IRenderable()
{
	Renderer::getInstance()->RegisterRenderable(this);
}

IRenderable::IRenderable(Mesh* mesh, Material* material) : mesh_(mesh), material_(material)
{
	Renderer::getInstance()->RegisterRenderable(this);
}

void IRenderable::Initialize()
{
	glGenVertexArrays(1, &vertexArrayObject_);
	glGenBuffers(1, &vertexBuffer_);
	glGenBuffers(1, &normalBuffer_);
	glGenBuffers(1, &indexBuffer_);

	glBindVertexArray(vertexArrayObject_);

	//TODO: if any of those vectors is empty, we should display an error message (better after mesh is loaded than here)
	const std::vector<glm::vec3> vertices = mesh_->getVertices();
	const std::vector<glm::vec3> normals = mesh_->getNormals();
	const std::vector<unsigned short> indices = mesh_->getIndices();
	if (!vertices.empty())
	{
		// Bind a buffer of vertices
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	if (!normals.empty())
	{
		// Bind a buffer for the indices
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer_);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	if (!indices.empty())
	{
		// Bind a buffer for the indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
	}
}

void IRenderable::Render(GLenum renderMode, bool renderWireframe)
{
	glBindVertexArray(vertexArrayObject_);

	if(renderWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh_->getIndices().size()), GL_UNSIGNED_SHORT, (void*)0);
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		if (renderMode == GL_PATCHES)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDrawElements(renderMode, static_cast<GLsizei>(mesh_->getIndices().size()),	GL_UNSIGNED_SHORT, nullptr);

		if (renderMode == GL_PATCHES)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}

void IRenderable::Shutdown()
{
	glDeleteBuffers(1, &vertexBuffer_);
	glDeleteBuffers(1, &normalBuffer_);
	glDeleteBuffers(1, &indexBuffer_);
	glDeleteVertexArrays(1, &vertexArrayObject_);
}
