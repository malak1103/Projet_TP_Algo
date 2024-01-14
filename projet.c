#include <stdio.h>
#include <stdlib.h>
#include "include/raylib.h"

typedef struct Node Node;
typedef struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

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

void createList()
{
    head = NULL;

    int data;

    printf("Enter the number of elements in the list: ");

    int numElements;
    scanf("%d", &numElements);

    for (int i = 0; i < numElements; ++i)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &data);

        insertAtEnd(data);
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

// Function to add an element to the list at a given position k
void addElementAtPosition(int data, int position)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;

    if (position == 1)
    {
        newNode->next = head;
        head = newNode;
    }

    else
    {
        Node *temp = head;

        for (int i = 1; i < position - 1 && temp != NULL; ++i)
        {
            temp = temp->next;
        }

        if (temp != NULL)
        {
            newNode->next = temp->next;
            temp->next = newNode;
        }

        else
        {
            printf("Invalid position for insertion.\n");
            free(newNode);
        }
    }
}




int isMouseOverButton(int x, int y, int width, int height)
{
    Vector2 mouse = GetMousePosition();
    return (mouse.x >= x && mouse.x <= x + width && mouse.y >= y && mouse.y <= y + height);
}
