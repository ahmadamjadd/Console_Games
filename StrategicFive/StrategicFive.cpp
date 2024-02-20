// I formatted document using Shift+Alt+F. That's why this much space is included in this code!
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <iomanip>
#include <windows.h>
#include <mmsystem.h>


#pragma comment(lib, "winmm.lib")
using namespace std;

// defining color codes with their names to use them easily afterwards
#define RESET_COLOR "\033[0m"
#define BOLD "\033[1m"
#define BLUE_COLOR "\033[1;34m"
#define GREEN_COLOR "\033[1;32m"
#define YELLOW_COLOR "\033[1;33m"
#define RED_COLOR "\033[1;31m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BGWHITE "\033[47m"

// function prototype for printing text in centre and to change color of selected option
void printCenteredText(string text, bool isSelected);
//function prototype of playing music
void playMusic(const char* filePath);

// class definition
class Game
{
private:
    int BoardSize;
    char **Board;
    char CurrentPlayer;
    int choice;
    int row, column;
    int BotRow, BotColumn;

public:
    Game(){};
    Game(int BoardSize)
    {
        this->BoardSize = BoardSize;
        Board = new char *[BoardSize];//dynamic memory allocation using double pointers
        for (int i = 0; i < BoardSize; ++i)
        {
            Board[i] = new char[BoardSize];
            for (int j = 0; j < BoardSize; j++)
            {
                Board[i][j] = ' ';//setting board values to empty space
            }
        }
    }
    friend void printCenteredText(string text, bool isSelected); // declaring this function as friend so it can use private variables of class
    void displayBoard();                                         // function for displaying of board
    bool CheckWin();                                             // function for checking if the player has won
    bool CheckDraw();                                            // function checking if there is a draw
    void Bot();                                                  // function for generating moves by computer
    void PlayGame();                                             // function for playing the entire game
};

int main()
{
    int size;
    int menuOption = 1; // Track the selected menu option

    playMusic("3 Minute Timer - Relaxing Music (320 kbps).mp3");

    while (true)
    {
        system("cls"); // clears screen

        cout << endl;
        cout << MAGENTA << "           ###                        ###                        ###                         ####    ###                    \n"
             << RESET_COLOR;
        cout << MAGENTA << " ######  #######   #####    #####   #######   #####    ######            ######             ###             ###  ##   #####\n"
             << RESET_COLOR;
        cout << CYAN << "###        ###    ###  ##       ##    ###    ###  ##  ###  ##    ###    ###                ######    ###    ###  ##  ###  ##\n"
             << RESET_COLOR;
        cout << CYAN << " #####     ###    ###       ######    ###    #######  ###  ##    ###    ###                 ###      ###    ###  ##  #######\n"
             << RESET_COLOR;
        cout << GREEN_COLOR << "     ##    ###    ###      ###  ##    ###    ###       ######    ###    ###                 ###      ###     #####   ###   \n"
             << RESET_COLOR;
        cout << GREEN_COLOR << "######      ####  ###       ######     ####   #####        ##    ###     ######             ###      ###      ###     #####\n"
             << RESET_COLOR;
        cout << GREEN_COLOR << "                                                       #####                                                               \n"
             << RESET_COLOR;
        cout << endl;

        printCenteredText("Choose Board Size:", false);
        printCenteredText("9x9", menuOption == 1);
        printCenteredText(" 15x15", menuOption == 2);

        int key = getch(); // Get input from user without need for Enter key
        // if w is presses 9x9 changes color, otherwise 15x15 changes color
        switch (key)
        {
        case 'w':
            Beep(400, 250);
            menuOption = 1;
            break;
        case 's':
            Beep(400, 250);
            menuOption = 2;
            break;
        case '\r': // if enter key is pressed, game will be played
            size = (menuOption == 1) ? 9 : 15;
            Game Play(size);
            Play.PlayGame();
            if (Play.CheckWin() || Play.CheckDraw())
            {
                system("pause");
                return 0; // Exit the program after the game is over
            }
            break;
        }
        
    }
   

    return 0;
}

// function definition for displaying board
void Game ::displayBoard()
{
    // Display column coordinates above the board
    cout << "    ";
    for (int col = 0; col < BoardSize; ++col)
    {
        cout << setw(3) << col << " ";
    }
    cout << endl;

    // Display the rest of the board
    cout << "   ";
    for (int col = 0; col < BoardSize; ++col)
    {
        cout << YELLOW_COLOR << "----" << RESET_COLOR;
    }
    cout << endl;

    for (int i = 0; i < BoardSize; ++i)
    {
        // Display row coordinate on the left
        cout << setw(2) << i << " |";

        for (int j = 0; j < BoardSize; ++j)
        {
            if (Board[i][j] == ' ')
            {
                cout << "   ";
            }
            else
            {
                cout << (Board[i][j] == 'X' ? RED_COLOR : (Board[i][j] == 'O' ? GREEN_COLOR : "")) << " " << Board[i][j] << " " << RESET_COLOR;
            }

            // code for displaying board boundary
            cout << YELLOW_COLOR << "|" << RESET_COLOR;
        }

        cout << "\n";
        cout << "   ";
        for (int col = 0; col < BoardSize; ++col)
        {
            cout << YELLOW_COLOR << "----" << RESET_COLOR;
        }
        cout << endl;
    }

    cout << "\n";
}


