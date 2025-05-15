#include <stdio.h>
#include <string.h>

//stores all the account details
typedef struct {
    int accountNumber;
    char name[100];
    float balance;
    int age;
    char password[100];
} Acc;

// stores employees details
typedef struct 
{
     int idNumber;
     char password[100];
}employee;

// stores all the data required

Acc accounts[100];
employee logins[2];
Acc deleted_acc[100];

//keeps counts of accounts (active/deactivated)

int Acc_count = 0;
int Del_count = 0;

//starts giving numbers for acc id
int number = 1000000;

//stores employees data
void employees(){
    logins[0].idNumber = 17090;
    strcpy(logins[0].password, "Test1234"); 

    logins[1].idNumber = 17095;
    strcpy(logins[1].password, "MUecole"); 
}

//sorts accounts using bubble sort
void sortAccounts() {
    for (int i = 0; i < Acc_count - 1; i++) {
        
        for (int j = 0; j < Acc_count - i - 1; j++) { 

            if (accounts[j].accountNumber > accounts[j + 1].accountNumber) {
                 Acc temp = accounts[j];
                accounts[j] = accounts[j + 1];

                accounts[j + 1] = temp;
            }
        }
    }
}



// Binary search to find Acc index by Acc number
int binarySearch(int accNum) {
    int low = 0, high = Acc_count - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (accounts[mid].accountNumber == accNum)
            return mid;
        else if (accounts[mid].accountNumber < accNum)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

//creates an bank account
void createAccount() {
    if (Acc_count >= 100) {
        printf("Acc limit reached.\n");
        return;
    }

    Acc newAcc;
    printf("Enter Account holder name: ");

    int c;
    while ((c = getchar()) != '\n' && c != EOF);  

    fgets(newAcc.name,100,stdin);
    printf("Enter initial balance: ");
    scanf("%f", &newAcc.balance);
    printf("Enter your age:");
    scanf("%d",&newAcc.age);
    while(newAcc.age>80 || newAcc.age<18){
        printf("Age should be between 18 to 80 to create acc");
        return;
    }
    newAcc.accountNumber = number;
    number++;
    printf("Your account number: %d\n",newAcc.accountNumber);

    printf("Enter Password: ");

    int p;
    while ((p = getchar()) != '\n' && p != EOF);  

    fgets(newAcc.password,100,stdin);
    while(strlen(newAcc.password)-1 >15){
        printf("The password should be of length 15 or less\n");
        printf("Retype password: ");
        fgets(newAcc.password,100,stdin);
    }
    
    accounts[Acc_count] = newAcc;
    Acc_count++;
    sortAccounts();
    printf("Acc created successfully.\n");
}

//deposits money in a bank account
void depositMoney() {
    int accNum;
    float amount;
    printf("Enter Acc number: ");
    scanf("%d", &accNum);

    int index = binarySearch(accNum);
    if (index == -1) {
        printf("Acc not found.\n");
        return;
    }

    printf("Type password: ");
    char pass[100];
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  
    fgets(pass,100,stdin);
    while(strcmp(accounts[index].password,pass)!=0){
        printf("wrong password \ntype again: ");
        fgets(pass,100,stdin);
    }

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid deposit amount.\n");
        return;
    }

    accounts[index].balance += amount;
    printf("Amount deposited successfully.\n");
}

// withdraws money from a bank account
void withdrawMoney() {
    int accNum;
    float amount;
    printf("Enter Acc number: ");
    scanf("%d", &accNum);

    int index = binarySearch(accNum);
    if (index == -1) {
        printf("Acc not found.\n");
        return;
    }

    printf("Type password: ");
    char pass[100];
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  
    fgets(pass,100,stdin);
    while(strcmp(accounts[index].password,pass)!=0){
        printf("wrong password \ntype again: ");
        fgets(pass,100,stdin);
    }

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > accounts[index].balance) {
        printf("Invalid withdrawal amount.\n");
        return;
    }

    accounts[index].balance -= amount;
    printf("Amount withdrawn successfully.\n");
}

//Lets user check their balance
void checkBalance() {
    int accNum;
    printf("Enter Acc number: ");
    scanf("%d", &accNum);

    int index = binarySearch(accNum);
    if (index == -1) {
        printf("Acc not found.\n");
        return;
    }

    printf("Type password: ");
    char pass[100];
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  
    fgets(pass,100,stdin);
    while(strcmp(accounts[index].password,pass)!=0){
        printf("wrong password \ntype again: ");
        fgets(pass,100,stdin);
    }
    printf("Acc Holder: %s\n", accounts[index].name);
    printf("Current Balance: %.2f\n", accounts[index].balance);
}

// deletes an account if required by user
void deleteAccount() {
    int accNum;
    printf("Enter Acc number to delete: ");
    scanf("%d", &accNum);

    int index = binarySearch(accNum);
    if (index == -1) {
        printf("Acc not found.\n");
        return;
    }

    printf("Type password: ");
    char pass[100];
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  
    fgets(pass,100,stdin);
    while(strcmp(accounts[index].password,pass)!=0){
        printf("wrong password \ntype again: ");
        fgets(pass,100,stdin);
    }

    deleted_acc[Del_count] = accounts[index];
    Del_count ++;

    for (int i = index; i < Acc_count - 1; i++) {
        accounts[i] = accounts[i + 1];
    }
    Acc_count--;
    printf("Acc deleted successfully.\n");
}

//shows all accounts(only employees)
void showaccounts(){
    printf("\n Available accounts\n");  
    for(int i = 0;i < Acc_count;i++){
        printf("\n%s\n",accounts[1].name);
        printf("%d\n",accounts[1].accountNumber);

    }

    printf("\n Deleted accounts\n");
    for(int i = 0;i < Del_count;i++){
        printf("\n%s\n",deleted_acc[1].name);
        printf("%d\n",deleted_acc[1].accountNumber);

    }

    return;

}

// enables employee login
void employeelogin() {
    int login;
    printf("Login ID: ");
    scanf("%d", &login);

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    int found = -1;
    for (int i = 0; i < 2; i++) {
        if (logins[i].idNumber == login) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Invalid employee ID.\n");
        return;
    }

    char pass[100];
    printf("Type password: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0'; 

    while (strcmp(logins[found].password, pass) != 0) {
        printf("Wrong password. Try again: ");
        fgets(pass, sizeof(pass), stdin);
        pass[strcspn(pass, "\n")] = '\0';
    }

    printf("Employee login successful.\n");

    int choice = 0;
    while (choice != 2) {
        printf("\n  Employee Menu\n"
               "1. Show all accounts\n"
               "2. Exit employee menu\n"
               "Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showaccounts(); break;
            case 2: printf("Exiting employee menu.\n"); break;
            default: printf("Invalid option.\n"); break;
        }
    }
    return;
}




int main() {
    employees();
    // gives user a banking page with navigation
    int choice = 0;
    while (choice != 7) {
      printf("\n   Banking System Menu   \n"
            "1. Create Acc\n"
            "2. Deposit Money\n"
            "3. Withdraw Money\n"
            "4. Check Balance\n"
            "5. Delete Acc\n"
            "6. Employee login\n"
            "7. Exit\n"
            "Choose an option: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: deleteAccount(); break;
            case 6: employeelogin();break;
            case 7: printf("Exited\n"); break;
            default: printf("Invalid option.\n");
        }
    } 

    return 0;
}
