# C Simple Programming Language

C Simple is a minimalistic programming language developed for a university project. It shares key features with the C language while being designed to be super simple.

## Syntax Keywords and Meanings

| Keyword                | Meaning                                                       |
| ---------------------- | ------------------------------------------------------------- |
| `int`                  | Declare an integer variable.                                  |
| `float`                | Declare a floating-point variable.                            |
| `if`                   | Conditional statement.                                        |
| `while`                | Looping construct.                                            |
| `+`, `-`, `*`          | Arithmetic operators (addition, subtraction, multiplication). |
| `/`                    | Division operator.                                            |
| `^`                    | Exponentiation operator.                                      |
| `<`, `>`, `<=`, `>=`   | Comparison operators.                                         |
| `==`, `!=`             | Equality and inequality operators.                            |
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
   - Employ the `if` and optional `else` keywords for conditional branching.

3. **Loops:**
   - Use `while` for looping constructs.

4. **Arithmetic Operations:**
   - Employ `+`, `-`, `*`, `/`, and `^` for basic arithmetic.

5. **Comparison and Logical Operators:**
   - Use `<`, `>`, `<=`, `>=`, `==`, `!=`, and `or` for comparisons.

6. **Shorthand Assignment:**
   - Use `+=`, `*=`, `/=`, and `-=` for shorthand assignments.

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
float calculateCircleArea(float radius) {
    float pi = 3.14;
    float area = pi * radius * radius;
    return area;
}

int main() {
    int x = 5;
    float result = 0.0;

    if (x > 0) {
        result = calculateCircleArea(x);
    } else {
        result = -1.0; // Error: Invalid radius for the circle
    }

    while (x < 10) {
        x += 2;
    }

    return 0;
}
```

### Program with Errors

```c
int main() {
    float y = 3.14;
    int count = 0;

    if (y >= 0) {
        // Error: 'count' used before initialization
        count += 1;
    } else {
        // Error: 'else' without a preceding 'if'
        y = y / count;
    }

    return 0;
}
```

Feel free to adapt the examples based on your specific language features and requirements. Additionally, update the error messages and comments for better clarity in your actual implementation.
