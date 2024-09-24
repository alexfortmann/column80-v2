/**
 * @file main.cpp
 * @brief A program to reformat text files to a specified column width.
 *
 * This program reads a text file and reformats its content so that each line
 * fits within a specified column width (default is 79 characters). The user
 * can specify a custom width and choose to overwrite the original file or 
 * write to a new file.
 *
 * Usage:
 *   ./80cols [Options] <input_filename> [output_filename]
 *
 * Options:
 *   -h, --help       Show help message and exit.
 *   -w WIDTH         Set the maximum column width (default is 79).
 *
 * @author Alex Fortmann
 * @date 2024-08-22
 * @version 2.0
 */

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    size_t columnWidth = 79;
    vector<string> files;

    if (argc < 2 || argc > 5) {
        cout << "Usage: column80 [Options] <input_filename> [output_filename]"
             << endl;
        return 1;
    }

    // Parse command-line arguments.
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        // Process custom width flag.
        if (arg == "-w") {
            // Check if the next argument exists and is a valid integer.
            if (i + 1 < argc) {
                try {
                    int tempWidth = stoi(argv[i + 1]);
                    if (tempWidth < 21) {
                        cerr << "Error: Width must be greater than 20."
                                  << endl;
                        return 1;
                    } else {
                        columnWidth = tempWidth;
                    }
                    ++i;  // Skip the width value in the next iteration.
                } catch (invalid_argument const &e) {
                    cerr << "Error: Invalid width provided after -w flag."
                         << endl;
                    return 1;
                } catch (out_of_range const &e) {
                    cerr << "Error: Width value provided "
                            "after -w is out of range."
                         << endl;
                    return 1;
                }
            } else {
                cerr << "Error: -w flag requires an integer argument."
                     << endl;
                return 1;
            }

        // If -h is specified, print the help message.
        } else if (arg == "-h" || arg == "--help") {
            cout << "Usage: column80 [Options] <input_filename> "
                         "[output_filename]\n"
                 << "\n"
                 << "Options:\n"
                 << "  -h, --help   Show this help message and exit\n"
                 << "  -w WIDTH     Set the maximum column width.\n"
                 << "               Default width is 79\n"
                 << "\n"
                 << "output_filename:\n"   
                 << "   Optional output filename.\n"
                 << "   If none provided, input is overwritten"
                 << endl;
            return 0;

        // Only add two files to the program.
        } else if (files.size() < 2) {
            files.push_back(argv[i]);

        // If more than two files or unrecognized argument, error.
        } else {
            cerr << "Error: Invalid arguments.\n"
                    "Usage: column80 [-w width] <input_filename> "
                    "[output_filename]"
                 << endl;
                 return 1;
        }
    }

    // If no files are specified, error.
    if (files.size() < 1) {
        cerr << "Error: No input file specified." << endl;
        return 1;
    }

    // Confirm overwrite to existing files.
    if (files.size() == 1) {
        string overwrite;
        while (overwrite != "Y" && overwrite != "n") {
            cout << "This will overwrite the existing file: " 
             << files[0] << endl;
            cout << "Do you want to proceed? (Y/n): " << endl;
            cin >> overwrite;

            if (overwrite == "n") {
                cout << "Ok, quitting program. File is unchanged." << endl;
                return 0;
            } else if (overwrite != "Y") {
            cout << "Invalid input. Please enter 'Y' or 'n'." << endl;
            }
        }
        
    }

    // Initialize variables for processing the file.
    ostringstream finalStream;
    ifstream toConvert;
    string line;
    int lineCount = 0;
    int overflowCount = 0;
    toConvert.open(files[0]);
    if (!toConvert.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return 1;
    }

    // Iterate through each line of the file.
    while (getline(toConvert, line)) {
        int charCount = 0;
        size_t spaceCount = 0;

        // Identify correct indentation to preserve.
        while (line[spaceCount] == ' ') {
            spaceCount++;
        }

        // Modify indentation if greater than columnWidth.
        while (spaceCount + 20 >= columnWidth) {
            if (spaceCount < 4) {
                spaceCount = 0;
            } 
            else {
                spaceCount -= 4;
            }
        }
        
        // Update/apply variables given the indentation.
        string spaceString(spaceCount, ' ');
        finalStream << spaceString;
        charCount = spaceCount;

        // For each word in the line, count width and break
        // lines as needed to match width requirement.
        istringstream iss(line);
        string word;
        bool firstWord = true;
        while (iss >> word) {
            if (charCount + word.length() + (firstWord ? 0 : 1) > columnWidth) {
                finalStream << endl;
                finalStream << spaceString;
                charCount = spaceCount;
                if (firstWord) {
                    overflowCount++;
                } else {
                    firstWord = true;
                }
                lineCount++;
            }
            
            if (!firstWord) {
                finalStream << " ";
                charCount++;
            }
            
            finalStream << word;
            charCount += word.length();
            firstWord = false; 
        }
        finalStream << endl;
    }

    toConvert.close();
    
    ofstream outFile;
    if (files.size() == 1) {
        // Overwrite the input file.
        outFile.open(files[0]);  
    } else {
        // Write to the specified output file.
        outFile.open(files[1]);  
    }

    if (!outFile.is_open()) {
        cerr << "Error: Could not open file for writing." << endl;
        return 1;
    }

    outFile << finalStream.str();
    outFile.close();
    cout << endl;

    // Print exit statistics.
    cout << lineCount << " line(s) created" << endl;
    if (overflowCount > 0) {
        cout << overflowCount << " long string(s) were greater than "
             << columnWidth
             << " columns in width." << endl;
    }

    return 0;
}