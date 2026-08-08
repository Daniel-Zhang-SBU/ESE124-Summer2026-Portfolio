# Artifact 1 — Early Program

Place the source code for one early-course program in this folder.

## Program Purpose

 This program displays and computes the approximation of 1/(1-x) using taylor series. You can input a x value and the number of terms you want to use. 

## Files

-`early_program.c`

## Compile and Run

```bash
gcc -Wall -Wextra -std=c11 early_program.c -o early_program
./early_program
```

Replace the command with the correct filenames for your program.

## Sample Input and Output
x is -0.3, number of terms is 4.

The actual value is: 0.769
The Taylor approximation is: 0.763

## What I Learned

I learned how to create a recursive property using the taylor series for 1/(1-x). One difficulty I had was how to change the eponents as the taylor series for 1/(1-x) is 1 + x + x^2 + x^3 + ... . The base, x stayed the same, but the exponent changed from 0 to 1 to 2... . I solved this by using a for loop. One bug I fixed was the definiton of x. Originally I had x as an int but in C, an int is an integer, so x could never have the decimals and I fixed this by changing x from an Int to a double. 

