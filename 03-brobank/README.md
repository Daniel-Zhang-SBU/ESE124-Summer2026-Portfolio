# Artifact 3 — BroBank Showcase

Place the completed BroBank source and header files in this folder. Include files such as `main.c`, `bank.c`, and `bank.h` when they are part of your design.

## Required Files

- `main.c`
- `bank.c`
- `bank.h`
- `sample_input.txt`
- `sample_output.txt`
- `balance.txt`
- `Makefile`
- Any additional `.c` or `.h` files used by your program

The automatic check compiles every `.c` file directly inside this folder and confirms that the program runs and produces output. `sample_output.txt` documents the expected demonstration for a reviewer. Do not include menu prompts or other text in `sample_input.txt`; it should contain only the input a user would type.

## Program Purpose

Brobank features a 3 digit pin lock to access your account, actions deposits, withdraws, undos, and a interest rate calculator. Brobank will update your bank balance with every deposit, withdraw, and undo and additionally will save your balance everytime you quit the program. Brobank will also output an txt file with all your transactions history including the ones you undid. 


## File Organization

Bank.h is the header file that contains all the helper function names.
Bank.c is the source file that contains all the helper function's function.
Main.c is where the brobank is located and it calls on the helper functions to complete tasks
that were asked by the user.

## Compile and Run

```bash
gcc -Wall -Wextra -std=c11 main.c bank.c -o brobank
./brobank
```

Adjust the command if your filenames are different.

## Sample Session

Add `sample_input.txt` and `sample_output.txt`, or show a representative session here.

## Design and Testing

My main design choice was to first create a lock, then to add the functions for the brobank that we worked on throughout the semester. For example in week 1, we created the brobank banner and I added a similar code implement it. Then for the brobank functionality I tried to incorporate all the functions we tried like deposit, withdraw, interest calculator, and undo as well. 

Some important test cases I made sure to add in my code was the edge cases. For example when entering the pin number, I made the program return an error if you typed in characters. Then the program safely cleared the previous input and waited for the next input. This is also seen when inputting the amount to deposit, withdraw, and in the interest calculator.

One meaningful bug that I fixed was the undo feature. I spent the most time doing that. Originally the undo feature only reverted your previous transaction and it did not show up in the transaction. I later realized that this was really confusing for the reader so I included it. 

## Showcase Purpose

Copy your own completed BroBank work into this folder. Do not combine code from classmates and do not create a second BroBank project. BroBank functionality is graded under the Final Project. In this portfolio, it is showcased and evaluated for organization, documentation, testing evidence, reflection, and professional presentation.
