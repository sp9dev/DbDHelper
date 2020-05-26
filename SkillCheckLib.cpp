/* PIOTR SLAWECKI */
#include "SkillCheckLib.h"

void AutoSkillcheck::capturescreen() {
	int x_size = 250, y_size = 250;
	HBITMAP hBitmap; 
	Mat matBitmap; 

	HDC hdcSys = GetDC(NULL);
	HDC hdcMem = CreateCompatibleDC(hdcSys); 
	void *ptrBitmapPixels; 

	BITMAPINFO bi; HDC hdc;
	ZeroMemory(&bi, sizeof(BITMAPINFO));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = x_size;
	bi.bmiHeader.biHeight = -y_size; 
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	hdc = GetDC(NULL);
	hBitmap = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &ptrBitmapPixels, NULL, 0);

	SelectObject(hdcMem, hBitmap);

	matBitmap = Mat(y_size, x_size, CV_8UC4, ptrBitmapPixels, 0);

	BitBlt(hdcMem, 0, 0, x_size, y_size, hdcSys, 835, 415, SRCCOPY); 
	DeleteObject(hBitmap);
	this->currentframe = matBitmap.clone();
	DeleteDC(hdc);
	DeleteDC(hdcSys);
	ReleaseDC(NULL, hdc);
	ReleaseDC(NULL, hdcSys);
	DeleteDC(hdcMem);
}

void AutoSkillcheck::prepareframe() {
	Mat cap_gray, res;
	cvtColor(this->currentframe, cap_gray, COLOR_BGR2GRAY);
	threshold(cap_gray, res, 245, 255, 3);
	cap_gray.release();
	this->currentframe = res.clone();
	res.release();
}

void AutoSkillcheck::registerframe() {
	this->reg.pushback(countNonZero(this->currentframe));
}

void AutoSkillcheck::presskey() {
	this->sckey.ki.dwFlags = 0;
	int tmp = rand() % 10 + 20;
	SendInput(1, &this->sckey, sizeof(INPUT));
	Sleep(tmp);
	this->sckey.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &this->sckey, sizeof(INPUT));
}

void AutoSkillcheck::handleskillcheck() {
	this->capturescreen();
	
	this->prepareframe();
	this->registerframe();
	int avg = this->reg.avg();
	if (avg > 20 && avg < 300) this->skillcheck = true;
	if (this->reg.detectdrop(2, 7) && skillcheck) {
		this->presskey();
		this->skillcheck = false;
		this->reg.setall(0);
		Sleep(3000);

	}
}

void AutoSkillcheck::togglestate() {
	this->activated = !this->activated;
}

bool AutoSkillcheck::getstate() {
	return this->activated;
}

AutoSkillcheck::AutoSkillcheck() {
	this->reg = SimpleRegister(10, 0);
	this->skillcheck = false;
	this->activated = false;
	this->sckey.type = INPUT_KEYBOARD;
	this->sckey.ki.wScan = ' ';
	this->sckey.ki.time = 0;
	this->sckey.ki.dwExtraInfo = 0;
	this->sckey.ki.wVk = 0x20;
}

AutoSkillcheck::~AutoSkillcheck() {
}


