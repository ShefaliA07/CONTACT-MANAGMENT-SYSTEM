#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    int id;
    char name[50], phone[15];
    int height;
    struct Contact *left, *right;
};

int comparisons = 0;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct Contact* n) {
    return n == NULL ? 0 : n->height;
}

struct Contact* create(int id, char name[], char phone[]) {
    struct Contact* n = malloc(sizeof(struct Contact));

    n->id = id;
    strcpy(n->name, name);
    strcpy(n->phone, phone);
    n->height = 1;
    n->left = n->right = NULL;

    return n;
}

int getBalance(struct Contact* n) {
    if (n == NULL)
        return 0;

    return getHeight(n->left) - getHeight(n->right);
}

struct Contact* rightRotate(struct Contact* y) {
    struct Contact* x = y->left;
    struct Contact* t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(getHeight(y->left),
                        getHeight(y->right));

    x->height = 1 + max(getHeight(x->left),
                        getHeight(x->right));

    return x;
}

struct Contact* leftRotate(struct Contact* x) {
    struct Contact* y = x->right;
    struct Contact* t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(getHeight(x->left),
                        getHeight(x->right));

    y->height = 1 + max(getHeight(y->left),
                        getHeight(y->right));

    return y;
}

struct Contact* insert(struct Contact* node,
                       int id, char name[], char phone[]) {
    if (node == NULL)
        return create(id, name, phone);

    if (id < node->id)
        node->left = insert(node->left, id, name, phone);
    else if (id > node->id)
        node->right = insert(node->right, id, name, phone);
    else
        return node;

    node->height = 1 + max(getHeight(node->left),
                           getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && id < node->left->id)
        return rightRotate(node);

    if (balance < -1 && id > node->right->id)
        return leftRotate(node);

    if (balance > 1 && id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct Contact* search(struct Contact* root, int id) {
    while (root != NULL) {
        comparisons++;

        if (id == root->id)
            return root;

        if (id < root->id)
            root = root->left;
        else
            root = root->right;
    }

    return NULL;
}

void display(struct Contact* root) {
    if (root != NULL) {
        display(root->left);

        printf("%d  %s  %s\n",
               root->id, root->name, root->phone);

        display(root->right);
    }
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

    printf("CONTACT MANAGEMENT SYSTEM - AVL\n");
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

    printf("\nAVL Tree Height: %d\n", getHeight(root));

    return 0;
}
