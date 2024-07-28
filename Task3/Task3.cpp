#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to compress the file using Run-Length Encoding
void compressFile(const string& inputFileName, const string& outputFileName)
{
    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName, ios::binary);

    if (!inputFile) 
    {
        cout << "Failed to open the input file." << endl;
        return;
    }
    if (!outputFile)
    {
        cout << "Failed to open the output file." << endl;
        return;
    }

    char currentChar, nextChar;
    int count = 1;

    if (inputFile.get(currentChar))
    {
        while (inputFile.get(nextChar)) 
        {
            if (nextChar == currentChar)
            {
                count++;
                if (count == 255)
                {
                    outputFile.put(currentChar);
                    outputFile.put(static_cast<char>(count));
                    count = 0;
                }
            }
            else 
            {
                outputFile.put(currentChar);
                outputFile.put(static_cast<char>(count));
                currentChar = nextChar;
                count = 1;
            }
        }
        outputFile.put(currentChar);
        outputFile.put(static_cast<char>(count));
    }

    inputFile.close();
    outputFile.close();
    cout << "File has been compressed successfully." << endl;
}

// Function to decompress the file using Run-Length Encoding
void decompressFile(const string& inputFileName, const string& outputFileName)
{
    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName, ios::binary);

    if (!inputFile)
    {
        cout << "Failed to open the input file." << endl;
        return;
    }
    if (!outputFile)
    {
        cout << "Failed to open the output file." << endl;
        return;
    }

    char currentChar;
    unsigned char count;

    while (inputFile.get(currentChar) && inputFile.get(reinterpret_cast<char&>(count))) 
    {
        for (int i = 0; i < count; ++i) 
        {
            outputFile.put(currentChar);
        }
    }

    inputFile.close();
    outputFile.close();
    cout << "File has been decompressed successfully." << endl;
}

void showMenu() 
{
    cout << "\nFile Compression Tool\n";
    cout << "1. Compress File\n";
    cout << "2. Decompress File\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    int choice;
    string inputFileName,
        outputFileName;

    while (true) 
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the name of the file to compress: ";
            cin >> inputFileName;
            cout << "Enter the name of the output file: ";
            cin >> outputFileName;
            compressFile(inputFileName, outputFileName);
            break;
        case 2:
            cout << "Enter the name of the file to decompress: ";
            cin >> inputFileName;
            cout << "Enter the name of the output file: ";
            cin >> outputFileName;
            decompressFile(inputFileName, outputFileName);
            break;
        case 3:
            cout << "Exiting the program..." << endl;
            return 0;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
