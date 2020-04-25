#include "FrameRateController.h"
#include <Windows.h>

FrameRateController* FrameRateController::instance_ = 0;
void FrameRateController::StartFrame()
{
	frameTimeStart_ = getTime(); /* Get time at frame start */
}

void FrameRateController::EndFrame()
{
	// Be idle until Frame cap passed
	do
	{
		frameTimeEnd_ = getTime();                        //Get time at frame end          
		frameTime_ = frameTimeEnd_ - frameTimeStart_;     //Time that elapsed in the frame 
	} while (frameTime_ < minimumFrameTime_);

	frameRate_ = 1.0f / frameTime_;                      // Calculate Instant Frame Rate 
}

double FrameRateController::getTime()
{
	__int64 f, t;
	double  r, r0, r1;

	QueryPerformanceFrequency((LARGE_INTEGER*)(&f));
	QueryPerformanceCounter((LARGE_INTEGER*)(&t));

	r0 = double(t / f);
	r1 = (t - ((t / f) * f)) / (double)(f);
	r = r0 + r1;

	return r;
}

