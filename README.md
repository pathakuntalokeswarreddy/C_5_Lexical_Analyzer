# Lexical Analyzer in C

## Overview

This project is a simple **Lexical Analyzer implemented in C**.

The main purpose of the project is to read a C source file and break the program into meaningful units called **tokens**. Each token is identified and classified based on its type, along with the line number.

This project was developed to understand how the **lexical analysis phase of a compiler** works and to get practical experience with file handling, strings, character processing, and pattern recognition in C.

## What is a Lexical Analyzer?

A lexical analyzer is the first stage of a compiler.

It reads the source code character by character and groups the characters into tokens such as:

* Preprocessor directives
* Header files
* Single-line and Multi-line Comments
* Keywords
* Identifiers
* Numeric constants
* Character constants
* String literals
* Operators
* Symbols

## Features

The analyzer currently recognizes:

* C keywords
* Identifiers
* Numeric constants
* Character constants
* String literals
* Operators
* compound operators
* Parentheses, braces and brackets
* Single-line comments
* Multi-line comments
* Preprocessor directives
* Header files
* Line numbers

The output is displayed in a table containing:

```text
Line No    Token    Token Type
```
**saves the tokenized data in a .txt file**

## Example

### Input

```c
#include <stdio.h>
int main()
{
    int sum = num1 + num2;
    return 0;
}

```

### Output

```text
---------------------------------------------
Line No    Token           Token Type
---------------------------------------------
1          #include        : PRE-PROCESSOR
1          <stdio.h>       : HEADER
2          int             : RESERVED KEYWORD
2          main            : IDENTIFIER
2          (               : OPEN_BRACE
2          )               : CLOSE_BRACE
3          {               : OPEN_BRACE
4          int             : RESERVED KEYWORD
4          sum             : IDENTIFIER
4          =               : OPERATOR
4          num1            : IDENTIFIER
4          +               : OPERATOR
4          num2            : IDENTIFIER
4          ;               : TERMINATING OPERATOR
5          return          : NON RESERVED KEYWORD
5          0               : NUMERIC CONSTANT
5          ;               : TERMINATING OPERATOR
6          }               : CLOSE_BRACE
---------------------------------------------
```

## Project Structure

The project is organized into separate files to keep the code easier to understand and maintain.

```text
Lexical-Analyzer/
│
├── main.c
├── header.h
├── main_scan.c
├── preprocessor_scan.c
├── word_scan.c
├── scan_functions.c
└── README.md
```

## How It Works

The analyzer reads the source file and processes it character by character.

The general flow is:

```text
Source Code
     ↓
Read Character
     ↓
Identify Lexeme
     ↓
Classify Token
     ↓
Store / Display Token Information
     ↓
Read Next Character
```

Special handling is provided for cases such as:

* Comments
* Strings
* Character literals
* Multi-character operators(compound operators like '==')
* Preprocessor directives
* Header files

For example, when the analyzer encounters `==`, it checks the next character before deciding the token type instead of treating the two `=` characters as separate operators.

## Concepts Used

This project helped me practice several C programming concepts:

* Tokenization
* Pattern matching
* File handling
* Structures
* Strings
* Pointers
* Functions
* Character handling
* Conditional statements
* Loops
* Preprocessor directives

## Limitations

This is an educational lexical analyzer and is **not intended to be a complete replacement for a compiler's lexer**.

Some advanced C language features and preprocessing rules may not be fully supported. The project focuses mainly on understanding the basic concepts behind lexical analysis and implementing them from scratch in C.

## Future Improvements

Some possible improvements are:

* Support more C lexical rules
* Improve error detection and reporting
* Handle escape sequences more completely
* Improve preprocessing directive handling
* Add support for hexadecimal, octal, and floating-point constants
* Improve token classification
* Provide better handling of invalid tokens

## Learning Outcome

Working on this project helped me understand how source code is processed before it reaches later stages of compilation.

Instead of treating a C program as just a sequence of characters, the project helped me understand how those characters are grouped into **lexemes and tokens**, which form the foundation for syntax analysis and the later stages of a compiler.

## Author

**Lokeswar Reddy Pathakunta**

This project was developed as part of my learning in **C programming**.
