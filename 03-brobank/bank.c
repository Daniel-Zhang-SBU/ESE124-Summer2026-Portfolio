#include <string.h>
#include <stdio.h>
#include <time.h>
#include "bank.h"

int handle_bank_locked(void)
{
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
            printf("Incorrect PIN or Invalid Input\n\n");
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

void display_banner(void)
{
    printf("+-------------------+\n");
    printf("|Welcome to BroBank!|\n");
    printf("|Author:Daniel Zhang|\n");
    printf("|Version: 1.0       |\n");
    printf("|Last update: 8/8/26|\n");
    printf("+-------------------+\n");
}

void get_balance(BroBank *bank)
{
    FILE *fp = fopen("balance.txt", "r");
    if(fp == NULL)
    {
        printf("Failed to read balance.txt");
        return;
    }

    fscanf(fp, "%lf", &bank->init_balance);

    fclose(fp);
}

void handle_bank_menu(BroBank *bank)
{
    if(bank->history_count == 0)
    {
        printf("\nAccount balance: %.2lf\n", bank->init_balance);
    }
    else
    {
        printf("Account balance: %.2lf\n", bank->balances[bank->history_count - 1]);
    }
    printf("[1]Deposit\n[2]Withdraw\n[3]Undo\n[4]Transactions\n[5]Interest Rate Calculator\n[6]Quit\n");
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
    if(bank == NULL || s == NULL || bank->history_count >= CAPACITY)
    {
        return 0;
    }
    double amount;
    while(1)
    {
        printf("Enter Deposit amount:");
        if(scanf("%lf", &amount) != 1)            //check that the input is not a character
        {
            scanf("%*s");
            printf("Invalid deposit amount\n");
            continue;
        }
        if(amount > 0)
        {
            if(bank->history_count == 0)
            {
                bank->balances[bank->history_count] = bank->init_balance + amount;
                break;
            }
            else
            {
            bank->balances[bank->history_count] = bank->balances[bank->history_count - 1] + amount;
            break;
            }
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
    if(bank == NULL || s == NULL || bank->history_count >= CAPACITY)
    {
        return 0;
    }
    double amount;
    while(1)
    {
        printf("Enter Withdraw amount:");       //check that the input is not a character
        if(scanf("%lf", &amount) != 1)
        {
            scanf("%*s");
            printf("Invalid withdraw amount\n");
            continue;
        }
        if(bank->history_count == 0)
        {
            if(amount > 0 && amount <= bank->init_balance)
            {
                bank->balances[0] = bank->init_balance - amount;
                break;
            }
            else
            printf("Invalid withdraw amount\n");
        }
        else
        {
            if(amount > 0 && amount <= bank->balances[bank->history_count - 1])
            {
                bank->balances[bank->history_count] =
                bank->balances[bank->history_count - 1] - amount;
                break;
            }
            else
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
    Transaction undo_tx;
    if(bank == NULL || s == NULL || bank->history_count == 0 || bank->history_count >= CAPACITY)
    {
        return 0; 
    }
    if(stackPop(&tx, s) == 0)
    {
        return 0;               //popping stack failed
    }
    if(tx.type == TX_DEPOSIT)
    {
        bank->balances[bank->history_count] =
        bank->balances[bank->history_count - 1] - tx.amount;
    }
    else if(tx.type == TX_WITHDRAW)
    {
        bank->balances[bank->history_count] =
        bank->balances[bank->history_count - 1] + tx.amount;
    }

    //mark the most recent transaction as undone
    bank->history[bank->history_count - 1].undone = 1;

    //create a transaction that shows you undid your previous action
    undo_tx.type = TX_UNDO;
    undo_tx.amount = tx.amount;
    undo_tx.undone = 0;
    undo_tx.time = time(NULL);

    bank->history[bank->history_count] = undo_tx;
    bank->history_count++;
    return 1;
}

void display_transactions(BroBank *bank)
{
    printf("Type \t\t amount \t balance \t time\n");
    for(int i = 0; i < bank->history_count; i++)
    {
        if(bank->history[i].type == TX_DEPOSIT)
        {
            printf("Deposit\t\t ");
        }
        else if(bank->history[i].type == TX_WITHDRAW)
        {
            printf("Withdraw\t ");
        }
        else if(bank->history[i].type == TX_UNDO)
        {
            printf("Undo\t\t ");
        }
        printf("%.2lf \t\t %.2lf \t %s \n", bank->history[i].amount, bank->balances[i], 
                                   ctime(&bank->history[i].time));
    }
}

int interest_rate_calc(void)
{
    double balance;
    double rate;
    int years = 1;
    int limit;
    while(1)
    {
        printf("Input the amount of money you start of with:");
        if (scanf("%lf", &balance) != 1)      //check that the input is not a character
        {
            printf("Invalid starting money, has to be digits\n");
            scanf("%*s");               //clear the previous input
            continue;
        }
        else if(balance > 0)
        {
            break;
        }
        else
        printf("Invalid starting money");
    }
    while(1)
    {
        printf("Input the interest in percent:");
        if (scanf("%lf", &rate) != 1)      //check that the input is not a character
        {
            printf("Invalid interest rate, has to be a number \n");
            scanf("%*s");               //clear the previous input
            continue;
        }
        else if(rate > 0 && rate < 100)
        {
            rate = rate / 100;
            break;
        }
        else
        printf("Invalid percent");
    }
    while(1)
    {
        printf("Input the number of years:");
        if (scanf("%d", &limit) != 1)      //check that the input is not a character
        {
            printf("Invalid amount of years\n");
            scanf("%*s");               //clear the previous input
            continue;
        }
        else if(limit> 0)
        {
            break;
        }
        else
        printf("Invalid amount of years");
    }
    while(years <= limit)
    {
        balance = balance + balance * rate; 
        printf("Year %d: %.2f\n", years, balance);
        ++years;
    }
    return 1;       //success exit.
}

void brobank_exit(BroBank *bank)
{
    FILE *fp1 = fopen("Transactions.txt", "a");
    if(fp1 == NULL)
    {
        printf("Failed to create transactions.txt");
        return;
    }
    FILE *fp2 = fopen("balance.txt", "w");
    if(fp2 == NULL)
    {
        printf("Failed to open balance.txt");
        return;
    }

    //save balance
    if(bank->history_count == 0)
    {   
        fprintf(fp2, "%.2lf", bank->init_balance);
    }   
    else
    fprintf(fp2, "%.2lf", bank->balances[bank->history_count - 1]);

    //save transactions
    fprintf(fp1, "Type \t\t amount \t balance \t time\n");
    for(int i = 0; i < bank->history_count; i++)
    {
        if(bank->history[i].type == TX_DEPOSIT)
        {
            fprintf(fp1, "Deposit\t\t ");
        }
        else if(bank->history[i].type == TX_WITHDRAW)
        {
            fprintf(fp1, "Withdraw\t ");
        }
         else if(bank->history[i].type == TX_UNDO)
        {
            fprintf(fp1, "Undo\t\t ");
        }
        fprintf(fp1, "%.2lf\t\t %.2lf\t\t %s\n", bank->history[i].amount, bank->balances[i],
                                        ctime(&bank->history[i].time));
    }
    fclose(fp1);
    fclose(fp2);
}