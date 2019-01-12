# Simple Compiler & Stack Machine (C++)

These two C++ applications can compile and run a simple dummy language. The compiler recursively compiles the language (.s) and creates an abstract stack machine code (.m). Then this abstract stack machine code is run by the stack machine.

The grammar of the simple language can be found in the PDF document.

## Getting Started

After compiling the both .cpp files you can run them on the test files provided.

### Prerequisites

You need to have GNU (Gnu is not Unix) Open Source compiler installed in order to compile the source files.

### Installing

If GNU (Gnu is not Unix) Open Source compiler is installed, you can run the application using the steps below.

First compile Compiler.cpp with g++ compiler.
```
g++ Compiler.cpp -o Compiler.o
```

Execute Compiler.o with an .s file. Output will be an .m file.
```
./Compiler.o prime.s
```

Then compile StackMachine.cpp with g++ compiler.
```
g++ StackMachine.cpp -o StackMachine.o
```

Execute StackMachine.o with an .m file. Output will be displayed on console.
```
./StackMachine.o prime.m
```

For prime.m, big numbers are displayed in scientific notation.
For all syntax errors, compiler gives an error and terminates compiling except the case that where a file does not have 'end'. 

## Deployment

You can just run the executable files on the input files.

## Built With

* [g++](https://www.cprogramming.com/g++.html) - The language used

## Authors

* **Mert Çotuk** - *Initial work* - [bmertcotuk](https://github.com/bmertcotuk)


