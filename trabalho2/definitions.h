#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h> 

typedef struct Account{
    int id;
    float balance;
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

enum operations {CREDIT = 0, DEBIT = 1, QUERY = 2} operations;
