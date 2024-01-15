#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *head = NULL;

int isMouseOverButton(int x, int y, int width, int height)
{
    Vector2 mouse = GetMousePosition();
    return (mouse.x >= x && mouse.x <= x + width && mouse.y >= y && mouse.y <= y + height);
}

// Function to insert an element at the end of the list
void insertAtEnd(int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }

    else
    {
        Node *temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

// Function to draw a rectangle representing a list node
void drawNodeRectangle(int posX, int posY, int data, bool highlighted)
{
    // Draw the rectangle containing the data
    DrawRectangle(posX, posY, 50, 50, highlighted ? SKYBLUE : LIGHTGRAY);
    DrawText(TextFormat("%d", data), posX + 10, posY + 10, 20, BLACK);

    // Draw the arrow
    DrawLine(posX + 50, posY + 25, posX + 100, posY + 25, BLACK);
    DrawTriangle((Vector2){posX + 100, posY + 25}, (Vector2){posX + 120, posY + 20}, (Vector2){posX + 120, posY + 30}, BLACK);
}

// Function to draw the entire linked list
void drawList(int highlightedNode)
{
    Node *current = head;

    int posX = 50;
    int posY = 200;

    while (current != NULL)
    {
        drawNodeRectangle(posX, posY, current->data, (highlightedNode == current->data));
        posX += 120;

        current = current->next;
    }
}

// Function to delete an element from the list at a given position k
void deleteElementAtPosition(int position)
{
    if (head == NULL)
    {
        printf("List is empty. Deletion not possible.\n");
        return;
    }

    Node *temp = head;

    if (position == 1)
    {
        head = temp->next;
        free(temp);
    }
    else
    {
        for (int i = 1; i < position - 1 && temp != NULL; ++i)
        {
            temp = temp->next;
        }

        if (temp != NULL && temp->next != NULL)
        {
            Node *toDelete = temp->next;
            temp->next = toDelete->next;
            free(toDelete);
        }
        else
        {
            printf("Invalid position for deletion.\n");
        }
    }
}

// Function to perform bubble sort on the list
void bubbleSort()
{
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;

    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->data > ptr1->next->data)
            {
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

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib LinkedList Visualization");

    SetTargetFPS(60);

    int highlightedNode = 0;

    char addBuffer[10] = "\0";    // Buffer for add input, allowing up to 10 digits
    char deleteBuffer[10] = "\0"; // Buffer for delete input, allowing up to 10 digits

    int action = 0; // 0: No action, 1: Add Element, 2: Delete Element, 3: Start Sorting

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
                if (((key >= KEY_ZERO) && (key <= KEY_NINE)) || ((key >= KEY_KP_0) && (key <= KEY_KP_9)))
                {
                    if (strlen(addBuffer) < 10)
                    {
                        char digit = (key >= KEY_KP_0 && key <= KEY_KP_9) ? (char)(key - KEY_KP_0 + '0') : (char)(key);
                        addBuffer[strlen(addBuffer)] = digit;
                    }
                }
            }

            if (deleteActive == 1)
            {
                if (((key >= KEY_ZERO) && (key <= KEY_NINE)) || ((key >= KEY_KP_0) && (key <= KEY_KP_9)))
                {
                    if (strlen(deleteBuffer) < 10)
                    {
                        char digit = (key >= KEY_KP_0 && key <= KEY_KP_9) ? (char)(key - KEY_KP_0 + '0') : (char)(key);
                        deleteBuffer[strlen(deleteBuffer)] = digit;
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
                for (int i = 0; i < 10; i++)
                {
                    addBuffer[i] = '\0';
                }
            }
            break;
        case 2:
            if (strlen(deleteBuffer) > 0)
            {
                int position = atoi(deleteBuffer);
                deleteElementAtPosition(position);

                for (int i = 0; i < 10; i++)
                {
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