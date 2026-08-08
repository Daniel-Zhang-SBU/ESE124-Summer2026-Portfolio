#include <string.h>
#include <stdio.h>
#include <time.h>
#include "bank.h"

int handle_bank_locked(void)
{
    int pin;
    char input[10];
    while(1)
    {
        printf("Enter your 3-digit PIN number\n");
        printf("Type \"exit\" to exit\n");
        scanf("%9s", input);

        if(strcmp(input,CORRECT_PIN) == 0)
        {
            return 1;
        }
        else if(strcmp(input,"exit") == 0)
        {
            return 0;
        }
        else
        {
            printf("Incorrect PIN or Invalid Input\n");
        }
    }
    return 0;   //safe exit incase something went wrong
}

void brobank_init(BroBank *bank) 
{
    if (!bank) return; 
    memset(bank, 0, sizeof *bank); 
    bank->p_rear = -1; 
}

void get_balance(BroBank *bank)
{
    FILE *fp = fopen("balance.txt", "r");
    if(fp == NULL)
    {
        printf("Failed to read balance.txt");
        return;
    }

    fscanf(fp, "%lf", &bank->balances[0]);

    fclose(fp);
}

void handle_bank_menu(BroBank *bank)
{
    printf("Account balance: %.2lf\n", bank->balances[bank->history_count]);
    printf("[1]Deposit\n [2]Withdraw\n [3]Undo\n [4]Transactions\n [5]Interest Rate Calculator\n [6]Quit\n");
    printf("Choose a numbered option:");
}

int get_choice(void)
{
    int option;

    while (1)
    {
        if (scanf("%d", &option) != 1)      //check that the input is not a character
        {
            printf("Invalid choice\n");
            scanf("%*s");               //clear the previous input
            continue;
        }

        if (option >= 1 && option <= 6)     //check that it is within 1 and 6
        {
            return option;
        }
        printf("Invalid choice\n");
    }
}

int handle_deposit(BroBank *bank, Stack *s)
{
    double amount;
    while(1)
    {
        printf("Enter Deposit amount:");
        if(scanf("%.2lf", &amount) != 1)            //check that the input is not a character
        {
            scanf("%*s");
            printf("Invalid deposit amount\n");
            continue;
        }
        if(amount > 0)
        {
            bank->balances[bank->history_count + 1] = bank->balances[bank->history_count] + amount;
            break;
        }
        else 
        {
        printf("Invalid Deposit Amount\n");
        }
    }
    Transaction tx;
    tx.type = TX_DEPOSIT;
    tx.amount = amount;
    tx.undone = 0;
    tx.time = time(NULL);
    if(bank->history_count < CAPACITY)
    {
    bank->history[bank->history_count] = tx;
    bank->history_count++;
    }
    return stackPush(tx, s);
}

int handle_withdraw(BroBank *bank, Stack *s)
{
    double amount;
    while(1)
    {
        printf("Enter Withdraw amount:");       //check that the input is not a character
        if(scanf("%.2lf", &amount) != 1)
        {
            scanf("%*s");
            printf("Invalid withdraw amount\n");
            continue;
        }
        if(amount  > 0 && amount <= bank->balances[bank->history_count])
        {
        bank->balances[bank->history_count + 1] = bank->balances[bank->history_count] - amount;
        break;
        }
        else
        {
        printf("Invalid withdraw amount\n");
        }
    }
    Transaction tx;
    tx.type = TX_WITHDRAW;
    tx.amount = amount;
    tx.undone = 0;
    tx.time = time(NULL);
    if(bank->history_count < CAPACITY)
    {
    bank->history[bank->history_count] = tx;
    bank->history_count++;
    }
    return stackPush(tx, s);
}

//stacking functions
void stackInit(Stack *s) { s->top = -1; }
int stackIsEmpty(const Stack *s) { return s->top < 0; }
int stackIsFull(const Stack *s) { return s->top == CAPACITY - 1; }

int stackPush(Transaction tx, Stack *s) 
{/* TODO: reject a full stack, then add value at the top. */
    if(s == NULL || stackIsFull(s))
    {
      return 0;  
    }
    s->top++;      //move pointer s in the stack to the next valid position in stack
    s->data[s->top] = tx;        //store the value in the stack
    return 1;   
}

int stackPop(Transaction *tx, Stack *s) 
{/* TODO: reject an empty stack, then remove the top value. */
    if(s == NULL || stackIsEmpty(s) || tx == NULL)
    {
      return 0;  
    }       
    *tx = s->data[s->top];
    s->top--;
    return 1;
}

int brobankUndo(BroBank *bank, Stack *s) 
{ /* TODO: reverse most recent successful transaction. */
    Transaction tx;

    if(bank == NULL || s == NULL)
    {
        return 0; 
    }
    if(stackPop(&tx, s) == 0)
    {
        return 0;               //popping stack failed
    }
    bank->history[bank->history_count - 1].undone = 1;      //update the undone count
    if(tx.type == TX_DEPOSIT)
    {
    bank->balances[bank->history_count] = bank->balances[bank->history_count - 1];
    }
    else if(tx.type == TX_WITHDRAW)
    {   
    bank->balances[bank->history_count] = bank->balances[bank->history_count - 1];
    }
    return 1;
}

void display_transactions(BroBank *bank)
{
    printf("Type \t amount \t balance \t time");
    for(int i = 0; i < bank->history_count; i++)
    {
        if(bank->history[i].type == TX_DEPOSIT)
    {
        printf("Deposit\t");
    }
    else if(bank->history[i].type == TX_WITHDRAW)
    {
        printf("Withdraw\t");
    }
        printf("%.2lf %.2lf %s\n", bank->history[i].amount, bank->balances, 
                             ctime(&bank->history[i].time));
    }
}