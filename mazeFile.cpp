#include <iostream>
#include <iomanip>
#include <termios.h>
#include "random"
#include <unistd.h>
#include "string"
#include "chrono"
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;
// -------------------------------------- Polished Version Of Beta Maze Game -------------------------------------- //

void entryMenu(){
    std::cout << "#################################################" << endl;
    std::cout << "              Welcome To The Maze" << endl;
    std::cout << "#################################################" << endl << endl;
    std::cout << "A - Enter The Maze (If You Dare)" << endl;
    std::cout << "B - Create Your Own Maze (Under Construction)" << endl;
    std::cout << "C - Settings" << endl;
    std::cout << "D - Import Game" << endl;
    std::cout << "E - Save Game" << endl;

};

class Maze {
private:
    bool vanishOn;
    char around = ' ';
    char userIcon = 'A';
    int playerPoints;
    int trap;
    bool gameWon;

    static const int ROWS = 20;
    static const int COLS = 51;
    char gameBoard[ROWS][COLS];
    int playerRow;
    int playerCol;
    bool gameRunning;
    string text;
    // Game Board Output
    void printGameBoard() {
        std::cout << "###################################################################################################" << endl;
        std::cout << "                                     " << text << endl;
        std::cout << "###################################################################################################" << endl;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                std::cout << gameBoard[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "___________________________________________________________________________________________________" << endl;
        std::cout << "A - Player Icon                         v - Vanish Item                         # - Wall Watch Out!" << endl;
        std::cout << "___________________________________________________________________________________________________" << endl;
    }

    // Check Condition
    bool check(){
        // Inisibility Move Coutrapter
        if(trap > 0){
            trap--;
        }
        else if(trap == 0){
            text = "Welcome To Death Maze";
            userIcon= 'A';
        }
        if(gameBoard[playerRow][playerCol] == '#'){
            system("clear");
            cout << "YOURE DEAD" << endl;
            return false;
        }
        else if(playerCol == COLS-1){
            system("clear");
            cout << "Congrats!!! You Escaped... This time..." << endl;
            gameWon = true;
            return false;
        }
        else if((gameBoard[playerRow][playerCol] == 'v') && (vanishOn == true)){
            trap+=3; 
            userIcon = ' ';
            text = "Player Has Vanished...";
            return true;
            playerPoints = playerPoints + 100;
        }
        return true;
    }

    int getch() {
        struct termios oldSettings, newSettings;
        tcgetattr(STDIN_FILENO, &oldSettings);
        newSettings = oldSettings;
        newSettings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
        int c = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
        return c;
    }

public:
    Maze();

    // Default Board Creation
    Maze(char defaultBoard[ROWS][COLS]){
        vanishOn = true;
        trap = 0;
        playerPoints = 0;
        text = "Welcome To Death Maze";
        playerRow = 2;
        playerCol = 2;
        memcpy(gameBoard, defaultBoard, sizeof(gameBoard));
    }
    int runGame(){
        playerPoints = 0;
        trap = 0;
        playerRow = 2;
        playerCol = 2;
        gameBoard[playerRow][playerCol] = userIcon;
        gameRunning = true;
        // only for entry no digit significance
        char console;
        while (gameRunning) {
            system("clear");  // Clear console screen
            printGameBoard();

            // Get user input
            int key = getch();
            switch (key) {
                case 'w':  // Up
                    if (playerRow > 0) {
                        gameBoard[playerRow][playerCol] = around;
                        playerRow--;
                        gameRunning = check();
                        gameBoard[playerRow][playerCol] = userIcon;
                    }
                    break;
                case 's':  // Down
                    if (playerRow < ROWS - 1) {
                        gameBoard[playerRow][playerCol] = around;
                        playerRow++;
                        gameRunning = check();
                        gameBoard[playerRow][playerCol] = userIcon;
                    }
                    break;
                case 'a':  // Left
                    if (playerCol > 0) {
                        gameBoard[playerRow][playerCol] = around;
                        playerCol--;
                        gameRunning = check();
                        gameBoard[playerRow][playerCol] = userIcon;
                    }
                    break;
                case 'd':  // Right
                    if (playerCol < COLS - 1) {
                        gameBoard[playerRow][playerCol] = around;
                        playerCol++;
                        gameRunning = check();
                        gameBoard[playerRow][playerCol] = userIcon;
                    }
                    break;
                case '~':
                    std::cout << "Enter Any Input To Quit Debug Console" << endl;
                    std::cout << "Maze Dimensions :" << ROWS << "," << COLS << endl;
                    std::cout << "Player Position :" << playerRow << "," << playerCol << endl;
                    std::cout << "Player Points :" << playerPoints << endl;
                    std::cout << "Vanish Moves Till Exit : " << trap << endl;
                    std::cout << '~';
                    std::cin >> console;
                    break;

                case 'q':  // Quit game
                    gameRunning = false;
                    break;
            }
        }
        gameBoard[playerRow][playerCol] = ' ';
        return playerPoints;
    }
    void settings(){
        system("clear");
        std::cout << "#################################################" << endl;
        std::cout << "                  Game Settings" << endl;
        std::cout << "#################################################" << endl;
        int xCoord, yCoord;
        char settingsChoice;
        while(settingsChoice != 'X'){
            std::cout << "A - Disable Vanishing" << endl;
            std::cout << "B - Enable Vanishing" << endl;
            std::cout << "X - Exit Settings" << endl;
            std::cin >> settingsChoice;
            settingsChoice = toupper(settingsChoice);
            switch (settingsChoice)
            {
            case 'A':
                vanishOn = false;
                break;
            case 'B':
                vanishOn = true;
                break;
        
            default:
                break;
            }
            system("clear");
        }
    }
    void build(){
        userIcon = 'A';
        for(int i=0; i < ROWS; i++){
            for(int x= 0; x < COLS; x++){
                gameBoard[i][x] = '#';
            }
        }
        playerPoints = 0;
        trap = 0;
        playerRow = 2;
        playerCol = 2;
        gameBoard[playerRow][playerCol] = userIcon;
        gameRunning = true;
        // only for entry no digit significance
        char console;
        while (gameRunning) {
            system("clear");  // Clear console screen
            printGameBoard();

            // Get user input
            int key = getch();
            switch (key) {
                case 'w':  // Up
                    if (playerRow > 0) {
                        gameBoard[playerRow][playerCol] = around;
                        playerRow--;
                        gameBoard[playerRow][playerCol] = userIcon;
                    }
                    break;
                case 's':  // Down
                    if (playerRow < ROWS - 1) {
                        gameBoard[playerRow][playerCol] = around;
                        playerRow++;
                       
                        gameBoard[playerRow][playerCol] = userIcon;
                    }
                    break;
                case 'a':  // Left
                    if (playerCol > 0) {
                        gameBoard[playerRow][playerCol] = around;
                        playerCol--;
                   
                        gameBoard[playerRow][playerCol] = userIcon;
                    }
                    break;
                case 'd':  // Right
                    if (playerCol < COLS - 1) {
                        gameBoard[playerRow][playerCol] = around;
                        playerCol++;
                        gameBoard[playerRow][playerCol] = userIcon;
                    }
                    break;
                case 'b':
                    around = '#';
                    text = "     In Build Mode";
                    break;
                
                case 'n':
                    around = ' ';
                    text = "Create Your Own Maze!";
                    break;
                case '~':
                    std::cout << "Enter Any Input To Quit Debug Console" << endl;
                    std::cout << "Maze Dimensions :" << ROWS << "," << COLS << endl;
                    std::cout << "Player Position :" << playerRow << "," << playerCol << endl;
                    std::cout << "Player Points :" << playerPoints << endl;
                    std::cout << "Vanish Moves Till Exit : " << trap << endl;
                    std::cout << '~';
                    std::cin >> console;
                    break;

                case 'q':  // Quit game
                    gameRunning = false;
                    break;
            }
        }
        gameBoard[playerRow][playerCol] = ' ';
    }
    void import(){
        char temp;
        string fileName;
        std::cout << "Enter File Name... (Must Be Within Program Directory)" << endl;
        std::cout << "Dimensions MUST BE 25 x 50" << endl;
        std::cin >> fileName;
        std::ifstream inputFile(fileName);

    
        if(inputFile.is_open()) {
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    
                    inputFile.get(temp);
                    if(temp != '\n'){
                        gameBoard[i][j] = temp;
                    }
                    
                }
            }
        inputFile.close();
        } else {
            std::cout << "Failed to open the file." << std::endl;
        }
    }
    void save(){
        char temp;
        string fileName;
        cout << "Enter Save File Name" << endl;
        cin >> fileName;
        std::ofstream outputFile(fileName);
        if(outputFile.is_open()) {
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    outputFile << gameBoard[i][j];
                }
                std::cout << '\n';
            }
            outputFile.close();
        }
        else {
            std::cout << "Failed to open the file." << std::endl;
        }
    }
};


