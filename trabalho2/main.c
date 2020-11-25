#include "definitions.h"

//Initializing the pthread mutex.
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*
    Adds the given value to the given account.
*/
void debit(Account* account, float amount){
    pthread_mutex_lock(&mutex);
    account->balance -= amount;
    pthread_mutex_unlock(&mutex);
};

/*
    Subtracts the given value from the given account.
*/
void credit(Account* account, float amount){
    pthread_mutex_lock(&mutex);
    account->balance += amount;
    pthread_mutex_unlock(&mutex);
};

/*
    Checks the ballance of a given account.
*/
void query(Account account){
    printf("\tAccount %d balance is $%.2f\n", account.id, account.balance);
};

/*
    Fills an operation array with random operation ids and account ids.
*/
void generate_operations(int n_accounts, int n_operations, Operation* operations){
    for(int i = 0; i < n_operations; ++i){
        operations[i].id = (rand() % 3); // 0..2
        operations[i].account_id = (rand() % n_accounts);
    }
}

/*
    Runs the operations on the given operation array over que given accounts.
*/
void* process(void* arguments){
    /* Argument Parsing */
    args_struct* args = (args_struct*)arguments;
    Account* accounts = args->accounts;
    Operation* operations = args->operations;
    int n_operations = args->n_operations;
    int thread_id = args->thread_id;
    
    /* Helper Variables */
    float amount;
    Account* account;
    
    for(int i = 0; i < n_operations; ++i){
        account = &accounts[operations[i].account_id];
        switch (operations[i].id){
            case CREDIT:
                amount = (rand() % 1000) + 1;
                printf("[THREAD %d]\n\tCredit %.2f to account %d\n", thread_id, amount, account->id);
                credit(account, amount);
                break;

            case DEBIT:
                amount = (rand() % 1000) + 1;
                printf("[THREAD %d]\n\tDebit %.2f to account %d\n", thread_id, amount, account->id);
                debit(account, amount);
                break;

            case QUERY:
                printf("[THREAD %d]\n\tQuerying account %d:\n", thread_id, account->id);
                query(*account);
                break;

            default:
                printf("Error.\n");
                return NULL;
                break;
        }
    }
};

/*
    Iniliatilzes an account with a random balance.
*/
Account initialize(Account *ac, int id){
    ac->id = id;
    ac->balance = (rand() % 10000);
}

/*
    Driver Code
*/
int main(int argc, char** argv){
    srand(time(NULL));
    int n_accounts = atoi(argv[1]);
    int n_threads = atoi(argv[2]);

    Account* accounts;
    accounts = malloc(n_accounts * sizeof(Account));
    
    for(int i = 0; i < n_accounts; ++i){
        initialize(&accounts[i], i);
    }

    printf("Initial balance:\n");
    for(int i = 0; i < n_accounts; ++i){
        query(accounts[i]);
    }
       
    args_struct* args;
    Operation* operations;
    pthread_t threads[n_threads];

    /*
        Generates a random array of operations for each thread and processes it in parallel.
    */
    printf("\n");
    for(int i = 0; i < n_threads; ++i){
        int n_operations = (rand() % 10) + 1;
        
        operations = malloc(n_operations * sizeof(Operation));
        generate_operations(n_accounts, n_operations, operations);
        
        args = malloc(sizeof(args_struct));
        args->accounts = accounts;
        args->operations = operations;
        args->n_operations = n_operations;
        args->thread_id = i;

        pthread_create(&threads[i], NULL, &process, (void*) args);
    }

    for(int i = 0; i < n_threads; ++i){
		pthread_join(threads[i], NULL);
	}

    printf("\nFinal balance:\n");
    for(int i = 0; i < n_accounts; ++i){
        query(accounts[i]);
    }

    return 0;
}
