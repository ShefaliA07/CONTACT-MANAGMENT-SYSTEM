
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    int id;
    char name[50];
    char phone[15];
    struct Contact *left, *right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct Contact* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

struct Contact* createContact(int id, char name[], char phone[]) {
    struct Contact* node =
        (struct Contact*)malloc(sizeof(struct Contact));

    node->id = id;
    strcpy(node->name, name);
    strcpy(node->phone, phone);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

int getBalance(struct Contact* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct Contact* rightRotate(struct Contact* y) {
    struct Contact* x = y->left;
    struct Contact* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(getHeight(y->left),
                        getHeight(y->right));
    x->height = 1 + max(getHeight(x->left),
                        getHeight(x->right));

    return x;
}

struct Contact* leftRotate(struct Contact* x) {
    struct Contact* y = x->right;
    struct Contact* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(getHeight(x->left),
                        getHeight(x->right));
    y->height = 1 + max(getHeight(y->left),
                        getHeight(y->right));

    return y;
}

struct Contact* insert(struct Contact* node,
                       int id, char name[], char phone[]) {
    if (node == NULL)
        return createContact(id, name, phone);

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

void search(struct Contact* root, int id) {
    if (root == NULL) {
        printf("Contact not found!\n");
        return;
    }

    if (id == root->id) {
        printf("Contact found!\n");
        printf("ID: %d\n", root->id);
        printf("Name: %s\n", root->name);
        printf("Phone: %s\n", root->phone);
    } else if (id < root->id) {
        search(root->left, id);
    } else {
        search(root->right, id);
    }
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

    root = insert(root, 101, "Arun", "9876543210");
    root = insert(root, 102, "Bala", "9876543211");
    root = insert(root, 103, "Charan", "9876543212");
    root = insert(root, 104, "Deepak", "9876543213");
    root = insert(root, 105, "Divya", "9876543214");

    printf("CONTACT MANAGEMENT SYSTEM - AVL\n");

    printf("\nAll Contacts:\n");
    display(root);

    printf("\nSearching for Contact ID 103:\n");
    search(root, 103);

    printf("\nAVL Tree Height: %d\n", getHeight(root));

    return 0;
}
