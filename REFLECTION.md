# Course Reflection

## Growth

The programming skill that improved the most for me during this course was how to read code and understand it. For example during structs I was still lost on how to use pointers correctly. However after doing brobank for a long time I understood how to use it intuitively. Since many of the functions called a pointer to that struct, I had the address of the struct so I needed '->' whereas another function created a new struct but since I have this actual struct and in this location I can access the items inside that i need by using '.'.

## Challenge

One concept that remains difficult for me is memory allocation. I just can't seem to grasp the idea on how to allocate memory and how that memory works. I tried to do memory allocation for the brobank as a practice but I saw that we used memset(memory set I believe is the meaning) so i didnt use malloc to allocate memory. In the future I will try to use malloc as much as possible to understand when dynamic memory is necessary by doing more examples of when a program will be more efficient with dynamic memory.

## Debugging

One important bug that I fixed was how the makefile clean worked. Originally I had rm -f brobank.exe however everytime i ran it, it kept syaing it could not find the file specified. I diagnosed it by searching up online why rm -f not work in windows. From the search I found out that rm is a Unix/Linux command that does not always exist in windows command prompt and that instead del should be used for deleting files.

## Next Goal

One goal that I have is to be able to program faster and to understand code faster. As of right now I am still slow on reading code and on how that code effects the rest of the code. I want to be able to read a function and the whole program and understand how that function works and if there is any way for it to be more efficient. 

