#ifndef FRAMERATECONTROLLER_H_
#define FRAMERATECONTROLLER_H_

#include "ISystem.h"
#include <string>

class FrameRateController : public ISystem
{
public:
	static FrameRateController* getInstance()
	{
		if (!instance_)
			instance_ = new FrameRateController();
		return instance_;
	}
	
	/// <summary>
	/// Starts counting the time
	/// </summary>
	void StartFrame();
	/// <summary>
	///  End counting the time and computes the passed time
	/// </summary>
	void EndFrame();
	
	double getCurrentFrameRate() { return frameRate_; }

	double getCurrentFrameTime() { return frameTime_; }

private:
	FrameRateController() {}
	static FrameRateController* instance_;

	void Initialize() {}
	void Update(float dt = 0) {}
	void Shutdown() {}

	/// <summary>
	/// Get the current time with at least milliseconds of precision
	/// </summary>
	/// <returns> Current time</returns>
	double getTime();

	double        minimumFrameRate_ = 1 / minimumFrameRate_;
	double        minimumFrameTime_ = 0.016666667f;
	double        frameTime_ = 0;
	double        frameRate_ = 0;

	double        frameTimeStart_ = 0;
	double        frameTimeEnd_ = 0;
};

#endif