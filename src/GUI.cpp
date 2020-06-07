#include "GUI.h"
#include "RenderView.h"

GUI* GUI::instance_ = 0;

void GUI::Initialize()
{
	TwInit(TW_OPENGL_CORE, NULL);
	TwWindowSize(RenderView::getInstance()->getWidth(), RenderView::getInstance()->getHeight());

	TwBar* GUI = TwNewBar("AngornRenderer GUI");
	TwDefine(" AngornRenderer GUI  size = '200 225' position='0 495' alpha = '200'");
	
	//RenderMode
	TwEnumVal Buffers[RenderMode::MAX_RENDER_MODES_AMOUNT] = {
		{ RenderMode::FINAL, "Lighting" },
		{ RenderMode::POSITION, "Position" },
		{ RenderMode::NORMAL, "Normals" },
		{ RenderMode::DIFFUSE, "Diffuse" },
		{ RenderMode::SPECULAR, "Specular" },
		{ RenderMode::AMBIENT, "Ambient" } };
	TwType BufferMode = TwDefineEnum("BufferType", Buffers,RenderMode::MAX_RENDER_MODES_AMOUNT);
	TwAddVarRW(GUI, "Buffer", BufferMode, &renderMode_, " keyIncr='1' help='Change the texture to be displayed' ");

}

void GUI::Update(float dt)
{
	TwDraw();
}

