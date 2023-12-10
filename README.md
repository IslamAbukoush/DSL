# C Simple Programming Language

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

## Instructions on How to Write a Sample Program

1. **Variable Declaration:**
   - Use `int` or `float` to declare variables, follow them by the vriable name, and you can optionally initialize thier value by following them with a `=` and then the value.
      ```c
      int x = 5;
      float y;
      int z = (3 + 5) / x + 1;
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
     

## How to Write a Sample Program

Follow these steps to create a simple C Simple program:

1. Declare variables using `int` or `float`.
2. Use conditional statements (`if` and optional `else`) for decision-making.
3. Implement loops using the `while` construct for repetitive tasks.
4. Perform arithmetic operations and comparisons.
5. Utilize shorthand assignment operators for concise variable updates.

## Program Examples

### Error-Free Program

```c
float pi = 3.14;
float radius = 10;
float area = pi * radius ^ 2;
print(area) // will output '314'

int input = 5;
int factorial = 1;

while(input > 1) {
   factorial *= input;
   input -= 1;
}
print(factorial) // will output '120'
```
