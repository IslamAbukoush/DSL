# C Simple Programming Language

- [Syntax Keywords and Meanings](#syntax-keywords-and-meanings)
- [Instructions on Syntax](#instructions-on-syntax)
- [Program Examples](#program-examples)
- [Try Simple C by yourself](#try-simple-c-by-yourself)
  - [Interactive Mode](#interactive-mode)
  - [Executive Mode](#executive-mode)

C Simple is a minimalistic programming language developed for a university project. It shares key features with the C language while being designed to be super simple.

## Syntax Keywords and Meanings

| Keyword                | Meaning                                                       |
| ---------------------- | ------------------------------------------------------------- |
| `int`                  | Declare an integer variable.                                  |
| `float`                | Declare a floating-point variable.                            |
| `if`                   | Conditional statement.                                        |
| `while`                | Looping construct.                                            |
| `+`                    | Addition operator.                                            |
| `-`                    | subtraction operator.                                         |
| `*`                    | multiplication operator.                                      |
| `/`                    | Division operator.                                            |
| `^`                    | Exponentiation operator.                                      |
| `<`, `>`, `<=`, `>=`   | Comparison operators.                                         |
| `==`, `!=`             | Equality and inequality operators.                            |
| `and`                  | Logical AND operator.                                         |
| `or`                   | Logical OR operator.                                          |
| `+=`, `*=`, `/=`, `-=` | Shorthand assignment operators.                               |

## Instructions on Syntax

1. **Variable Declaration:**
   - Use `int` or `float` to declare variables, follow them by the vriable name, and you can optionally initialize thier value by following them with a `=` and then the value.
      ```c
      int x = 5;
      float y;
      int z = (3 + 5) / x + 1;
      ```
    - Note: All variables are considered global variables no matter where you declare them, so it wouldn't be a good idea to declare one inside of a loop, as it will throw an error if the loop runs more than one time.
      ```c
      int counter = 0;
      while(counter < 3) {
        int x = 3;
        counter += 1;
      }
      // "Error while interpreting: Variable 'x' has already been declared."
      ```
2. **Conditional Statements:**
   - Employ the `if` statement for conditional branching.
      ```c
      if(x > 5 and y < 3)
      {
         z = 3;
      }
      ```
   
3. **Loops:**
   - Use `while` for looping constructs.
     ```c
     int counter = 0;
     while(counter < 10)
     {
        print(counter);
        counter += 1;
     }
      // will output 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
     ```

4. **Arithmetic Operations:**
   - Employ `+`, `-`, `*`, `/`, and `^` for basic arithmetic.
     ```c
     int x = 3 ^ 2 + 3 * 2 * (5 - 2) / 6;
     ```

5. **Comparison and Logical Operators:**
   - Use `<`, `>`, `<=`, `>=`, `==`, `!=`, `and`, and `or` for comparisons.
     ```c
     int result = 5 >= 3;
     print(result) // will output '1' which means true
     result = 5 <= 3;
     print(result) // will output '0' which means false
     int result = 5 == 3;
     print(result) // will output '0' which means false
     result = 5 != 3;
     print(result) // will output '1' which means true
     ```

6. **Shorthand Assignment:**
   - Use `+=`, `*=`, `/=`, and `-=` for shorthand assignments.
     ```c
     float x = 0;
     x += 1;
     print(x); // will output '1'
     x *= 5;
     print(x); // will output '5'
     x /= 2;
     print(x); // will output '2.5'
     x -= 2;
     print(x); // will output '0.5'
     ```
     
7. **Print Function:**
   - Use `print()` for outputing variables or expressions.
     ```c
     int x = 10;
     print(x); // will output '10'
     print((2 + 4) * 5 - 4 * 6); // will output '6'
     print(1 > 3 or 1 > 0); // will output '1'
     ```
8. **Semicolons:**
   - Semicolons `;` are optional in Simple C, however, it is a good practice to write them after the end of each instruction, to avoid unexpected behaviour.


9. **Comments:**
   - You can write one line comments using two slashes `//` and end them with a new line, anything on the same line after the `//` will not be read by the lexer.
   ```c
     int x = 10;
     print(x); // This is a comment, you can write here whatever you want and it will not affect the program 
   ```
10. **User input:**
   - Use the special keyword `input` to take input from user.
   ```c
     int x = input + 10;
     print(x); // This will output whatever value you put and add 10 to it
   ```

## How to Write a Sample Program

Follow these steps to create a simple C Simple program:

1. Declare variables using `int` or `float`.
2. Use conditional statement `if` for decision-making.
3. Implement loops using the `while` construct for repetitive tasks.
4. Perform arithmetic operations and comparisons.
5. Utilize shorthand assignment operators for concise variable updates.

## Program Examples

### Program that calculates the area of a circle given the radius:

```c
float pi = 3.14;
float radius = 10;
float area = pi * radius ^ 2;
print(area) // will output '314'
```

### Program that calculates the factorial of a number:

```c
int input = 5;
int factorial = 1;

while(input > 1) {
   factorial *= input;
   input -= 1;
}
print(factorial) // will output '120'
```

### Program that prints the sum of positive numbers between -10 and 10:

```c
int n = 10;
int sum = 0;
int counter = -10;
while(counter <= n) {
  if(counter < 0) {
    sum += counter;
  }
  counter += 1;
}
print(sum); // will output 55
```

## Try Simple C by yourself

### Interactive Mode:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-username/c-simple.git
   cd c-simple
   ```

2. **Compile for Interactive Mode:**
   ```bash
   gcc -o app dynamic_array.c dynamic_array_float.c lexer.c parser.c interpreter.c interactive_mode.c
   ```

3. **Run the Interactive Mode:**
   ```bash
   ./app
   ```
   This opens the interactive mode where you can execute code line by line.

4. **Enter Code:**
   - Input your C Simple code line by line.
   - Press Enter to execute each line.

5. **Exit Interactive Mode:**
   - Type `0` to exit the interactive mode.

### Executive Mode:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-username/c-simple.git
   cd c-simple
   ```

2. **Compile for Executive Mode:**
   ```bash
   gcc -o app dynamic_array.c dynamic_array_float.c lexer.c parser.c interpreter.c execute.c
   ```
3. **Run the Executive Mode with a Code File:**
   ```bash
   ./app file_name.txt
   ```
   Replace `file_name.txt` with the name of your C Simple code file, and the file must be in the same directory as the other C files.

Follow the instructions above to either run it in interactive mode or save it to a file and execute it in executive mode.
