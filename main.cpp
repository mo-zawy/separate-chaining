#include <iostream>
#include "hash.h"
#include <string>
using namespace std;

int main()
{
    hash a;
    a.AddItem("mohamed");
    a.AddItem("ahmed");
    a.AddItem("emad");
    a.printTable();
    a.update();
    a.printTable();
    return 0;
}
