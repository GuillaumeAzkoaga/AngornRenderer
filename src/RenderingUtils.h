#ifndef RENDERING_UTILS_H_
#define RENDERING_UTILS_H_

#include <glew.h>
#include <wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

// Shader paths
#define GEOMETRY_VERTEX_FILE			"../Data/Shaders/geometry_pass.vert"
#define GEOMETRY_FRAGMENT_FILE			"../Data/Shaders/geometry_pass.frag"
#define TESS_CONTROL_FILE				"../Data/Shaders/tess_control.sh"
#define TESS_EVAL_FILE					"../Data/Shaders/tess_eval.sh"
#define MULTILIGHTING_VERTEX_FILE		"../Data/Shaders/multilighting_pass.vert"
#define MULTILIGHTING_FRAGMENT_FILE		"../Data/Shaders/multilighting_pass.frag"
#define EDGE_DETECTION_VERTEX_FILE		"../Data/Shaders/edge_pass.vert"
#define EDGE_DETECTION_FRAGMENT_FILE	"../Data/Shaders/edge_pass.frag"
#define RENDER_VERTEX_FILE				"../Data/Shaders/render.vert"
#define RENDER_FRAGMENT_FILE			"../Data/Shaders/render.frag"

enum RenderMode
{
	FINAL,
	POSITION,
	NORMAL,
	DIFFUSE,
	SPECULAR,
	AMBIENT,

	MAX_RENDER_MODES_AMOUNT
};



GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

void GLAPIENTRY MessageCallback(GLenum source,	GLenum type, GLuint id,	GLenum severity, GLsizei length, const GLchar* message,	const void* userParam );


#endif