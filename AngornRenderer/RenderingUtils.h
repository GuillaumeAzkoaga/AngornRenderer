#ifndef RENDERING_UTILS_H_
#define RENDERING_UTILS_H_

#include <glew.h>
#include <wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

// Shader paths
#define GEOMETRY_VERTEX_FILE			"../Shaders/geometry_pass.vert"
#define GEOMETRY_FRAGMENT_FILE			"../Shaders/geometry_pass.frag"
#define MULTILIGHTING_VERTEX_FILE		"../Shaders/multilighting_pass.vert"
#define MULTILIGHTING_FRAGMENT_FILE		"../Shaders/multilighting_pass.frag"
#define EDGE_DETECTION_VERTEX_FILE		"../Shaders/edge_pass.vert"
#define EDGE_DETECTION_FRAGMENT_FILE	"../Shaders/edge_pass.frag"
#define VIEW_VERTEX_FILE				"../Shaders/view.vert"
#define VIEW_FRAGMENT_FILE				"../Shaders/view.frag"

enum RenderMode
{
	FINAL,
	POSITION,
	NORMAL,
	DIFFUSE,
	SPECULAR,
	SPECULARCOLOR,
	EDGES,
	DEPTH,

	MAX_RENDER_MODES_AMOUNT
};



GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

void GLAPIENTRY MessageCallback(GLenum source,	GLenum type, GLuint id,	GLenum severity, GLsizei length, const GLchar* message,	const void* userParam );


#endif