#include "SkillCheckLib.h"

void AutoSkillcheck::capturescreen() {
	int x_size = 250, y_size = 250; // <-- Your res for the image

	HBITMAP hBitmap; // <-- The image represented by hBitmap

	Mat matBitmap; // <-- The image represented by mat

	// Initialize DCs

	HDC hdcSys = GetDC(NULL); // Get DC of the target capture..
	HDC hdcMem = CreateCompatibleDC(hdcSys); // Create compatible DC 
	void *ptrBitmapPixels; // <-- Pointer variable that will contain the potinter for the pixels

	// Create hBitmap with Pointer to the pixels of the Bitmap
	BITMAPINFO bi; HDC hdc;
	ZeroMemory(&bi, sizeof(BITMAPINFO));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = x_size;
	bi.bmiHeader.biHeight = -y_size; 

	bi.bmiHeader.biPlanes = 1;

	bi.bmiHeader.biBitCount = 32;
	hdc = GetDC(NULL);
	hBitmap = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &ptrBitmapPixels, NULL, 0);
	// ^^ The output: hBitmap & ptrBitmapPixels

	// Set hBitmap in the hdcMem 
	SelectObject(hdcMem, hBitmap);

	// Set matBitmap to point to the pixels of the hBitmap
	matBitmap = Mat(y_size, x_size, CV_8UC4, ptrBitmapPixels, 0);
	// * SETUP DONE *

	// Now update the pixels using BitBlt
	BitBlt(hdcMem, 0, 0, x_size, y_size, hdcSys, 835, 415, SRCCOPY); 
	DeleteObject(hBitmap);
	this->currentframe = matBitmap;
	DeleteDC(hdc);
	DeleteDC(hdcSys);

}

void AutoSkillcheck::prepareframe() {
	Mat cap_gray, res;
	cvtColor(this->currentframe, cap_gray, COLOR_BGR2GRAY);
	threshold(cap_gray, res, 245, 255, 3);
	cap_gray.release();
	this->currentframe = res;
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
		Sleep(2000);
	}
}

AutoSkillcheck::AutoSkillcheck() {
	this->reg = SimpleRegister(10, 0);
	this->skillcheck = false;
	this->sckey.type = INPUT_KEYBOARD;
	this->sckey.ki.wScan = ' ';
	this->sckey.ki.time = 0;
	this->sckey.ki.dwExtraInfo = 0;
	this->sckey.ki.wVk = 0x20;
}

AutoSkillcheck::~AutoSkillcheck() {
}


