# Column80 v2

Column80 is a command-line utility that automatically reformats text files to ensure each line adheres to a specified column width (character limit), helping to comply with various style guides. This tool is particularly useful for preparing text files that will be viewed in environments without automatic word wrapping, such as command-line editors or simple text viewers. While it is primarily designed for non-Markdown README files, Column80 can be used to format any text file.

## Features

- Reformat text files to a specified column width.
- Preserve indentation and word boundaries.
- Overwrite the input file or output to a new file.
- Configurable column width with a default of 79 characters.

## Requirements

- A C++ compiler (e.g., `clang++` or `g++`).
- A Unix-like operating system (Linux, macOS, etc.).

## Install

### Building from Source

To build Column80 from source, follow these steps from the command line:

1. Clone the repository:

   ```bash
   git clone https://github.com/alexfortmann/column80-v2.git
   cd column80-v2
   ```

2. Compile and install the program system-wide, using the provided Makefile:
    
    ```bash
    sudo make install
    ```

This will install the column80 binary to /usr/local/bin/.

Most likely /usr/local/bin is already in your PATH. If not, you’ll need to add it to your .bashrc, .bash_profile, or .zshrc file (depending on your shell).

## Uninstall

To uninstall Column80 from your system, run:

```bash
sudo make uninstall
```

This will remove the column80 binary from /usr/local/bin/.

## Usage

To use Column80, run the following command:

```bash
column80 [Options] <input_filename> [output_filename]
```

### Options

- `-h`, `--help`: Display the help message and exit.
- `-w WIDTH`: Set the maximum column width. The default width is 79, which aligns with Python's PEP 8 style guide (79 characters) and is also compatible with common C++ style guides (typically 80 characters). The minimum custom width is 21 columns.

## Recommended Use Case: 

When working on your README files in an IDE, it's recommended to enable word wrapping. This allows you to write and edit your text more easily, as the content will visually fit within the editor window without manually inserting line breaks. 

In the editor, the resulting text will look like this (note that line numbers are misleading due to the word wrapping):

<img width="626" alt="Before" src="https://github.com/user-attachments/assets/e15170e6-5fbf-4af4-b887-17148178ab6b">


Once you're done writing your document, save the file as-is. Then, run `column80` to automatically insert line breaks, ensuring that your README file adheres to the specified column width:

<img width="628" alt="After" src="https://github.com/user-attachments/assets/259e0a31-b0fc-45f7-bdc0-09200b59f311">


### Examples

Reformat a text file with the default column width of 79 characters:

```bash
column80 myfile.txt
```

Reformat a text file to a column width of 60 characters and save the result to a new file:

```bash
column80 -w 60 myfile.txt newfile.txt
```
Display the help message:

```bash
column80 -h
```
## Special Cases

### Long strings

Long strings that exceed the specified column width will not be broken into separate lines. This design choice ensures the integrity of URLs and similar content.

### Long Indentation (rare)

Indentation is preserved in the output file. However, if the indentation exceeds the specified column width, it will be adjusted to be 20 characters less than the maximum column width.


## License

There is currently no license for this project. But I am planning to update it with one in the future.

## Author

Written by Alex Fortmann.

Version 2.0 - Copyright (c) 2024 Alex Fortmann. All rights reserved.
