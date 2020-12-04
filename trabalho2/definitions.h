#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Account{
    int id;
    float balance;
    int status;
} Account;

typedef struct Operation{
    int id;
    int account_id; 
} Operation;

typedef struct args_struct{
    Account* accounts;
    Operation* operations;
    int n_operations;
    int thread_id;
} args_struct;

enum operations {NONE = 0 , CREDIT = 1, DEBIT = 2, QUERY = 3} operations;
