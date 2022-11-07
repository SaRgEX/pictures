#pragma once

#include <iostream>
#include <fstream>
#include "file.h"





int writeFile(A* first, B* second, C* third, FileHeader* header)
{
	std::ofstream out("Structures.txt");

	if (out.is_open())
	{
		out.write((const char*)header, sizeof(FileHeader));

		out.write((const char*)first, header->AArraySize);
		out.write((const char*)second, header->BArraySize);
		out.write((const char*)third, header->CArraySize);
		std::cout << "End of program";
		out.close();
	}
	return 0;
}

int main()
{
	int a, b, c;

	std::cout << "A array size: ";
	std::cin >> a;
	std::cout << "B array size: ";
	std::cin >> b;
	std::cout << "C array size: ";
	std::cin >> c;

	A* structA = new A[a];
	B* structB = new B[b];
	C* structC = new C[c];

	for (int i = 0; i < a; i++)
	{
		std::cout << "A input 1: ";
		std::cin >> structA[i].name;
		std::cout << "A input 2: ";
		std::cin >> structA[i].age;
		std::cout << "A input 3: ";
		std::cin >> structA[i].isEighteen;
	}

	for (int i = 0; i < b; i++)
	{
		std::cout << "B input 1: ";
		std::cin >> structB[i].number;
		std::cout << "B input 2: ";
		std::cin >> structB[i].age;
		std::cout << "B input 3: ";
		std::cin >> structB[i].eighteen;
	}

	for (int i = 0; i < c; i++)
	{
		std::cout << "C input 1: ";
		std::cin >> structC[i].name;
		std::cout << "C input 2: ";
		std::cin >> structC[i].age;
		std::cout << "C input 3: ";
		std::cin >> structC[i].eighteen;
	}

	FileHeader header;
	header.AArrayOffSet = sizeof(header);
	header.AArraySize = sizeof(A) * a;
	header.BArrayOffSet = sizeof(header) + sizeof(header.AArraySize);
	header.BArraySize = sizeof(B) * b;
	header.CArrayOffSet = sizeof(header.BArrayOffSet) + sizeof(header.BArraySize);
	header.CArraySize = sizeof(C) * c;

	writeFile(structA, structB, structC, &header);

	delete structA;
	delete structB;
	delete structC;

	return 0;
}


