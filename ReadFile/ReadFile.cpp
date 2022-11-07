#include <iostream>
#include <fstream>
#include "../sadzxc/file.h"

int main()
{
    FileHeader header;   
    A* a = 0;
    B* b = 0;
    C* c = 0;
    std::ifstream file("../sadzxc/Structures.txt");
    if (file.is_open())
    {
        file.read((char*)&header, sizeof(FileHeader));
        a = new A[header.AArraySize];
        b = new B[header.BArraySize];
        c = new C[header.CArraySize];

        file.read((char*)a, sizeof(A));
        for (int i = 0; i < header.AArraySize / sizeof(A); i++)
        {
            std::cout << "A ARRAY:\n";
            std::cout << a[i].name << " " << a[i].age << " " << a[i].isEighteen << "\n";
        }
        file.read((char*)b, sizeof(B));
        for (int i = 0; i < header.BArraySize / sizeof(B); i++)
        {
            std::cout << "B ARRAY:\n";
            std::cout << b[i].number << " " << b[i].age << " " << b[i].eighteen << "\n";
        }
        file.read((char*)c, sizeof(C));
        for (int i = 0; i < header.CArraySize / sizeof(C); i++)
        {
            std::cout << "C ARRAY:\n";
            std::cout << c[i].name << " " << c[i].age << " " << c[i].eighteen << "\n";
        }
        file.close();
    }
}
