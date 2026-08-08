#ifndef BROBANK_H
#define BROBANK_H

#include <time.h>

#define CAPACITY 64
#define CORRECT_PIN "589"       //define correct_pin as a string


typedef enum { TX_DEPOSIT, TX_WITHDRAW, TX_UNDO} TransactionType;
typedef struct { TransactionType type; double amount; int undone; time_t time;} Transaction;
typedef struct {Transaction data[CAPACITY]; int top; } Stack;
typedef struct {
    double init_balance; double balances[CAPACITY+1];
    int p_front, p_rear, p_count;
    Transaction history[CAPACITY]; int history_count;
} BroBank;

int handle_bank_locked(void);
void brobank_init(BroBank *bank);

void get_balance(BroBank *bank);
void display_banner(void);
void handle_bank_menu(BroBank *bank);
int get_choice(void);


int handle_deposit(BroBank *bank, Stack *s);
int handle_withdraw(BroBank *bank, Stack *s);
int brobankUndo(BroBank *bank, Stack *s);

void display_transactions(BroBank *bank);

//stack adt 
void stackInit(Stack *s);
int stackPush(Transaction tx, Stack *s);
int stackPop(Transaction *tx, Stack *s);
int stackIsEmpty(const Stack *s);
int stackIsFull(const Stack *s);

int interest_rate_calc(void);

void brobank_exit(BroBank *bank);


#endif