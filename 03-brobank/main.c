#include <stdio.h>
#include "bank.h"
int main(void)
{
    int account_count = 0;
    int choice = 0;
    BroBank bank;
    Stack transactions;

    if (handle_bank_locked() != 1)      //handle lock screen
    {
        return 0;
    }

    brobank_init(&bank);     //initalize account
    get_balance(&bank);                     //read balance that was saved
    stackInit(&transactions);
    while (1)
    {
        handle_bank_menu(&bank);
        choice = get_choice();
        switch (choice)
        {
        case 1:
            handle_deposit(&bank, &transactions);
            break;

        case 2:
            handle_withdraw(&bank, &transactions);
            break;

        case 3:
            brobankUndo(&bank, &transactions);
            break;

        case 4:
            display_transactions(&bank);
            break;

        case 5:
            // Interest Rate Calculator
            break;
        
        case 6:
            return 0;
        }
    }

    return 0;
}