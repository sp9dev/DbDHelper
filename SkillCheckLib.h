/* PIOTR SLAWECKI */
#pragma once
#ifndef SKILLCHECKLIB_H
#define SKILLCHECKLIB_H
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include "SimpleRegister.h"
#include <time.h>

using namespace std;
using namespace cv;

class AutoSkillcheck
{
public:
	AutoSkillcheck();
	~AutoSkillcheck();

	void capturescreen();

	void prepareframe();

	void registerframe();

	void handleskillcheck();

	void presskey();

	void togglestate();

	bool getstate();



private:
	SimpleRegister reg;
	Mat currentframe;
	bool skillcheck;
	INPUT sckey;
	bool activated;
};











#endif