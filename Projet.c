#include <stdio.h>
#include <stdlib.h>
#include "include/raylib.h"

typedef struct Node Node;
typedef struct Node {
    int data;
    Node* next;
};
Node* head = NULL;



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

// Function to perform bubble sort on the list
void bubbleSort() {
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

    return tete;
}

int main() {
   const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib LinkedList Visualization");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // UI
        DrawText("Press 1: Add Element  2: Delete Element  3: Start Sorting", 10, 10, 20, BLACK);

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

        drawList();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}


