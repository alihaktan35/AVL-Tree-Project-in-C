// github.com/alihaktan35

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to calculate height
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Function which returns maximum of a and b
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Funtion to create a node
struct Node *newNode(int key) {
    struct Node *node = (struct Node *)
            malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

// Function to search for a node in the tree
struct Node *searchNode(struct Node *root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return searchNode(root->left, key);
    else
        return searchNode(root->right, key);
}

// Right rotate function
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate function
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Function to get the balance factor
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Function to insert a node
struct Node *insertNode(struct Node *node, int key) {
    // Find the correct position to insert the node and insert it
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else {
        printf("Node with key %d already exists in the tree. Duplicates are not allowed.\n", key);
        return node;
    }

    // Update the balance factor of each node and balance the tree
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to find the node with the minimum value
struct Node *minValueNode(struct Node *node) {
    struct Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Function to delete a node
struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL) {
        printf("Fail! Cannot find %d in the tree.\n",key);
        return root;
    }

    // Find the node and delete it
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
        // Print the 'deleted' message
        printf("The node has been deleted.\n");
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and balance the tree
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Print the tree in PREORDER
void printPreOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

// Print the tree in INORDER
void printInOrder(struct Node *root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->key);
        printInOrder(root->right);
    }
}

///////////////////////////////////////////////////////////

int main() {
    // Initialization of the root node
    struct Node *root = NULL;

    while (true) {
        printf("-----------------------\n");
        printf("AVL Tree Project by ahs\n");
        printf("-----------------------\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Update\n");
        printf("4. Traverse the tree in Preorder\n");
        printf("5. Traverse the tree in Inorder\n");
        printf("6. Exit\n\n");
        printf("Please enter your choice:\n");

        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 1-6.\n\n");
            while ((getchar()) != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                // Insert option
                printf("\nYour choice is INSERT.\n");
                int valueToInsert;
                bool continueInserting = true;

                while (continueInserting) {
                    printf("Enter a node value to insert: (It must be an integer)\n");
                    while (true) {
                        if (scanf("%d", &valueToInsert) != 1) {
                            printf("Invalid input. Please enter an integer.\n\n");
                            while ((getchar()) != '\n'); // Clear input buffer
                        } else {
                            break;
                        }
                    }
                    root = insertNode(root, valueToInsert);

                    // Ask for Y/N confirmation
                    printf("Do you want to continue inserting? (Y/N)\n");
                    char answer;
                    scanf(" %c", &answer); // The space character (" ") before %c provides clean input
                    while ((getchar()) != '\n'); // Clear input buffer

                    if (answer == 'Y' || answer == 'y') {
                        continueInserting = true;
                    } else if (answer == 'N' || answer == 'n') {
                        continueInserting = false;
                        printf("Returning back to the menu.\n");
                    } else {
                        printf("Invalid input. Please enter Y or N.\n");
                    }
                }
                break;


            case 2:
                // Delete option
                printf("\nYour choice is DELETE.\n");
                int valueToDelete;
                bool continueDeleting = true;

                while (continueDeleting) {
                    printf("Enter a node value to delete: (It must be an integer)\n");
                    while (true) {
                        if (scanf("%d", &valueToDelete) != 1) {
                            printf("Invalid input. Please enter an integer.\n\n");
                            while ((getchar()) != '\n'); // Clear input buffer
                        } else {
                            break;
                        }
                    }
                    root = deleteNode(root, valueToDelete);

                    // Ask for Y/N confirmation
                    printf("Do you want to continue deleting? (Y/N)\n");
                    char answer;
                    scanf(" %c", &answer); // The space character (" ") before %c provides clean input
                    while ((getchar()) != '\n'); // Clear input buffer

                    if (answer == 'Y' || answer == 'y') {
                        continueDeleting = true;
                    } else if (answer == 'N' || answer == 'n') {
                        continueDeleting = false;
                        printf("Returning back to the menu.\n");
                    } else {
                        printf("Invalid input. Please enter Y or N.\n");
                    }
                }
                break;

            case 3:
                // Update option
                printf("\nYour choice is UPDATE.\n");
                int valueToUpdate;
                bool continueUpdating = true;

                while (continueUpdating) {
                    printf("Enter a node value to update:\n");
                    while (true) {
                        if (scanf("%d", &valueToUpdate) != 1) {
                            printf("Invalid input. Please enter an integer.\n\n");
                            while ((getchar()) != '\n'); // Clear input buffer
                        } else {
                            break;
                        }
                    }
                    struct Node *searchResult = searchNode(root, valueToUpdate);
                    if (searchResult != NULL) {
                        printf("Node with key %d found in the tree.\n", valueToUpdate);
                        printf("Enter the NEW value for this node:\n");
                        int newValue = 0;
                        while (true) {
                            if (scanf("%d", &newValue) != 1) {
                                printf("Invalid input. Please enter an integer.\n\n");
                                while ((getchar()) != '\n'); // Clear input buffer
                            } else {
                                break;
                            }
                        }

                        if (searchNode(root, newValue) != NULL) {
                            printf("Node with key %d already exists in the tree. Duplicates are not allowed.\n", newValue);
                        } else {
                            root = deleteNode(root, valueToUpdate);
                            root = insertNode(root, newValue);
                            printf("Node with key %d updated to %d.\n", valueToUpdate, newValue);
                        }
                    } else {
                        printf("Node with key %d not found in the tree.\n", valueToUpdate);
                    }

                    // Ask for Y/N confirmation
                    printf("Do you want to continue updating? (Y/N)\n");
                    char answer;
                    scanf(" %c", &answer); // The space character (" ") before %c provides clean input
                    while ((getchar()) != '\n'); // Clear input buffer

                    if (answer == 'Y' || answer == 'y') {
                        continueUpdating = true;
                    } else if (answer == 'N' || answer == 'n') {
                        continueUpdating = false;
                        printf("Returning back to the menu.\n");
                    } else {
                        printf("Invalid input. Please enter Y or N.\n");
                    }
                }
                break;

            case 4:
                // Preorder traversal
                printf("\nYour choice is PREORDER TRAVERSAL.\n");
                printf("Tree in Preorder: ");
                printPreOrder(root);
                printf("\n\n");
                break;
            case 5:
                // Inorder traversal
                printf("\nYour choice is INORDER TRAVERSAL.\n\n");
                printf("Tree in Inorder: ");
                printInOrder(root);
                printf("\n\n");
                break;
            case 6:
                // Exit
                printf("Exiting... Bye!");
                return 0;
            default:
                printf("Invalid input. Please enter a number between 1-6.\n\n");
        }
    }
}