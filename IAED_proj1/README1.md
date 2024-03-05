# Project 1 - IAED 2022/23

## Programming Language:
- C

## 1. Introduction

Interaction with the program should occur through a set of lines composed of a letter (command) and a number of arguments depending on the command to be executed.
It can be assumed that all input provided will respect the indicated types; for example, where a decimal integer value is expected, a letter will never be entered.
The possible commands are listed in the following table and indicate the operations to be performed.

| Command | Action |
|:---:|:---|
| __q__ | terminates the program |
| __c__ | adds and lists careers |
| __p__ | adds and lists stops |
| __l__ | adds and lists connections between stops |
| __i__ | lists interconnection nodes |

## 2. Problem Specification

Each __career__ (*left*, *right*, or *middle* in the figure) is characterized by a name composed of letters or decimal digits, a starting stop, and a destination stop.
The length of the name cannot exceed __20__ *bytes*.
Note that an accented character in *utf-8* uses more than one *byte*.
For example, `praça` has 5 letters but occupies 6 *bytes* (`char` in __C__).

A __stop__ (*A1*, *A2*, *B1*, ... in the figure) is characterized by a name and a location, latitude, and longitude, represented as real numbers in floating point.
In the name describing the stop, white characters may occur (spaces or horizontal tab `\t`).
In this case, the name is represented in quotes.
If it does not contain white characters, the name can be delimited by quotes or not.
The name never contains the quote character in its description.
The length of the name cannot exceed __50__ *bytes*.

Each __connection__ (*A1* to *B1*, *B1* to *C1*, ... in the figure) is characterized by a __career__, two __stops__ (origin and destination), a cost, and a duration.
To be a valid connection, it must represent an extension of the career, that is, the origin of the connection is the same stop as the terminal station of the career, or the destination of the connection is the same stop as the departure station of the career.
The cost and duration are represented as real numbers in floating point and must be printed with two decimal places (`%.2f`).

Note that circular careers can exist. When a connection is added with origin at the last stop of a career and with destination at the first stop of the career, then a cycle is formed. In these situations, the new connection is added at the end of the career.

There can be a maximum of __200__ careers, __10000__ stops, and __30000__ connections.

## 3. Input Data

The program should read the input data from the terminal command line.
No command line exceeds __BUFSIZ__ *bytes* (*8192 bytes* on most systems).

During program execution, instructions must be read from the terminal (*standard input*) in the form of a set of lines starting with a character, which is then called a command, followed by a number of pieces of information depending on the command to be executed; the command and each of the pieces of information are separated by at least one white character.

The available commands are described below. The characters `<` and `>` are used only in the command descriptions to indicate parameters.
Optional parameters are indicated between `[` and `]`.
Repetitions are indicated between `{` and `}`.
Each command always has all the parameters necessary for its correct execution.
The characters `...` indicate possible repetitions of a parameter.

Each command indicates a certain action, which is characterized in terms of input format, output format, and errors to return.

<u>If the command generates more than one error, only the first one should be indicated.</u>

- __q__ - terminates the program:
  - Input Format: `q`
  - Output Format: NOTHING

- __c__ - adds and lists careers:
  - Input Format: `c [ <career-name> [ inverse ] ]`
  - Output Format without arguments: `<career-name> <starting-stop> <destination-stop> <number-of-stops> <total-cost> <total-duration>`, in creation order. Stops are omitted for careers without connections.
  - Output Format with arguments: `<starting-stop> { , <stop> }`, in sequence of the route if a new career is not created.
  - Note: the `inverse` parameter implies printing the stops in reverse order and can be abbreviated to 3 characters, otherwise, nothing should be printed.
  - Errors:
    - `incorrect sort option.` if after the career name there is a word that is not `inverse` or one of its abbreviations up to 3 characters.

