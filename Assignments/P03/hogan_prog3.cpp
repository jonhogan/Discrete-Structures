/**********************************************************************
 * Jonathan Hogan                                                     *
 * Dr. Stringfellow                                                   *
 * CMPS-2433-101                                                      *
 * November 18, 2020                                                 *
 *                                                                    *
 * Description:                                                       *
 *      Program to read from a user defined file, check the frequency *
 *      that letters appears and attempts to decipher the text using  *
 *      a shift (Caeser) cipher                                       *
 *                                                                    *
 * Files:                                                             *
 *       hogan_prog3.cpp                                              *
 *       input      (End user defined)                                *
 *       output.txt (End user defined)                                *
 *                                                                    *
 *********************************************************************/


#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**********************************************************************
*Function Index:
*	  string decrypt
*	  void letterFreq
*     void header
*     void openFiles
*     void setNumArray
**********************************************************************/

// Function used to decipher the text
string decrypt(string s, int key, char a[]);

// Fill an array with the letters from the Alphabet
void fillAlphaArray(char a[]);

// Function to find the frequency a letter appears
void letterFreq(string s, char a[], int n[]);

// Print output header
void header(ofstream& fout);

// Finds the highest frequency letter, and the number of times used
int highFreq(char a[], int n[]);

// Opens input and output files.
void openFiles(ifstream& fin, ofstream& fout);

// Sets the number array to 0 between frequency counts
void setNumArray(int n[]);

int main()
{
	char alphaArray[26];

	int numArray[26];
	string cipherText, testCaseString, decryptText;
	int testCase = 0, highCountLoc, encryptKey;
	int success = 0, failure = 0;
	char userResponse;
	bool correctResponse;

	bool decrypted = false;

	// Starting point to fill the alphaCount array

	ifstream fin;
	ofstream fout;

	openFiles(fin, fout);

	// Print header
	header(fout);

	// Read number of Test Cases from the input file
	getline(fin, testCaseString);

	// Convert the testCaseString to an Int
	stringstream convertString(testCaseString);
	convertString >> testCase;

	// Insert Letters into the first row of the alphaCount array
	fillAlphaArray(alphaArray);


	for (int i = 0; i < testCase; i++)
	{
		// Set the bool the run the while loop after an attempted
		// decryption
		correctResponse = false;
		getline(fin, cipherText, '#');

		// Set numArray elements to 0 to ensure accurate count
		setNumArray(numArray);

		letterFreq(cipherText, alphaArray, numArray);
		highCountLoc = highFreq(alphaArray, numArray);
		encryptKey = alphaArray[highCountLoc] - alphaArray[4];

		// Pass to the decypt fuction to attempt to decrypt the text
		decryptText = decrypt(cipherText, encryptKey, alphaArray);

		// Print to console and file
		cout << '\n' << decryptText;
		fout << '\n' << decryptText;

		cout << "\n\n";
		fout << "\n\n";
		
		// Ask user if the file decrypted with a control for incorrect
		// input at the keyboard
		while (correctResponse == false)
		{
			cout << "Did the message decode correctly? (Y/N): ";
			cin >> userResponse;

			if (userResponse == 'y' || userResponse == 'Y')
			{
				success++;
				correctResponse = true;
			}
			else if (userResponse == 'n' || userResponse == 'N')
			{
				failure++;
				correctResponse = true;
			}
			else
				cout << "\n\nInvalid input, please use Y or N.\n\n";
		}
	}

	cout << "Attempts to decode: " << testCase << "\nSuccessful "
		 <<"Attempts: " << success << "\nFailed Attempts: " << failure
		 << "\n\n";
	fout << "Attempts to decode: " << testCase << "\nSuccessful "
		 << "Attempts: " << success << "\nFailed Attempts: " << failure
		 << "\n\n";

	fin.close();
	fout.close();

	return 0;
}

