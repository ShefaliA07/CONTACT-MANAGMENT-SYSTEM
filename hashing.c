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
int comparisons = 0;

int hashFunction(int id) {
    return id % 10;
}

void insert(int id, char name[], char phone[]) {
    int index = hashFunction(id);

    while (table[index].occupied) {
        if (table[index].id == id)
            return;

        collisions++;
        index = (index + 1) % SIZE;
    }

    table[index].id = id;
    strcpy(table[index].name, name);
    strcpy(table[index].phone, phone);
    table[index].occupied = 1;
}

struct Contact* search(int id) {
    int index = hashFunction(id);
    int start = index;

    while (table[index].occupied) {
        comparisons++;

        if (table[index].id == id)
            return &table[index];

        index = (index + 1) % SIZE;

        if (index == start)
            break;
    }

    return NULL;
}

void display() {
    printf("\nAll 30 Contacts:\n");

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
    char *names[] = {
        "Arun", "Bala", "Charan", "Deepak", "Divya",
        "Eswar", "Farah", "Gokul", "Hari", "Ishita",
        "Jai", "Kavin", "Lakshmi", "Manoj", "Nisha",
        "Omkar", "Priya", "Rahul", "Sneha", "Tarun",
        "Uma", "Varun", "Wafa", "Xavier", "Yasmin",
        "Zoya", "Adithya", "Bhavana", "Chitra", "Dinesh"
    };

    for (int i = 0; i < SIZE; i++)
        table[i].occupied = 0;

    for (int i = 0; i < 30; i++) {
        char phone[15];
        sprintf(phone, "98765432%02d", 10 + i);

        insert(101 + i, names[i], phone);
    }

    printf("CONTACT MANAGEMENT SYSTEM - HASHING\n");

    display();

    comparisons = 0;
    struct Contact* found = search(115);

    printf("\nSearching ID 115: %s\n",
           found ? "Found" : "Not Found");
    printf("Successful search comparisons: %d\n",
           comparisons);

    comparisons = 0;
    found = search(999);

    printf("\nSearching ID 999: %s\n",
           found ? "Found" : "Not Found");
    printf("Unsuccessful search comparisons: %d\n",
           comparisons);

    printf("\nTotal Collisions: %d\n", collisions);

    return 0;
}
