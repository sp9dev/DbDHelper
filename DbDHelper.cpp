/* PIOTR SLAWECKI */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include "SkillCheckLib.h"
#include "SimpleRegister.h"
#include <chrono>


using namespace std;
using namespace cv;


int main()
{
	bool activated = false;

	cout << "_________________________" << endl;
	cout << "Welcome to DbDHelper," << endl;
	cout << "a simple software, that helps you with the arcade apect of DbD game!" << endl;
	cout << "To activate DbDHelper, press numpad slash." << endl;
	cout << "By Piotr Slawecki" << endl;
	cout << "_________________________" << endl;

	AutoSkillcheck sc = AutoSkillcheck();
	
	while (true) {
		if(GetKeyState(0x6F) < 0) {
			activated = !activated;
			Sleep(400);
		}

		if (activated) sc.handleskillcheck();
	}

	
	return 0;
}

