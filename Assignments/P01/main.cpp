/**********************************************************************
 * Jonathan Hogan                                                     *
 * Dr. Stringfellow                                                   *
 * CMPS-2433-101                                                      *
 * September 23 2020                                                  *
 *                                                                    *
 * *******************************************************************/

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

int HighBit (unsigned int);
int NextHigh (unsigned int, int);

int main ()
{
    int counter, index;
    unsigned int number;

    ifstream InFile;
    ofstream OutFile;

    InFile.open("HighBits");
    
    InFile >> counter;

    for (int i =0; i < counter; i++)
    {
        InFile >> number;
        index = HighBit(number);
    }


}


// Function to locate the index of the highest bit.
int HighBit(unsigned int a) {
    int index = 1;

    while (a != 1)
    {
        if (a == 0)
        {
            index = -1;
        }
        a = a >> 1;
        index++;
    }

    return index;
}

// Function used to mask the next highest bit to 1
int NextHigh(unsigned int a, int b) {
    return 0,
}