#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Record {
    char phoneNumber[15];
    char username[50];
    char address[100];
    struct Record* next;
} Record;

typedef struct HashTable {
    Record* table[TABLE_SIZE];
} HashTable;

unsigned int hash(char* key) {
    unsigned int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue += key[i];
    }
    return hashValue % TABLE_SIZE;
}
void insertRecord_phone(HashTable* ht, char* phoneNumber, char* username, char* address) {
    unsigned int index = hash(phoneNumber);
    Record* newRecord = (Record*)malloc(sizeof(Record));
    strcpy(newRecord->phoneNumber, phoneNumber);
    strcpy(newRecord->username, username);
    strcpy(newRecord->address, address);
    newRecord->next = ht->table[index];
    ht->table[index] = newRecord;
}
void insertRecord_name(HashTable* ht, char* phoneNumber, char* username, char* address) {
    unsigned int index = hash(username);
    Record* newRecord = (Record*)malloc(sizeof(Record));
    strcpy(newRecord->phoneNumber, phoneNumber);
    strcpy(newRecord->username, username);
    strcpy(newRecord->address, address);
    newRecord->next = ht->table[index];
    ht->table[index] = newRecord;
}
Record* searchByPhoneNumber(HashTable* ht, char* phoneNumber) {
    unsigned int index = hash(phoneNumber);
    Record* current = ht->table[index];
    while (current != NULL) {
        if (strcmp(current->phoneNumber, phoneNumber) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
Record* searchByUsername(HashTable* ht, char* username) {
    unsigned int index = hash(username);
    Record* current = ht->table[index];
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
void printRecord(Record* record) {
    if (record != NULL) {
        printf("the result is:\n");
        printf("Phone Number: %s\n", record->phoneNumber);
        printf("Username: %s\n", record->username);
        printf("Address: %s\n", record->address);
    } else {
        printf(" not found.\n\n");
    }
}

int main() {
    HashTable ht;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.table[i] = NULL;
    }
    HashTable ht_name;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht_name.table[i] = NULL;
    }

    printf("Welcome to the phone book!\n");
    while (1) {
        printf("\n\n");

        printf("1. Add a record\n");
        printf("2. Search by phone number\n");
        printf("3. Search by username\n");
        printf("4. Exit\n");
        printf("Please select an option: ");
        printf("\n\n");
        int option;
        scanf("%d", &option);
        if (option == 1) {
            char phoneNumber[15];
            char username[50];
            char address[100];
            printf("Please enter the phone number: ");
            scanf("%s", phoneNumber);
            printf("Please enter the username: ");
            scanf("%s", username);
            printf("Please enter the address: ");
            scanf("%s", address);
            insertRecord_phone(&ht, phoneNumber, username, address);
            insertRecord_name(&ht_name, phoneNumber, username, address);
            printf("\nsuccessfully added\n ");
        } else if (option == 2) {
            char phoneNumber[15];
            printf("Please enter the phone number: ");
            scanf("%s", phoneNumber);
            Record* record = searchByPhoneNumber(&ht, phoneNumber);
            printRecord(record);
        } else if (option == 3) {
            char username[50];
            printf("Please enter the username: ");
            scanf("%s", username);
            Record* record = searchByUsername(&ht_name, username);
            printRecord(record);
        } else if (option == 4) {
            break;
        } else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}
