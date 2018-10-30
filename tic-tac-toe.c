#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print(char gamespaces[], char board_print[]);
//adds | and \n chars to make a board--can scale for larger boards
//prints the whole board, with numbers and spaces

void play(char gamespaces[], char board_print[], char next_char);
//this function puts the char 'X' or 'O' in a space that is the inputted value -1
//also checks to see if that space alreay has 'X' or 'O' and gives an error message (missing a turn)

void check_end(char gamespaces[], char board_print[]);
//checks all winning combos, returns value for replay X won, replay O won, stop play
void restart(char gamespaces[]);
//resets for replay, does not reset reverse (which offsets the turn counter for switched play)

void tutorial(void);
//a short tutorial that explains how to play

int main(void)
{
    printf("Tic\nTac\nToe\n");
    printf("*****************************\n");

    tutorial();

    char board_print[24];
    char gamespaces[] = "123456789";
    char next_char = 'X';

    while (next_char == 'X' || next_char == 'O')//keeps it going--add a 'best out of #' prompt?
    {
        play(gamespaces, board_print, next_char);
        check_end(gamespaces, board_print);
        next_char = 'O';

        play(gamespaces, board_print, next_char);
        check_end(gamespaces, board_print);
        next_char = 'X';
    }
}

void tutorial(void)
{
    char c = 'a';

    do
    {
        printf("Would you like to see the Tutorial? (y/n)\n");
        c = getchar();
    }
    while (c != 'y' && c != 'n');

    if (c == 'n')
    {
        return;
    }

    else if (c == 'y')
    {
        printf("Here is the gameboard.\n");
        char board_print[24];
        printf("\n");

        char gamespaces[] = "123456789";
        print(gamespaces, board_print);
        sleep(2);

        printf("To play, enter the number of the space where you would like to play.\n\nLike this...\n\n");

        print(gamespaces, board_print);
        sleep(2);

        printf("1 [enter]\n\n");
        sleep(1);

        printf("Then you'll see that number replaced by X or O.\n");
        sleep(3);

        printf("|X|2|3|\n|4|5|6|\n|7|8|9|\n");
        sleep(2);

        printf("Let's get started.\n\n\n");
        sleep(2);
    }
}

void print(char gamespaces[], char board_print[])
{

    int grid_size = 3; //3*3 grid for tictactoe (change grid_size for larger games)
    int with_newline = grid_size * (grid_size + 1); //size if we format the string into a grid (\n every n'th char)
    int total_board = with_newline * 2; //size with | characters (added every other char)

    int space_count = 0;

    for (int a = 0; a < total_board - 1; a++)
    {
        if (a % 2 == 0)
        {
            board_print[a] = '|';
        }

        else if (a == 7 || a == 15 || a == 23)
        {
            board_print[a] = '\n';
        }

        else
        {
            board_print[a] = gamespaces[space_count];
            space_count++;
        }
    }
    //prints the whole thing out

    printf("\n\n");

    for (int b = 0; b < total_board; b++)//24 chars total including numbers, |, and \n
    {
        printf("%c", board_print[b]);
    }

    printf("\n");
}

void play(char gamespaces[], char board_print[], char next_char)
{
    print(gamespaces, board_print);

    int player_input = 0;

    printf("%c, choose a space to play.\nEnter the number and press enter.\n", next_char);
    scanf(" %d", &player_input);

    printf("*****************************\n\n\n");

    int player_space = player_input - 1; //subtracting 1 for zero indexed board spaces

    for (int c = 0; c <= 8; c++)//counts through all board spaces
    {
        if ((c == player_space) && (gamespaces[c] == 'X' || gamespaces[c] == 'O'))
        {
            printf("That space was already played: you lose a turn.");

            return;
        }

        else if (c == player_space)
        {
            gamespaces[c] = next_char;
        }
    }
}

void check_end(char gamespaces[], char board_print[])
{
    char again = 'a';

    //all winning combinations: 123, 456, 789, 147, 258, 369, 159, 357
    //zero indexed: 012, 345, 678, 036, 147, 258, 048, 246
    if ((gamespaces[0] == 'X' && gamespaces[1] == 'X' && gamespaces[2] == 'X')
        || (gamespaces[3] == 'X' && gamespaces[4] == 'X' && gamespaces[5] == 'X')
        || (gamespaces[6] == 'X' && gamespaces[7] == 'X' && gamespaces[8] == 'X')
        || (gamespaces[0] == 'X' && gamespaces[3] == 'X' && gamespaces[6] == 'X')
        || (gamespaces[1] == 'X' && gamespaces[4] == 'X' && gamespaces[7] == 'X')
        || (gamespaces[2] == 'X' && gamespaces[5] == 'X' && gamespaces[8] == 'X')
        || (gamespaces[0] == 'X' && gamespaces[4] == 'X' && gamespaces[8] == 'X')
        || (gamespaces[2] == 'X' && gamespaces[4] == 'X' && gamespaces[6] == 'X'))
    {
        print(gamespaces, board_print);

        printf("X wins. Would you like to play again? (y/n)\n");
        scanf(" %c", &again);
    }

    else if ((gamespaces[0] == 'O' && gamespaces[1] == 'O' && gamespaces[2] == 'O')
             || (gamespaces[3] == 'O' && gamespaces[4] == 'O' && gamespaces[5] == 'O')
             || (gamespaces[6] == 'O' && gamespaces[7] == 'O' && gamespaces[8] == 'O')
             || (gamespaces[0] == 'O' && gamespaces[3] == 'O' && gamespaces[6] == 'O')
             || (gamespaces[1] == 'O' && gamespaces[4] == 'O' && gamespaces[7] == 'O')
             || (gamespaces[2] == 'O' && gamespaces[5] == 'O' && gamespaces[8] == 'O')
             || (gamespaces[0] == 'O' && gamespaces[4] == 'O' && gamespaces[8] == 'O')
             || (gamespaces[2] == 'O' && gamespaces[4] == 'O' && gamespaces[6] == 'O'))
    {
        print(gamespaces, board_print);

        printf("O wins. Would you like to play again? (y/n)\n");
        scanf(" %c", &again);
    }

    else if (gamespaces[0] != '1' && gamespaces[1] != '2' && gamespaces[2] != '3' &&
             gamespaces[3] != '4' && gamespaces[4] != '5' && gamespaces[5] != '6' &&
             gamespaces[6] != '7' && gamespaces[7] != '8' && gamespaces[8] != '9')
    {
        print(gamespaces, board_print);

        printf("Cat's Game. Would you like to play again? (y/n)\n");
        scanf(" %c", &again);
    }

    if (again == 'y')
    {
        restart(gamespaces);
    }

    if (again == 'n')
    {
        printf("\nThanks for playing.\n");
        exit(0);
    }
}

void restart(char gamespaces[])
{
    char reset_spaces[] = "123456789";

    //sets gamespaces to default values (1-9)
    for (int d = 0; d <= 8; d++)
    {
        gamespaces[d] = reset_spaces[d];
    }
}