// function declaration for checking if person has won
bool Game ::CheckWin()
{
    // Check rows
    for (int i = 0; i < BoardSize; ++i)
    {
        for (int j = 0; j <= BoardSize - 5; ++j)
        {
            bool win = true;
            for (int k = 0; k < 5; ++k)
            {
                if (Board[i][j + k] != CurrentPlayer)
                {
                    win = false;
                    break;
                }
            }
            if (win)
            {
                return true;
            }
        }
    }

    // Check columns
    for (int i = 0; i < BoardSize; ++i)
    {
        for (int j = 0; j <= BoardSize - 5; ++j)
        {
            bool win = true;
            for (int k = 0; k < 5; ++k)
            {
                if (Board[j + k][i] != CurrentPlayer)
                {
                    win = false;
                    break;
                }
            }
            if (win)
            {
                return true;
            }
        }
    }

    // Check diagonals
    for (int i = 0; i <= BoardSize - 5; ++i)
    {
        for (int j = 0; j <= BoardSize - 5; ++j)
        {
            bool winDiagonal1 = true;
            bool winDiagonal2 = true;
            for (int k = 0; k < 5; ++k)
            {
                if (Board[i + k][j + k] != CurrentPlayer)
                {
                    winDiagonal1 = false;
                }
                if (Board[i + k][j + 4 - k] != CurrentPlayer)
                {
                    winDiagonal2 = false;
                }
            }
            if (winDiagonal1 || winDiagonal2)
            {
                return true;
            }
        }
    }

    return false;
}

