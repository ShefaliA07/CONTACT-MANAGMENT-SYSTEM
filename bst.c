#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    int id;
    char name[50], phone[15];
    struct Contact *left, *right;
};

int comparisons = 0;

struct Contact* create(int id, char name[], char phone[]) {
    struct Contact* n = malloc(sizeof(struct Contact));
    n->id = id;
    strcpy(n->name, name);
    strcpy(n->phone, phone);
    n->left = n->right = NULL;
    return n;
}

struct Contact* insert(struct Contact* root,
                       int id, char name[], char phone[]) {
    if (root == NULL)
        return create(id, name, phone);

    if (id < root->id)
        root->left = insert(root->left, id, name, phone);
    else if (id > root->id)
        root->right = insert(root->right, id, name, phone);

    return root;
}

struct Contact* search(struct Contact* root, int id) {
    while (root != NULL) {
        comparisons++;

        if (id == root->id)
            return root;
        else if (id < root->id)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

void display(struct Contact* root) {
    if (root != NULL) {
        display(root->left);
        printf("%d  %s  %s\n", root->id,
               root->name, root->phone);
        display(root->right);
    }
}

int height(struct Contact* root) {
    if (root == NULL)
        return 0;

    int l = height(root->left);
    int r = height(root->right);
    return 1 + (l > r ? l : r);
}

int main() {
    struct Contact* root = NULL;

    char *names[] = {
        "Arun", "Bala", "Charan", "Deepak", "Divya",
        "Eswar", "Farah", "Gokul", "Hari", "Ishita",
        "Jai", "Kavin", "Lakshmi", "Manoj", "Nisha",
        "Omkar", "Priya", "Rahul", "Sneha", "Tarun",
        "Uma", "Varun", "Wafa", "Xavier", "Yasmin",
        "Zoya", "Adithya", "Bhavana", "Chitra", "Dinesh"
    };

    for (int i = 0; i < 30; i++) {
        char phone[15];
        sprintf(phone, "98765432%02d", 10 + i);
        root = insert(root, 101 + i, names[i], phone);
    }

    printf("CONTACT MANAGEMENT SYSTEM - BST\n");
    printf("\nAll 30 Contacts:\n");
    display(root);

    comparisons = 0;
    struct Contact* found = search(root, 115);
    printf("\nSearching ID 115: %s\n",
           found ? "Found" : "Not Found");
    printf("Successful search comparisons: %d\n",
           comparisons);

    comparisons = 0;
    found = search(root, 999);
    printf("\nSearching ID 999: %s\n",
           found ? "Found" : "Not Found");
    printf("Unsuccessful search comparisons: %d\n",
           comparisons);

    printf("\nBST Height: %d\n", height(root));

    return 0;
}
