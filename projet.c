#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

}
int main() {
     const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib LinkedList Visualization");

    SetTargetFPS(60);

    int highlightedNode = 0;

    char addBuffer[10] = "\0";    // Buffer for add input, allowing up to 10 digits
    char deleteBuffer[10] = "\0"; // Buffer for delete input, allowing up to 10 digits
    
    int action = 0;                 // 0: No action, 1: Add Element, 2: Delete Element, 3: Start Sorting

    int addActive = 0;
    int deleteActive = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw buttons
        DrawRectangle(10, 10, 100, 30, LIGHTGRAY);
        DrawRectangleLines(10, 10, 100, 30, GRAY);
        DrawText("Add", 35, 15, 12, BLACK);

        DrawRectangle(120, 10, 100, 30, LIGHTGRAY);
        DrawRectangleLines(120, 10, 100, 30, GRAY);
        DrawText("Delete", 145, 15, 12, BLACK);

        DrawRectangle(230, 10, 100, 30, LIGHTGRAY);
        DrawRectangleLines(230, 10, 100, 30, GRAY);
        DrawText("Sort", 255, 15, 12, BLACK);

        if (isMouseOverButton(10, 10, 100, 30) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            addActive = 1;
            deleteActive = 0;
        }

        if (isMouseOverButton(120, 10, 100, 30) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            addActive = 0;
            deleteActive = 1;
        }

        if (isMouseOverButton(230, 10, 100, 30) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            action = 3;
        }

        if (addActive == 1)
        {
            // Draw the input box for adding elements
            DrawRectangle(10, 50, 200, 30, LIGHTGRAY);
            DrawRectangleLines(10, 50, 200, 30, GRAY);
            DrawText("Add Element:", 15, 50, 12, BLACK);
            DrawText(addBuffer, 20, 60, 12, BLACK);
        }

        if (deleteActive == 1)
        {
            // Draw the input box for deleting elements
            DrawRectangle(10, 90, 200, 30, LIGHTGRAY);
            DrawRectangleLines(10, 90, 200, 30, GRAY);
            DrawText("Delete Element (Position):", 15, 90, 12, BLACK);
            DrawText(deleteBuffer, 20, 100, 12, BLACK);
        }

        // Check for key press and update the input buffers
        int key = GetKeyPressed();

        switch (key)
        {
        case KEY_BACKSPACE:
            if (addActive == 1)
            {
                if (strlen(addBuffer) > 0)
                {
                    addBuffer[strlen(addBuffer) - 1] = '\0';
                }
            }
            if (deleteActive == 1)
            {
                if (strlen(deleteBuffer) > 0)
                {
                    deleteBuffer[strlen(deleteBuffer) - 1] = '\0';
                }
            }
            break;
        case KEY_ENTER:
            if (addActive == 1)
            {
                action = 1;
            }
            if (deleteActive == 1)
            {
                action = 2;
            }
            break;
        default:
            if (addActive == 1)
            {
                // Process numerical input
                if ((key >= KEY_ZERO) && (key <= KEY_NINE))
                {
                    if (strlen(addBuffer) < 10)
                    {
                        addBuffer[strlen(addBuffer)] = (char)(key);
                    }
                }
            }
            if (deleteActive == 1)
            {
                // Process numerical input
                if ((key >= KEY_ZERO) && (key <= KEY_NINE))
                {
                    if (strlen(deleteBuffer) < 10)
                    {
                        deleteBuffer[strlen(deleteBuffer)] = (char)(key);
                    }
                }
            }
        }

        // Execute the action based on the button pressed
        switch (action)
        {
        case 1:
            if (strlen(addBuffer) > 0)
            {
                int data = atoi(addBuffer);
                insertAtEnd(data);

                highlightedNode = 0;
                for(int i = 0; i < 10; i++) {
                    addBuffer[i] = '\0';
                }
            }
            break;
        case 2:
            if (strlen(deleteBuffer) > 0)
            {
                int position = atoi(deleteBuffer);
                deleteElementAtPosition(position);

                for(int i = 0; i < 10; i++) {
                    deleteBuffer[i] = '\0';
                }
            }
            break;
        case 3:
            bubbleSort();

            break;
        }

        action = 0; // Reset action after processing

        // Draw the linked list
        drawList(highlightedNode);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}


