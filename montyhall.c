#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int has_prize;

} Door;

void printDoorsWithGoat(int openDoor)
{
    printf("\n  _______    _______    _______\n");
    for (int i = 0; i < 3; i++)
    {
        if (i == openDoor)
        {
            printf(" |       |  "); // Open door
        }
        else
        {
            printf(" |       |  "); // Closed door
        }
    }
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        if (i == openDoor)
        {
            printf(" |  Goat |  "); // Goat revealed
        }
        else
        {
            printf(" |   %d   |  ", i); // Closed door with number
        }
    }
    printf("\n");

    printf(" |_______|  |_______|  |_______|\n");
    printf("\n");
}

void printDoorsWithCar(int openDoor)
{
    printf("\n  _______    _______    _______\n");
    for (int i = 0; i < 3; i++)
    {
        if (i == openDoor)
        {
            printf(" |       |  "); // Open door
        }
        else
        {
            printf(" |       |  "); // Closed door
        }
    }
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        if (i == openDoor)
        {
            printf(" |  CAR |  "); // Goat revealed
        }
        else
        {
            printf(" |   %d   |  ", i); // Closed door with number
        }
    }
    printf("\n");

    printf(" |_______|  |_______|  |_______|\n");
    printf("\n");
}

void manualGame()
{
    Door doors[3];

    for (int i = 0; i < 3; i++)
    {
        doors[i].has_prize = 0;
    }

    srand(time(NULL));

    int prizeDoor = rand() % 3;
    printf("prize is %d\n", prizeDoor);
    doors[prizeDoor].has_prize = 1;

    int choice;
    printf("  _______    _______    _______\n");
    printf(" |       |  |       |  |       |\n");
    printf(" |   0   |  |   1   |  |   2   |\n");
    printf(" |_______|  |_______|  |_______|\n");
    printf("Time to pick a door!\nType number 0-2 to select door.\nYour choice:");
    scanf("%d", &choice);

    printf("you chose %d\n", choice);

    // in case input was out of bounds
    while (choice < 0 || choice > 2)
    {
        printf("Invalid input!\nType number 0-2 to select door.\nYour choice:");
        scanf("%d", &choice);
    }

    // we have to find a door to open, that does not contain the prize and is not the one the player chose. We try randomly until we find one
    int openDoor = -1;

    while (openDoor == -1)
    {
        int temp = rand() % 3;
        if (doors[temp].has_prize == 0 && temp != choice)
        {
            openDoor = temp;
        }
    }

    printDoorsWithGoat(openDoor);
    printf("You chose Door %d. The host reveals Door %d to reveal a goat.\nWould you like to change your choice?\nEnter 4 if you do not wish to change, otherwise enter the number of the door you are choosing:", choice, openDoor);
    int num;

    scanf("%d", &num);

    while (num == openDoor || num < 0 || (num > 2 && num != 4))
    {
        printf("You chose the open door, or your input was invalid. Try again:");
        scanf("%d", &num);
    }
    // contestant changed his mind
    if (num != 4 && num != choice)
    {
        choice = num;
    }
    else if (choice == num)
    {
    }

    printf("Your final choice is %d.\nLet's see...", choice);

    if (doors[choice].has_prize == 1)
    {
        printDoorsWithCar(choice);

        printf("YOU WIN\n");
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            if (doors[i].has_prize == 1)
            {
                printDoorsWithCar(i);
                break;
            }
        }
        printf("YOU LOSE\n");
    }
}

void simulatedGame()
{
    srand(time(NULL));

    int winsWithoutChange = 0;
    int winsWithChange = 0;
    int numOfIterations = 1000;
    for (int iteration = 0; iteration < numOfIterations; iteration++)
    {
        // Initialize doors
        Door doors[3];
        for (int i = 0; i < 3; i++)
        {
            doors[i].has_prize = 0;
        }

        // Randomly place the prize
        int prizeDoor = rand() % 3;
        doors[prizeDoor].has_prize = 1;

        // Player makes an initial choice
        int choice = rand() % 3;

        // Host opens a door with a goat (not the chosen door or the prize door)
        int openDoor = -1;
        while (openDoor == -1)
        {
            int temp = rand() % 3;
            if (doors[temp].has_prize == 0 && temp != choice)
            {
                openDoor = temp;
            }
        }

        // Determine the final choice
        int finalChoice = choice;
        if (iteration >= numOfIterations / 2)
        {
            // Simulate switching choice for iterations >= 50
            for (int i = 0; i < 3; i++)
            {
                if (i != choice && i != openDoor)
                {
                    finalChoice = i;
                    break;
                }
            }
        }

        // Check if the final choice wins the prize
        if (doors[finalChoice].has_prize == 1)
        {
            if (iteration < numOfIterations / 2)
            {
                winsWithoutChange++;
            }
            else
            {
                winsWithChange++;
            }
        }
    }

    printf("Results after %d simulations:\n", numOfIterations);
    printf("Wins without changing choice: %d/%d\n", winsWithoutChange, numOfIterations / 2);
    printf("Wins with changing choice: %d/%d\n", winsWithChange, numOfIterations / 2);
}

int main()
{
    // manualGame();
    printf("Enter 1 to play the game manually, or enter 2 to simulate the game for 1000 iterations.\n");
    int num;
    scanf("%d", &num);
    if (num == 1)
    {
        manualGame();
    }
    else
    {
        simulatedGame();
    }

    return 0;
}