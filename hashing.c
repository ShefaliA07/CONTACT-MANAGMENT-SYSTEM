#include <stdio.h>
#include <string.h>

#define SIZE 37

struct Contact {
    int id;
    char name[50];
    char phone[15];
    int occupied;
};

struct Contact table[SIZE];
int collisions = 0;

int hashFunction(int id) {
    return id % 10;
}

void insert(int id, char name[], char phone[]) {
    int index = hashFunction(id);

    while (table[index].occupied) {
        if (table[index].id == id) {
            printf("Duplicate ID: %d\n", id);
            return;
        }

        collisions++;
        index = (index + 1) % SIZE;
    }

    table[index].id = id;
    strcpy(table[index].name, name);
    strcpy(table[index].phone, phone);
    table[index].occupied = 1;
}

void search(int id) {
    int index = hashFunction(id);
    int start = index;

    while (table[index].occupied) {
        if (table[index].id == id) {
            printf("Contact found!\n");
            printf("ID: %d\n", table[index].id);
            printf("Name: %s\n", table[index].name);
            printf("Phone: %s\n", table[index].phone);
            return;
        }

        index = (index + 1) % SIZE;

        if (index == start)
            break;
    }

    printf("Contact not found!\n");
}

void display() {
    printf("\nAll Contacts:\n");

    for (int i = 0; i < SIZE; i++) {
        if (table[i].occupied) {
            printf("%d  %s  %s\n",
                   table[i].id,
                   table[i].name,
                   table[i].phone);
        }
    }
}

int main() {
    for (int i = 0; i < SIZE; i++)
        table[i].occupied = 0;

    insert(101, "Arun", "9876543210");
    insert(102, "Bala", "9876543211");
    insert(103, "Charan", "9876543212");
    insert(104, "Deepak", "9876543213");
    insert(105, "Divya", "9876543214");

    printf("CONTACT MANAGEMENT SYSTEM - HASHING\n");

    display();

    printf("\nSearching for Contact ID 103:\n");
    search(103);

    printf("\nSearching for Contact ID 999:\n");
    search(999);

    printf("\nTotal Collisions: %d\n", collisions);

    return 0;
}