// function for checking if it's a draw
bool Game ::CheckDraw()
{
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            if (Board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}
void Game::Bot()
{
    CurrentPlayer = 'O';
    bool blockX = false;
    bool winO = false;

    // Check for consecutive 'X' in rows or columns
    for (int i = 0; i < BoardSize; ++i)
    {
        for (int j = 0; j <= BoardSize - 4; ++j)
        {
            // Check consecutive 'X' in rows
            if (Board[i][j] == 'X' && Board[i][j + 1] == 'X' && Board[i][j + 2] == 'X' && Board[i][j + 3] == ' ')
            {
                BotRow = i;
                BotColumn = j + 3;
                blockX = true; // Block X by placing 'O' after the sequence
            }

            // Check consecutive 'X' in columns
            if (Board[j][i] == 'X' && Board[j + 1][i] == 'X' && Board[j + 2][i] == 'X' && Board[j + 3][i] == ' ')
            {
                BotRow = j + 3;
                BotColumn = i;
                blockX = true; // Block X by placing 'O' after the sequence
            }
        }
    }

    // Check for consecutive 'X' in diagonals
    for (int i = 0; i <= BoardSize - 4; ++i)
    {
        for (int j = 0; j <= BoardSize - 4; ++j)
        {
            // Check consecutive 'X' in diagonals
            if (Board[i][j] == 'X' && Board[i + 1][j + 1] == 'X' && Board[i + 2][j + 2] == 'X' && Board[i + 3][j + 3] == ' ')
            {
                BotRow = i + 3;
                BotColumn = j + 3;
                blockX = true; // Block X by placing 'O' after the sequence
            }

            if (Board[i][j + 3] == 'X' && Board[i + 1][j + 2] == 'X' && Board[i + 2][j + 1] == 'X' && Board[i + 3][j] == ' ')
            {
                BotRow = i + 3;
                BotColumn = j;
                blockX = true; // Block X by placing 'O' after the sequence
            }
        }
    }

    // Check for consecutive 'O' in rows or columns
    if (!blockX)
    {
        for (int i = 0; i < BoardSize; ++i)
        {
            for (int j = 0; j <= BoardSize - 4; ++j)
            {
                // Check consecutive 'O' in rows
                if (Board[i][j] == 'O' && Board[i][j + 1] == ' ')
                {
                    BotRow = i;
                    BotColumn = j + 1;
                    winO = true; // Win by placing another 'O' after the sequence
                }

                // Check consecutive 'O' in columns
                if (Board[j][i] == 'O' && Board[j + 1][i] == ' ')
                {
                    BotRow = j + 1;
                    BotColumn = i;
                    winO = true; // Win by placing another 'O' after the sequence
                }
            }
        }
    }

    // If no blocking or winning move is needed, make a random move
    if (!blockX && !winO)
    {
        srand(time(0));
        BotRow = rand() % BoardSize;
        BotColumn = rand() % BoardSize;
    }
}

// function for playing whole game
void Game ::PlayGame()
{
    
    int menuoption = 1;

    while (true)
    {
        system("cls");
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        printCenteredText("Human VS Human", menuoption == 1);
        printCenteredText("Human VS Bot", menuoption == 2);
        char keys = getch();
        switch (keys)
        {
        case 'w':
            Beep(400, 250);
            menuoption = 1;
            break;
        case 's':
            Beep(400, 250);
            menuoption = 2;
            break;
        case '\r': // Enter key
            choice = menuoption;
            break;
        }

        if (choice != 0)
        {
            break;
        }
    }

    playMusic("3 Minute Timer - Epic Motivational Music (320 kbps).mp3");

    if (choice == 1) // Human VS Human
    {
        system("cls");
        displayBoard();
        CurrentPlayer = 'X';

        while (true)
        {
            cout << "Player " << CurrentPlayer << ", enter row and column (e.g., 0 1): ";
            cin >> row >> column;

            if (row < 0 || row >= BoardSize || column < 0 || column >= BoardSize || Board[row][column] != ' ')
            {
                cout << "Invalid Option! Try Again:\n";
                Beep(600, 1000);
                continue;
            }

            system("cls");
            // according to player turn, assign X or O to char array and then display board
            Board[row][column] = CurrentPlayer;
            CurrentPlayer == 'X' ? Beep(500, 500) : Beep(350, 500);
            displayBoard();

            // check draw
            if (CheckDraw())
            {
                system("cls");
                displayBoard();
                cout << "It's a draw!\n";
                cout << "Well Played!\n";
                break;
            }

            // check win
            if (CheckWin())
            {
                system("cls");
                displayBoard();
                cout << "Player " << CurrentPlayer << " wins!\n";
                break;
            }

            // Switch to the other player
            CurrentPlayer = (CurrentPlayer == 'X') ? 'O' : 'X';
        }
    }
    else if (choice == 2) // Human VS Bot
    {
        system("cls");
        displayBoard();
        CurrentPlayer = 'X';

        while (true)
        {
            if (CurrentPlayer == 'X') // Player X
            {
                cout << "Player " << CurrentPlayer << ", enter row and column (e.g., 0 1): ";
                cin >> row >> column;

                if (row < 0 || row >= BoardSize || column < 0 || column >= BoardSize || Board[row][column] != ' ')
                {
                    cout << "Invalid Option! Try Again:\n";
                    Beep(600, 1000);
                    continue;
                }

                Board[row][column] = CurrentPlayer; // Assigning player's move to array and then displaying board
                Beep(500, 500);
                system("cls");
                displayBoard();

                // check Draw
                if (CheckDraw())
                {
                    system("cls");
                    displayBoard();
                    cout << "It's a draw!\n";
                    cout << "Well Played!\n";
                    break;
                }

                // check Win
                if (CheckWin())
                {
                    system("cls");
                    displayBoard();
                    cout << "Player " << CurrentPlayer << " wins!\n";
                    break;
                }
            }
            else if (CurrentPlayer == 'O') // Bot
            {
                Bot();

                cout << "Bot " << CurrentPlayer << ", enter row and column (e.g., 0 1): ";
                Sleep(1000);
                row = BotRow;
                column = BotColumn;
                cout << row << " " << column << endl;
                Sleep(1000);

                if (row < 0 || row >= BoardSize || column < 0 || column >= BoardSize || Board[row][column] != ' ')
                {
                    cout << "Invalid move! Try again.\n";
                    continue;
                }

                Board[row][column] = CurrentPlayer; // assigning bot move to array and then displaying board
                system("cls");
                displayBoard();
                Beep(350, 500);

                // check win
                if (CheckWin())
                {
                    system("cls");
                    displayBoard();
                    cout << "Bot wins!\n";
                    break;
                }

                // check Draw
                if (CheckDraw())
                {
                    system("cls");
                    displayBoard();
                    cout << "It's a draw!\n";
                    cout << "Well Played!\n";
                    break;
                }
            }
            // Switch to the other player
            CurrentPlayer = (CurrentPlayer == 'X') ? 'O' : 'X';
        }
    }
    else
    {
        cout << "Invalid Option!!! Select Again!\n";
        cin >> choice;
    }
}

void printCenteredText(string text, bool isSelected)
{
    int screenWidth = 130; // total width of console
    int textLength = text.length();

    /// number of spaces to be left before text
    int spaces = (screenWidth - textLength) / 2;

    // print spaces and text accordingly
    cout << RESET_COLOR;
    if (isSelected)
    {
        cout << BOLD << RED_COLOR;
    }
    else
    {
        cout << YELLOW_COLOR;
    }

    cout << string(spaces, ' ') << text << RESET_COLOR << endl;
}

void playMusic(const char* filePath)
{
    // Stop the current music
    mciSendStringW(L"stop mp3", NULL, 0, NULL);
    mciSendStringW(L"close mp3", NULL, 0, NULL);

    // Convert narrow string to wide string
    wstring wideFilePath;
    wideFilePath.assign(filePath, filePath + strlen(filePath));

    // Open the new music file
    mciSendStringW((L"open \"" + wideFilePath + L"\" type mpegvideo alias mp3").c_str(), NULL, 0, NULL);

    // Play the new music
    mciSendStringW(L"play mp3", NULL, 0, NULL);
}

