#include "IRenderable.h"
#include "Renderer.h"

IRenderable::IRenderable(bool toRender) : isRendered_(toRender)
{
	if(isRendered_)
		Renderer::getInstance()->RegisterRenderable(this);
}

IRenderable::IRenderable(Mesh* mesh, Material* material, bool toRender) : mesh_(mesh), material_(material), isRendered_(toRender)
{
	if(isRendered_)
		Renderer::getInstance()->RegisterRenderable(this);
}

IRenderable::~IRenderable()
{
	DeleteBuffers();
	if(isRendered_)
		Renderer::getInstance()->UnregisterRenderable(this);
}

void IRenderable::GenerateAndBindBuffers()
{
	glGenVertexArrays(1, &vertexArrayObject_);
	glGenBuffers(1, &vertexBuffer_);
	glGenBuffers(1, &normalBuffer_);
	glGenBuffers(1, &textCoordBuffer_);
	glGenBuffers(1, &indexBuffer_);

	glBindVertexArray(vertexArrayObject_);

	const std::vector<glm::vec3> vertices = mesh_->getVertices();
	const std::vector<glm::vec3> normals = mesh_->getNormals();
	const std::vector<glm::vec2> textCoords = mesh_->getTextureCoords();
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
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	if (!textCoords.empty())
	{
		// Bind a buffer for the UV coordinates
		glBindBuffer(GL_ARRAY_BUFFER, textCoordBuffer_);
		glBufferData(GL_ARRAY_BUFFER, textCoords.size() * sizeof(glm::vec2), &textCoords[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	if (!indices.empty())
	{
		// Bind a buffer for the indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
	}

	isBufferGenerated_ = true;
}

void IRenderable::Render(GLenum renderMode, bool renderWireframe)
{
	glBindVertexArray(vertexArrayObject_);

	if (renderWireframe && renderMode == GL_PATCHES)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
	
	glDrawElements(renderMode, static_cast<GLsizei>(mesh_->getIndices().size()), GL_UNSIGNED_SHORT, nullptr);

	if (renderWireframe && renderMode == GL_PATCHES)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void IRenderable::DeleteBuffers()
{
	glDeleteBuffers(1, &vertexBuffer_);
	glDeleteBuffers(1, &normalBuffer_);
	glDeleteBuffers(1, &textCoordBuffer_);
	glDeleteBuffers(1, &indexBuffer_);
	glDeleteVertexArrays(1, &vertexArrayObject_);
}

