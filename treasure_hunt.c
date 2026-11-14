#include <stdio.h>

#define MAP_SIZE 5
#define REGULAR_ATTEMPTS 5

int hiddenMap[MAP_SIZE][MAP_SIZE];
int selectedMap[MAP_SIZE][MAP_SIZE];
int playerScores[2];
int inputEnded;

/* Prints the game title and explains the rules. */
void displayWelcome(void)
{
    printf("==================================================\n");
    printf("       TREASURE HUNT - A Battle of Luck\n");
    printf("                  and Strategy\n");
    printf("==================================================\n");
    printf("Two players take turns searching a 5 x 5 map.\n");
    printf("Each player gets 5 regular turns and 1 lucky turn.\n");
    printf("A treasure is worth 10 points; a bonus spot is worth 5.\n");
    printf("Finds are shown on the map, but hidden spots stay secret.\n\n");
}

/* Clears the boards and places treasures and bonus spots. */
void initializeMap(void)
{
    int row;
    int column;

    for (row = 0; row < MAP_SIZE; row++)
    {
        for (column = 0; column < MAP_SIZE; column++)
        {
            hiddenMap[row][column] = 0;
            selectedMap[row][column] = 0;
        }
    }

    /* Secret treasure locations. */
    hiddenMap[0][1] = 1;
    hiddenMap[1][3] = 1;
    hiddenMap[2][0] = 1;
    hiddenMap[3][4] = 1;
    hiddenMap[4][2] = 1;

    /* Secret bonus locations. */
    hiddenMap[0][4] = 2;
    hiddenMap[2][2] = 2;
    hiddenMap[4][0] = 2;

    playerScores[0] = 0;
    playerScores[1] = 0;
}

/* Displays revealed picks without showing undiscovered locations. */
void displayMap(void)
{
    int row;
    int column;

    printf("\n                 TREASURE MAP\n");
    printf("       +---+---+---+---+---+\n");
    printf("       | 1 | 2 | 3 | 4 | 5 |\n");
    printf("+------+---+---+---+---+---+\n");

    for (row = 0; row < MAP_SIZE; row++)
    {
        printf("|  %d   ", row + 1);
        for (column = 0; column < MAP_SIZE; column++)
        {
            if (selectedMap[row][column] == 0)
            {
                printf("| ? ");
            }
            else if (hiddenMap[row][column] == 1)
            {
                printf("| T ");
            }
            else if (hiddenMap[row][column] == 2)
            {
                printf("| B ");
            }
            else
            {
                printf("| X ");
            }
        }
        printf("|\n");
        printf("+------+---+---+---+---+---+\n");
    }
    printf("Legend: ? = unexplored, X = empty, T = treasure, B = bonus\n");
}

/* Reads one integer, discarding a line if it contains invalid text. */
int readNumber(void)
{
    int number;
    int character;
    int status;

    while (1)
    {
        status = scanf("%d", &number);
        if (status == 1)
        {
            inputEnded = 0;
            return number;
        }
        if (status == EOF)
        {
            inputEnded = 1;
            return 0;
        }

        printf("Please enter a whole number: ");
        do
        {
            character = getchar();
        } while (character != '\n' && character != EOF);
    }
}

int calculateScore(int row, int column);

/* Lets one player choose a valid unused spot, then updates the score. */
int playerTurn(int playerNumber, int turnNumber, int isBonusRound)
{
    int row;
    int column;
    int points;

    if (isBonusRound)
    {
        printf("\n*** LUCKY BONUS ROUND: Player %d gets one extra pick! ***\n",
               playerNumber);
    }
    else
    {
        printf("\nPlayer %d - attempt %d of %d\n",
               playerNumber, turnNumber, REGULAR_ATTEMPTS);
    }

    while (1)
    {
        printf("Choose a row (1-5): ");
        row = readNumber();
        if (inputEnded == 1)
        {
            return 0;
        }

        printf("Choose a column (1-5): ");
        column = readNumber();
        if (inputEnded == 1)
        {
            return 0;
        }

        if (row < 1 || row > MAP_SIZE || column < 1 || column > MAP_SIZE)
        {
            printf("That spot is outside the map. Try again!\n");
        }
        else if (selectedMap[row - 1][column - 1] == 1)
        {
            printf("That spot has already been searched. Pick another!\n");
        }
        else
        {
            break;
        }
    }

    selectedMap[row - 1][column - 1] = 1;
    points = calculateScore(row - 1, column - 1);
    playerScores[playerNumber - 1] += points;

    if (hiddenMap[row - 1][column - 1] == 1)
    {
        printf("TREASURE! You found the loot. The map owes you a high-five!\n");
    }
    else if (hiddenMap[row - 1][column - 1] == 2)
    {
        printf("BONUS! A lucky stash! Even the X marks the spot today!\n");
    }
    else
    {
        printf("Nothing here! The ground says, \"Nice try, explorer!\"\n");
    }

    printf("Player 1: %d points | Player 2: %d points\n",
           playerScores[0], playerScores[1]);
    displayMap();
    return 1;
}

/* Returns 10 for treasure, 5 for a bonus spot, or 0 for an empty spot. */
int calculateScore(int row, int column)
{
    if (hiddenMap[row][column] == 1)
    {
        return 10;
    }
    else if (hiddenMap[row][column] == 2)
    {
        return 5;
    }
    return 0;
}

/* Announces the final scores and declares the winner or a tie. */
void displayResults(void)
{
    printf("\n==================================================\n");
    printf("                 FINAL TREASURE TALLY\n");
    printf("==================================================\n");
    printf("Player 1: %d points\n", playerScores[0]);
    printf("Player 2: %d points\n", playerScores[1]);

    if (playerScores[0] > playerScores[1])
    {
        printf("\nThe crown goes to PLAYER 1! What a legendary loot grab!\n");
    }
    else if (playerScores[1] > playerScores[0])
    {
        printf("\nPLAYER 2 is the treasure champion! The loot is yours!\n");
    }
    else
    {
        printf("\nIt's a tie! The treasure chest belongs to both explorers!\n");
    }
    printf("Thanks for playing TREASURE HUNT!\n");
}

int main(void)
{
    int attempt;
    int player;

    displayWelcome();
    initializeMap();
    displayMap();

    for (attempt = 1; attempt <= REGULAR_ATTEMPTS; attempt++)
    {
        for (player = 1; player <= 2; player++)
        {
            if (playerTurn(player, attempt, 0) == 0)
            {
                printf("\nInput ended. Game over.\n");
                return 0;
            }
        }
    }

    for (player = 1; player <= 2; player++)
    {
        if (playerTurn(player, REGULAR_ATTEMPTS + 1, 1) == 0)
        {
            printf("\nInput ended. Game over.\n");
            return 0;
        }
    }

    displayResults();
    return 0;
}
