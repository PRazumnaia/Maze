#include "time.h"
#include <iostream>
using namespace std;

int main()
{
    int result = 48;
    if (timer(50, 2) == result) 
    {
        cout << "Timer test ended [CORRECT]\n" << endl;
    }
    else
    {
        cout << "Timer test ended [FAIL]\n" << endl;
    }
}