/**********************************************************************
* Purpose: Use the key from the encrypted text to attempt to decript
*          the ciphered text
*
* Recieves:
*		string
*		int
*		char array
*
* Scope Variables:
*		string decryptedText
*		int remainder
*       int size
*
* Returns: Void
**********************************************************************/
string decrypt(string s, int key, char a[])
{
	string decryptedText;
	// get the size of the ciphered string
	int size = s.length();
	
	
	// Prints out the deciphered text
	for (int i = 0; i < size; i++)
	{
		// Handles non-Alpha chars
		if (s[i] < 65 || s[i]> 91 )
		{
			decryptedText += s[i];
		}
		else
		{
			decryptedText += char(((65 + s[i]-key) % 26)+65);
		}
	}

	return decryptedText;
}

/**********************************************************************
* Purpose: Fill an array with the letters from the Alphabet
*
* Recieves:
*		char array
*		char
*
* Scope Variables:
*		char letter
*
* Returns: Void
**********************************************************************/
void fillAlphaArray(char a[])
{
	char letter = 'A';

	for (int i = 0; i < 26; i++)
	{
		a[i] = letter;
		letter++;
	}
}

/**********************************************************************
* Purpose: Prints a header to the output file
*
* Recieves:
*		ofstream
*
* Scope Variables:
*
* Returns: Void
**********************************************************************/
void header(ofstream& fout)
{
	fout << "Jonathan Hogan\nDr.Stringfellow\nCMPS - 2433 - 101\n"
		<< "November 18, 2020\n\n\n"
	    << "Program to read from a user defined file, check the "
		<< "frequency\nthat letters appears and attempts to decipher"
		<< " the text using a shift (Caeser) cipher\n\n\n\n";


}

/**********************************************************************
* Purpose: Compares the letters in the encrypted text to the
*          alphaArray, increments the elements in the numArray
*          to get a frequency of the letters used.
*
* Recieves:
*		string
*		char array
*		int array
*
* Scope Variables:
*		int size
*
* Returns: Void
**********************************************************************/
void letterFreq(string s, char a[], int n[])
{
	// get the size of the ciphered string
	int size = s.length();
	
	// Compare the letters in the ciphered text to alphaArray
	// Increments the corresponding element of numArray
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (s[i] == a[j])
			{
				n[j]++;
			}
		}
	}
}

/**********************************************************************
* Purpose: Searches the numArray to find the highest frequency count
*          prints the letter, and the number of times used.
*
* Recieves:
*		char array
*		int array
*
* Scope Variables:
*		int hFreq
*		int loc
*
* Returns: int
**********************************************************************/
int highFreq(char a[], int n[])
{
	int hFreq, loc;

	// Set hFreq and loc to the first element
	hFreq = n[0];
	loc = 0;

	for (int i = 1; i < 26; i++)
	{
		if (hFreq < n[i])
		{
			hFreq = n[i];
			loc = i;
		}
	}

	//cout << "Highest frequency letter is " << a[loc] << ", used "
	//	<< hFreq << " times.\n\n";

	return loc;
}

/**********************************************************************
* Purpose: Ask user for input and out put files
*
* Receives:
*      ifstream (In file stream set in main())
*      ofstream (Out file stream set in main())
*
* Scope Variables:
*      char finName
*      char oufFileName
*
* Returns: Void
**********************************************************************/
void openFiles(ifstream& fin, ofstream& fout)
{
	char finName[40];
	char foutName[40];

	cout << "Enter the input file name: ";
	cin >> finName;

	//Opens input file
	fin.open(finName);

	cout << "Enter the output file name: ";
	cin >> foutName;

	//open output file
	fout.open(foutName);
}

/**********************************************************************
* Purpose: Sets the NumArray from Main to 0. This clears it for each
*		   run of the letterFreq function
*
* Receives:
*      int array
*
* Scope Variables:
*      
*
* Returns: Void
**********************************************************************/
void setNumArray(int n[])
{
	for (int i = 0; i < 26; i++)
		n[i] = 0;
}