CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror
Brobank=bank.c bank.h

all: brobank
brobank: main.c $(Brobank)
	$(CC) $(CFLAGS) main.c $(Brobank) -o brobank

clean:
	del /Q brobank.exe