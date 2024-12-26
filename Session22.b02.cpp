#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    char account[50];
    char password[50];
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

const char *filename = "accounts.dat";
void loadAccountsFromFile();
void saveAccountsToFile();
void registerAccount();
void loginAccount();

int main() {
    int choice;
    loadAccountsFromFile();

    do {
        printf("\nMENU\n");
        printf("1.Dang nhap \n");
        printf("2. Dang ki\n");
        printf("3. Thoat\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                loginAccount();
                break;
            case 2:
                registerAccount();
                break;
            case 3:
                printf("Thoat\n");
                break;
            default:
                printf("Khong hop le\n");
        }
    } while (choice != 3);

    return 0;
}

void loadAccountsFromFile() {
    FILE *file = fopen(filename, "rb");
    if (file) {
        accountCount = fread(accounts, sizeof(Account), MAX_ACCOUNTS, file);
        fclose(file);
    } else {
        accountCount = 0;
    }
}

void saveAccountsToFile() {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    } else {
        printf("Loi\n");
    }
}

void registerAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Tai khoan da het cho chua \n");
        return;
    }

    Account newAccount;
    char confirmPassword[50];
    int isDuplicate = 0;

    do {
        isDuplicate = 0;
        printf("Enter account: ");
        scanf("%s", newAccount.account);

        for (int i = 0; i < accountCount; i++) {
            if (strcmp(accounts[i].account, newAccount.account) == 0) {
                isDuplicate = 1;
                printf("Da ton tai tai khoan\n");
                break;
            }
        }
    } while (isDuplicate);

    do {
        printf("Moi nhap mat khau : ");
        scanf("%s", newAccount.password);
        printf("Confirm password: ");
        scanf("%s", confirmPassword);

        if (strcmp(newAccount.password, confirmPassword) != 0) {
            printf("Mat khau khong hop le\n");
        }
    } while (strcmp(newAccount.password, confirmPassword) != 0);

    accounts[accountCount++] = newAccount;
    saveAccountsToFile();
    printf("Dang ky thanh cong.\n");
}

void loginAccount() {
    char inputAccount[50], inputPassword[50];
    int isLoggedIn = 0;

    printf("Nhap tai khoan: ");
    scanf("%s", inputAccount);
    printf("Nhap mat khau : ");
    scanf("%s", inputPassword);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].account, inputAccount) == 0 &&
            strcmp(accounts[i].password, inputPassword) == 0) {
            isLoggedIn = 1;
            break;
        }
    }

    if (isLoggedIn) {
        printf("Dang nhap thanh cong.\n");
    } else {
        printf("Dang nhap ko hop le \n");
    }
}

