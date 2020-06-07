#ifndef GUI_H_
#define GUI_H_

#include "ISystem.h"
#include "AntTweakBar/AntTweakBar.h"
#include "RenderingUtils.h"

class GUI : public ISystem
{
public:
	static GUI* getInstance() {
		if (!instance_)
			instance_ = new GUI();
		return instance_;
	}

	void Initialize();
	void Update(float dt = 0);

	const RenderMode getRenderMode() const { return renderMode_; }
private:
	GUI() {}
	void Shutdown() {};
	static GUI* instance_;


	RenderMode renderMode_ = RenderMode::FINAL;
};

#endif