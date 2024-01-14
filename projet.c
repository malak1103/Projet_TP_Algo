#include <stdio.h>
#include <stdlib.h>
#include "include/raylib.h"

typedef struct Node Node;
typedef struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

// Function to create a singly linked list by reading elements
void createList() {
     head = NULL;
    int data;

    printf("Enter the number of elements in the list: ");
    int numElements;
    scanf("%d", &numElements);

    for (int i = 0; i < numElements; ++i) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &data);
        insertAtEnd(data);
    }
}

// Function to insert an element at the end of the list
void insertAtEnd(int data) {
    Node* newNode =malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to draw a rectangle representing a list node
void drawNodeRectangle(int posX, int posY, int data, bool highlighted) {
    // Draw the rectangle containing the data
    DrawRectangle(posX, posY, 50, 50, highlighted ? SKYBLUE : LIGHTGRAY);
    DrawText(TextFormat("%d", data), posX + 10, posY + 10, 20, BLACK);

    // Draw the arrow
    DrawLine(posX + 50, posY + 25, posX + 100, posY + 25, BLACK);
    DrawTriangle((Vector2){posX + 100, posY + 25}, (Vector2){posX + 120, posY + 20}, (Vector2){posX + 120, posY + 30}, BLACK);
}

// Function to draw the entire linked list
void drawList(int highlightedNode) {
    Node* current = head;
    int posX = 50;
    int posY = 200;

    while (current != NULL) {
        drawNodeRectangle(posX, posY, current->data, (highlightedNode == current->data));
        posX += 120;
        current = current->next;
    }
}
// Function to delete an element from the list at a given position k
void deleteElementAtPosition(int position) {
    if (head == NULL) {
        printf("List is empty. Deletion not possible.\n");
        return;
    }

    Node* temp = head;

    if (position == 1) {
        head = temp->next;
        free(temp);
    } else {
        for (int i = 1; i < position - 1 && temp != NULL; ++i) {
            temp = temp->next;
        }

        if (temp != NULL && temp->next != NULL) {
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            free(toDelete);
        } else {
            printf("Invalid position for deletion.\n");
        }
    }
}

// Function to handle user input
void handleInput(int* highlightedNode) {
    if (IsKeyPressed(KEY_ONE)) {
        int data, position;
        printf("Enter a number: ");
        scanf("%d", &data);
        printf("Enter position to insert: ");
        scanf("%d", &position);
        addElementAtPosition(data, position);
    }

    if (IsKeyPressed(KEY_TWO)) {
        int position;
        printf("Enter position to delete: ");
        scanf("%d", &position);
        deleteElementAtPosition(position);
    }

    if (IsKeyPressed(KEY_THREE)) {
        bubbleSort();
    }

    *highlightedNode = 0; // Reset highlighted node after processing input
}
