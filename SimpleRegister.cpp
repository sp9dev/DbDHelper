#include "SimpleRegister.h"

SimpleRegister::SimpleRegister(int rsize, int defaultvalue) {
	assert(rsize > 0);
	this->regsize = rsize;
	this->data = new int[this->regsize];
	for (int i = 0; i < this->regsize; i++) this->data[i] = defaultvalue;
}

SimpleRegister::SimpleRegister() {
	this->regsize = 10;
	this->data = new int[this->regsize];
	for (int i = 0; i < this->regsize; i++) this->data[i] = 0;
}

SimpleRegister::~SimpleRegister() {
	
}

int SimpleRegister::size() const {
	return this->regsize;
}

void SimpleRegister::pushback(int num) {
	for (int i = 1; i < this->regsize; i++) this->data[i - 1] = this->data[i];
	this->data[this->regsize - 1] = num;
}

int SimpleRegister::rangeavg(int start, int end) {
	//start, end - inclusive
	assert(start >= 0);
	assert(end > start);
	assert(end < this->regsize);
	int sum = 0;
	for (int i = start; i <= end; i++) sum += this->data[i];
	return sum / (end - start + 1);
}

int SimpleRegister::avg() {
	int sum = 0;
	for (int i = 0; i < this->regsize; i++) sum += this->data[i];
	return sum / this->regsize;
}

bool SimpleRegister::detectdrop(int lastframecount, int tolerance) {
	assert(lastframecount < this->regsize);
	assert(lastframecount > 1);
	int previousavg = this->rangeavg(0, this->regsize - lastframecount - 1);
	int latestavg = this->rangeavg(this->regsize - lastframecount, this->regsize - 1);
	return (previousavg > latestavg + tolerance);
}