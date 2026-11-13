
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    int id;
    char name[50];
    char phone[15];
    struct Contact *left, *right;
};

struct Contact* createContact(int id, char name[], char phone[]) {
    struct Contact* newContact =
        (struct Contact*)malloc(sizeof(struct Contact));

    newContact->id = id;
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->left = NULL;
    newContact->right = NULL;

    return newContact;
}

struct Contact* insert(struct Contact* root,
                       int id, char name[], char phone[]) {
    if (root == NULL)
        return createContact(id, name, phone);

    if (id < root->id)
        root->left = insert(root->left, id, name, phone);
    else if (id > root->id)
        root->right = insert(root->right, id, name, phone);

    return root;
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

int height(struct Contact* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight
                ? leftHeight : rightHeight);
}

int main() {
    struct Contact* root = NULL;

    root = insert(root, 101, "Arun", "9876543210");
    root = insert(root, 102, "Bala", "9876543211");
    root = insert(root, 103, "Charan", "9876543212");
    root = insert(root, 104, "Deepak", "9876543213");
    root = insert(root, 105, "Divya", "9876543214");

    printf("CONTACT MANAGEMENT SYSTEM - BST\n");

    printf("\nAll Contacts:\n");
    display(root);

    printf("\nSearching for Contact ID 103:\n");
    search(root, 103);

    printf("\nBST Height: %d\n", height(root));

    return 0;
}
