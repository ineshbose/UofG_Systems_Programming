# Lab 1

### File copy character at a time
Create a file named `repeat.c` that prints out every character that is read from standard input, compile it and test it.

### File copy line at a time
Create a file named `lfcopy.c` that copies standard input to standard output a line at a time using `readline` and `writeline` (source code provided), compile it and test it.

### Line Counting
Write a program for counting lines on standard input reading a character at a time. Write a second program that counts lines using `readline` and prints the result on standard output. Compile and test both programs.

### Real Word Counting
Write a program that counts words, where a word is defined as a sequence of characters that are all letters - i.e. no digits, punctuation marks, white space, control characters, etc. Create a file named `wcount.c` that counts the number of words using this definition, and prints the results on standard output. Compile and test the program.

### Collapsing White Space
Write a program that copies standard input to standard output, converting all sequences of white space (as defined by `isspace()`) to a single space. Since '`\n`' is considered white space by `isspace()`, be sure to write a newline character to standard output before program terminates.