- __p__ - adds and lists stops:
  - Input Format: `p [ <stop-name> [ <latitude> <longitude> ] ]`
  - Output Format without arguments: `<stop-name>: <latitude> <longitude> <number-of-careers>` for each stop and in creation order, one per line where `<number-of-careers>` is the number of careers that stop at the stop.
  - Output Format with one argument: `<latitude> <longitude>`.
    - If the command is invoked with three arguments, a new stop is created without generating output data.
    - Notes:
      - The `<stop-name>` must be delimited by quotes if the name contains white characters (space or horizontal tab); the name cannot contain the quote character.
  - Errors:
    - `<stop-name>: stop already exists.` in the case of creating a stop and there is already a stop with the indicated name.
    - `<stop-name>: no such stop.` in the case of listing a stop and there is no stop with the indicated name.
    - Coordinates are printed in 16 positions with 12 decimal digits (`%16.12f`).

- __l__ - adds connections:
  - Input Format: `l <career-name> <origin-stop> <destination-stop> <cost> <duration>`
  - Output Format: NOTHING
  - Notes:
    - The `<stop-name>` must be delimited by quotes if the name contains white characters (space or horizontal tab); the name cannot contain the quote character.
  - Errors:
    - `<career-name>: no such line.` if there is no career with the indicated name.
    - `<stop-name>: no such stop.` in the case of not existing a stop with the indicated name, origin, or destination.
    - `link cannot be associated with bus line.` if the stops of the connection, origin, or destination, do not correspond to one of the ends of the career.
   

 - `negative cost or duration.` if the cost or duration are negative values.

- __i__ - lists intersections between careers:
  - Input Format: `i`
  - Output Format: `<stop-name> <number-of-careers>: <career-name> ...` for each stop where more than one line stops, one per line in the order of creation of the stops. The names of the careers should be listed alphabetically.

__You can only use library functions defined in `stdio.h`, `stdlib.h`, `ctype.h`, and `string.h`__

*Important note*: the use of the `goto` statement, the `extern` declaration, and the native C `qsort` function is not allowed, and none of these *names* should appear in your code.

## Examples of Command Usage

Consider that the careers from the figure above are defined.

### __Command `c`__

```text
c
```

The `c` command without arguments allows listing all careers in the system.

```text
c middle
```

The `c` command followed by an existing career in the system allows listing all stops on the career from origin to destination.

```text
c middle inverse
```

The same as the previous one, but stops are listed from destination to origin.

```text
c down
```

The `c` command followed by a non-existing career in the system allows creating the new career. In this case, there is nothing to show in the output.

### __Command `p`__

```text
p
```

The `p` command without arguments allows listing all stops in the system.

```text
p C1
```

The `p` command with one argument shows the latitude and longitude of the stop.

```text
p X1 2.5 45.6
```

The `p` command with three arguments creates a new stop.

### __Command `l`__

```text
l left X1 A1 0.5 2
```

The `l` command allows adding new connections to a career. In this case, if `X1` is the last stop of the career, then the new connection is inserted at the end and `A1` is the new last stop. Otherwise, if `A1` is the origin of the career, then the connection is inserted at the beginning of the career and `X1` becomes the new origin. If both conditions are met (insertion of a cycle in the career), then the connection is inserted at the end.

### Command __`i`__

```text
i
```

The `i` command allows listing stops that correspond to intersections of careers.

## 4. Compilation and Testing

The compiler to use is `gcc` with the following compilation options: `-O3 -Wall -Wextra -Werror -ansi -pedantic`. To compile the program, run the following command:

```text
$ gcc -O3 -Wall -Wextra -Werror -ansi -pedantic -o proj1 *.c
```

The program should write to *standard output* the responses to the commands presented in *standard input*. The responses are also lines of text formatted as defined earlier in this statement.
Pay attention to the number of spaces between elements of your output, as well as the absence of spaces at the end of each line. Make sure to scrupulously follow the given instructions.

See the examples of input and their respective output in the `public-tests/` folder.

The program should be executed as follows:

```text
$ ./proj1 < test.in > test.myout
```

Subsequently, you can compare your output (`*.myout`) with the expected output (`*.out`) using the `diff` command,

```text
$ diff test.out test.myout
```

To test your program, you can follow the steps above or use the `make` command in the `public-tests/` folder.
