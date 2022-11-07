#pragma once

#include <iostream>

struct FileHeader {
	int AArrayOffSet;
	int AArraySize;
	int BArrayOffSet;
	int BArraySize;
	int CArrayOffSet;
	int CArraySize;
};

struct A {
	char name[10];
	double age;
	bool isEighteen;
};

struct B {
	long number;
	unsigned age;
	float eighteen;
};

struct C {
	char name;
	long long age;
	short eighteen;
};