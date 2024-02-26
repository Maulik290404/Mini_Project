#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Define the structure for the linked list node
typedef struct Node {
    char data[MAX_LINE_LENGTH];
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        strncpy(newNode->data, data, MAX_LINE_LENGTH);
        newNode->next = NULL;
    }
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertAtEnd(Node** headRef, char* data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        Node* current = *headRef;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to print the linked list
void printLinkedList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%s", current->data); // Print data of the current node
        current = current->next;
    }
}

// Function to delete a node from the linked list by position
void deleteNodeByPosition(Node** headRef, int position) {
    if (*headRef == NULL) {
        return;
    }

    Node* temp = *headRef;
    if (position == 0) {
        *headRef = temp->next;
        free(temp);
        return;
    }

    int i;
    for (i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        return;
    }

    Node* nextNode = temp->next->next;
    free(temp->next);
    temp->next = nextNode;
}

// Function to read a specific line from a file and add it to the linked list
void readSpecificLineFromFile(const char* filename, Node** headRef, int line_number) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int current_line = 0;
    while (fgets(line, sizeof(line), file)) {
        current_line++;
        if (current_line == line_number) {
            insertAtEnd(headRef, line);
            fclose(file);
            return;
        }
    }

    fclose(file);
}

// Function to free memory allocated for the linked list
void freeLinkedList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    const char* filename = "2022worldcup.csv";  // Replace 'example.csv' with the path to your CSV file

    Node* head = NULL;
    int choice;
    int position;

    do {
        // Print menu options
        printf("\nMenu:\n");
        printf("1. Add specific line\n");
        printf("2. Delete data\n");
        printf("3. Print data\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the line number to add: ");
                scanf("%d", &position);
                readSpecificLineFromFile(filename, &head, position);
                break;
            case 2:
                printf("Enter the position of the data to delete: ");
                scanf("%d", &position);
                deleteNodeByPosition(&head, position);
                break;
            case 3:
                printf("Data in the linked list:\n");
                printLinkedList(head);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    // Free memory allocated for the linked list
    freeLinkedList(head);

    return 0;
}

