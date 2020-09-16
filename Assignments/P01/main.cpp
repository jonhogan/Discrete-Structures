/**********************************************************************
 * Jonathan Hogan                                                     *
 * Dr. Stringfellow                                                   *
 * CMPS-2433-101                                                      *
 * September 23 2020                                                  *
 *                                                                    *
 * *******************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int HighBit(unsigned int);
int NextHigh(unsigned int, int);

int main()
{
    int cases, index, k2;
    unsigned int k;
    string fileName;

    ifstream inFile;
    ofstream outFile;

    cout << "Please enter the name of the file you wish to use: ";
    cin >> fileName;

    inFile.open(fileName);
    outFile.open("output.txt");

    inFile >> cases;

    outFile << "Jonathan Hogan\nHighest Bit Program 1\n\n"
         << "There are " << cases << " test cases.\n\n"
         << "k   HighestBit   k2\n___________________\n";

    for (int i = 0; i < cases; i++)
    {
        inFile >> k;
        index = HighBit(k);
        k2 = NextHigh(k, index);
        if (index < 0)
        {
            outFile << setw(5) << k << setw(6) << '-' << setw(8)
                << k2 << '\n';
        }
        else
        {
            outFile << setw(5) << k << setw(6) << index << setw(8) 
                << k2 << '\n';
        }
    }

    inFile.close();
    outFile.close();

    return 0;
}


// Function to locate the index of the highest bit.
int HighBit(unsigned int a)
{
    int index = 1;
    
    while (a != 1)
    {
        if (a == 0)
        {
            index = -1;
            break;
        }
        else
        {
            a = a >> 1;
            index++;
        }
    }
    
    return index;
}

// Function used to mask bit to the left to 1
int NextHigh(unsigned int a, int b)
{
    int orNum, orHigh;
    
    if (b < 0)
    {
        orNum = 1 << 0;
    }
    else
    {
        orNum = 1 << b;
    }
    orHigh = a | orNum;
    return orHigh;
}
