/*************************************
 * Jonathan Hogan                    *
 * Dr. Stringfellow                  *
 * CMPS-2433-101                     *
 * September 23 2020                 *
 *                                   *
 * **********************************/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int HighBit (int);
int NextHigh (int);

int main ()
{
    int counter;
    unsigned int number;

    ifstream InFile;
    ofstream OutFile;

    InFile.open("HighBits.dat");
    
    InFile >> counter;

    for (int i =0; i < counter; i++)
    {
        InFile >> number;
        HighBit(number);
    }


}