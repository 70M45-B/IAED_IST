# Project 2 - IAED 2022/2023

## Programming Language:
- C

## 1. Introduction

The objective of this project is to develop, in the C language, additional functionalities to those created in the first project. Interaction with the program should occur through a set of lines composed of a letter (command) and a number of arguments dependent on the command to execute. It can be assumed that all input provided will respect the indicated types, for example, where a decimal integer value is expected, a letter will never be introduced. The commands from the first project are listed in the following table and maintain the operations to execute.

| Command | Action |
|:---:|:---|
| __q__ | ends the program |
| __c__ | adds and lists careers |
| __p__ | adds and lists stops |
| __l__ | adds connections between stops on a career |
| __i__ | lists intersection nodes |

In addition to the commands from the first project, the commands listed in the following table are added, as well as the operations to execute.

| Command | Action |
|:---:|:---|
| __r__ | removes a career |
| __e__ | eliminates a stop |
| __a__ | erases all data |

## 2. Problem Specification

There are no limits on the number of stops or connections, nor on the size of the names of careers or stops, so you should try to use memory as strictly necessary. There can be no global variables. To facilitate the entry of data, it can be assumed that each instruction does not exceed 65535 characters. If memory runs out, the program should terminate in a controlled manner, printing the message `No memory.` Before finishing, the program must release all reserved memory.

## 3. Input Data

During program execution, instructions must be read from the standard input in the form of a set of lines starting with a word, which is called a _command_, followed by a number of pieces of information dependent on the command to execute. Commands and arguments are separated by spaces or tabs.

Each command indicates a certain action, characterized in terms of input format, output format, and errors.
In the case of multiple errors for the same command, only the first of these errors should be returned.
The additional commands are:

* __r__ - removes a career:
    * Input format: `r <career-name>`
    * Output format: Nothing. Deletes the indicated career and all connections used by it.
    * Errors:
        * `<career-name>: no such line.` if there is no career with the indicated name.
* __e__ - eliminates a stop:
    * Input format: `e <stop-name>`
    * Output format: Deletes the indicated stop, causing all careers that stopped there to skip the stop but keeping the remaining route; the cost and duration result from the sum of the two routes collapsed by the elimination of the stop; if the stop is an end of the route of a career, the route is shortened.
    * Errors:
        * `<stop-name>: no such stop.` if there is no stop with the indicated name.

* __a__ - erases all data:
    * Input format: `a`
    * Output format: Frees all reserved memory from the beginning of execution (see _valgrind_).

__Only library functions defined in `stdio.h`, `stdlib.h`, `ctype.h`, and `string.h` can be used.__

*Important note*: the use of the `goto` statement, the `extern` declaration, and the native C `qsort` function is not allowed, and none of these *names* should appear in your code.

## Examples of Command Usage

Consider that the careers from the figure of the first project statement are defined.

### __Command `r`__

```text
r middle
```

The `r` command followed by the name of a career removes the indicated career and all its connections from the system.

### __Command `e`__

```text
e D2
```

The `e` command followed by an existing stop in the system removes the stop from the system. The connections of the careers with the stop to be eliminated must be updated.

### __Command `a`__

```text
a
```

The `a` command removes all stops, careers, and their respective connections from the system.

## 4. Compilation and Testing

The compiler to use is `gcc` with the following compilation options: `-O3 -Wall -Wextra -Werror -ansi -pedantic`. To compile the program, run the following command:

```text
$ gcc -O3 -Wall -Wextra -Werror -ansi -pedantic -o proj2 *.c
```

The program should write to *standard output* the responses to the commands presented in *standard input*. The responses are also lines of text formatted as defined earlier in this statement.
Pay attention to the number of spaces between elements of your output, as well as the absence of spaces at the end of each line. Make sure to scrupulously follow the given instructions.

See the examples of input and their respective output in the `public-tests/` folder.

The program should be executed as follows:

```text
$ ./proj2 < test.in > test.myout
```

Subsequently, you can compare your output (`*.myout`) with the expected output (`*.out`) using the `diff` command,

```text
$ diff test.out test.myout
```

To test your program, you can follow the steps above or use the `make` command in the `public-tests/` folder.
