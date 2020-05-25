#pragma once
#ifndef SIMPLEREGISTER_H
#define SIMPLEREGISTER_H
#include <cassert>



class SimpleRegister
{

private:
	int regsize;
	int* data;

public:
	SimpleRegister(int rsize, int defaultvalue);
	SimpleRegister();
	~SimpleRegister();

	int size() const;

	void pushback(int num);

	int rangeavg(int start, int end);

	int avg();

	bool detectdrop(int lastframecount, int tolerance);


};



#endif