# CONTACT-MANAGMENT-SYSTEM
Contact Management using BST,AVL and HASHING in C
# Contact Management System

## 1. Introduction
The Contact Management System is a C programming project
used to store and search contact details using different
data structures.

## 2. Objective
To implement and compare:
- Binary Search Tree (BST)
- AVL Tree
- Hashing with Linear Probing

## 3. Contact Details
Each contact contains:
- Contact ID
- Name
- Phone Number

The project uses 30 unique contacts with IDs from 101 to 130.

## 4. Data Structures Used

### Binary Search Tree
BST stores contacts according to their Contact ID.
Smaller IDs are stored on the left and larger IDs
are stored on the right.

### AVL Tree
AVL is a self-balancing Binary Search Tree.
It uses rotations to maintain balance.

### Hashing with Linear Probing
Hashing calculates an index using the hash function.
If a position is occupied, linear probing checks
the next available position.

## 5. Experimental Results

| Measurement | BST | AVL | Hashing |
|---|---:|---:|---:|
| Successful comparisons | 15 | 5 | 10 |
| Unsuccessful comparisons | 30 | 5 | 21 |
| Tree height | 30 | 5 | N/A |
| Collisions | N/A | N/A | 300 |

## 6. Observation
BST becomes unbalanced when contacts are inserted
in ascending order.

AVL maintains balance and reduces the number
of search comparisons.

Hashing provides indexed storage, but collisions
occur and are handled using linear probing.

## 7. Conclusion
Based on this experiment, AVL performs better
than BST and the tested hashing implementation
for the selected search operations.

AVL provides balanced searching, while BST
becomes skewed for sorted insertion.

## 8. Files Included
- bst.c
- avl.c
- hashing.c
- contacts.txt
- experiment_results.txt
- README.md

## 9. Programming Language
C
