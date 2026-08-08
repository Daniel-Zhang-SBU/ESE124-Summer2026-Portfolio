# Artifact 2 — Mid-Course Program

Place the source code for one mid-course program in this folder. Choose work that demonstrates arrays, strings, functions, files, pointers, or another significant course concept.

## Program Purpose

The programs opens a file called grades.csv and computes the average of the student's scores that
is inside the file. The program will safely close after displaying the average of all the students.

## Files

-`midcourse_program.c`
-`grades.csv`

## Compile and Run

```bash
gcc -Wall -Wextra -std=c11 midcourse_program.c -o midcourse_program
./midcourse_program
```

## Sample Input and Output
Inputs
Check grades.csv.
The format is student name,score 1,score 2,score 3. No spaces allowed after comma
If the line in grades.csv is not this format, the program will automatically reject that line.

grades.csv 
Alice,88,92,79
Bob,73,65,81
Tom,74


Output 
Alice average 86.3
Bob average 73.0
Student Tom invalid line

## What I Learned

Design: I designed the program to read the student names and their grades from a CSV file one line at a time using fgets. Each line is then seperated using sscanf and they are checked to make sure the student has three valid scores before the scores are included in the average. Invalid lines are rejected.

The test cases I used are 2 valid lines inside grades.csv and invalid line. (See Sample Input and Output)

One bug I fixed was that orignially for my sscanf I had spaces after every comma for every input. However the grades.csv do not have any spaces so it sscanf kept failing and no grade averages were being computed despite having a valid test case. 