int main(){
    int lastScore;
    char choice = ' ';
    char defaultBoard[20][51] = {
    {'#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', '#', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' '},
    {'#', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', 'v', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' '},
    {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', ' '},
    {'#', ' ', '#', '#', '#', ' ', '#', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', 'v', '#', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'v', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', 'v', '#', ' ', '#', ' ', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', ' ', ' '},
    {'#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#', '#', '#', 'v', '#', '#', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', 'v', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', '#'},
    {'#', '#', '#', ' ', '#', ' ', ' ', '#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', '#', '#', ' ', ' ', ' ', 'v', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', 'v', '#', ' ', ' ', ' ', ' ', ' ', '#', ' '},
    {' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', 'v', '#', ' ','#', '#', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', 'v', '#', ' ', '#', '#', '#', ' ', '#', '#',' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' '},
    {'#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', ' ', ' ', '#', '#', 'v', 'v', 'v', '#', '#', ' ', ' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#','#', '#', '#', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', ' '},
    {' ', ' ', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', '#', 'v', 'v', 'v', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',' ', '#', ' ', ' ', '#', 'v', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', ' ', ' ', '#', ' ', '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', '#', ' ',' ', '#', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#',' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', 'v', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', ' ', '#', '#', '#'},
    {'#', '#', ' ', '#', '#', ' ', ' ', '#', ' ', '#', '#', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', '#', '#', ' ', '#','#', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', '#', 'v', '#', ' ', '#', ' ', '#', ' ', ' ', ' '},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ',' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', '#'},
    {' ', '#', '#', 'v', ' ', '#', 'v', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#','#', ' ', ' ', ' ', '#', 'v', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', 'v', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {' ', ' ', '#', 'v', '#', '#', 'v', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ','#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', '#', '#', '#', 'v', ' ', ' ', '#', ' ', '#', '#', '#', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', ' ', ' ','#', '#', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
    Maze mazeArray(defaultBoard);

    while(choice != 'X'){
        entryMenu();
        std::cin >> choice;
        choice = toupper(choice);
        switch (choice)
        {
        case 'A':
            lastScore = mazeArray.runGame();
            break;
        
        case 'B':
            mazeArray.build();
            break;
        
        case 'C':
            mazeArray.settings();
            break;
        
        case 'D':
            mazeArray.import();
            break;

        case 'E':
            mazeArray.save();
            break;

        } 
        system("clear");  
    }
}