#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cctype> // for character-based functions
#include "include/snake.h"
#include "include/apple.h"

#define CONSOLE_CLEAR "cls" //cls for window, clear for linux

using namespace std;

const int WIDTH = 50, HEIGHT = 25;

void board(Snake &mainSnake, Apple &mainApple);
void board(Snake mainSnake);
char getKeyPress();

int main () {

    Snake                   mainSnake = Snake();
    Apple                   mainApple = Apple(HEIGHT, WIDTH);
    bool                    continueGame{true};
    bool                    resetGame{false};

    while (true) {
        if (kbhit()){
            // switch (getch()) {
            //     case 'w' : mainSnake.direction = 'u'; break;
            //     case 'a' : mainSnake.direction = 'l'; break;
            //     case 'd' : mainSnake.direction = 'r'; break;
            //     case 's' : mainSnake.direction = 'd'; break;
            //     case '\r': mainSnake.direction = 'p'; break;    //ENTER
            //     case ' ' : continueGame = false; break;         //SPACE
            //     case '\033' : continueGame = false; break;      //ESC
            // }

            switch (getKeyPress()) {
                case 'u' : mainSnake.direction = 'u'; break;
                case 'l' : mainSnake.direction = 'l'; break;
                case 'r' : mainSnake.direction = 'r'; break;
                case 'd' : mainSnake.direction = 'd'; break;
                case 'p' :
                    mainSnake.direction = 'p';
                    cout << "____ pause game ____________";
                    Sleep(2000);
                    break;                                      // pause game
                case 'o' : resetGame           = true; break;   // reset game
                case 'e' : continueGame        = false; break;  // exit game
            }

            if (!continueGame) {
                cout << "____ exit game ____________";
                Sleep(1000);
                break;
            }

            if (resetGame) {
                cout << "____ reset game ____________";
                Sleep(2000);
                mainSnake = Snake();
                mainApple = Apple(HEIGHT, WIDTH);
                resetGame = false;
            }
        }

        // moving
        mainSnake.move();

        // check collision

        // drawing        
        // board(mainSnake);
        board(mainSnake, mainApple);
        // board(&mainSnake, &mainApple);

        // check food
        bool appleEaten = mainSnake.CheckApple(mainApple);

        if (appleEaten) {
            mainApple.newApple();
        }        

        Sleep(50);
    };

    system(CONSOLE_CLEAR);
    return 0;
};

char getKeyPress() {
    // implementation of https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
    char keyPressed{'p'};
    char keyChar = getch();    
    // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {30, 30});
    // cout << "___" << (int)keyChar << "___________________________________";
    // Sleep(3000); // to kown what happened when arrow keys pressed

    switch (toupper(keyChar)) {
        case 'W'    : keyPressed = 'u'; break;      // up
        case 'A'    : keyPressed = 'l'; break;      // left
        case 'D'    : keyPressed = 'r'; break;      // right
        case 'S'    : keyPressed = 'd'; break;      // down
        case '\r'   : keyPressed = 'o'; break;      // reset //ENTER
        case ' '    : keyPressed = 'p'; break;      // pause //SPACE
        case '\033' : keyPressed = 'e'; break;      // exit  //ESC \033 or 27
        case -32    : // when arrow pressed, getch return -32 first then 72 75 77 80 or 'M' 'P' 'H' 'K' r d u r
            // if (getch()== 91) {                             // '[' or 91 to check/handle arrow keys
            switch (toupper(getch())) {                             // to check/handle arrow keys
                case  72   : keyPressed = 'u'; break;      // up or 'A' 65 72
                case  80   : keyPressed = 'd'; break;      // down or 'B' 66 80
                case  77   : keyPressed = 'r'; break;      // right or 'C' 67 77
                case  75   : keyPressed = 'l'; break;      // left or 'D' 68 75
            }
            // }
            break;
    }

    return keyPressed;
}

void board() {
    for (int i{0}; i < HEIGHT; ++i) {
        cout << "#";
        for (int j{1}; j < WIDTH - 1; ++j) {
            if ((i==0) || i==HEIGHT-1) cout << "#";
            else cout << " ";
        }
        cout << "#" << endl;
    }
}

void board(Snake mainSnake) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 1});

    for (int i{0}; i < HEIGHT; ++i) {
        cout << "#"; // cout << "\t\t\t#";
        for (int j{1}; j < WIDTH - 1; ++j) {
            if ((i==0) || i==HEIGHT-1) cout << "#";
            else if ((i == mainSnake.position[0][0]) && (j == mainSnake.position[0][1])) cout << "x";
            else cout << " ";
        }
        cout << "#" << endl;
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 1});
}

void board(Snake &mainSnake, Apple &mainApple) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 1});

    CONSOLE_CURSOR_INFO info;
    info.dwSize          = 100;
    info.bVisible        = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    bool isBody;

    for (int i{0}; i < HEIGHT; ++i) {

        info.bVisible        = TRUE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

        cout << "#"; // cout << "\t\t\t#";

        info.bVisible        = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

        for (int j{1}; j < WIDTH - 1; ++j) {

            isBody = false;

            if ((i==0) || i==HEIGHT-1) {
                info.bVisible        = TRUE;
                SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

                cout << "#";

                info.bVisible        = FALSE;
                SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
            }
            else if ((i == mainSnake.position[0][0]) && (j == mainSnake.position[0][1])) {
                info.bVisible        = TRUE;
                SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
                
                cout << "x";

                info.bVisible        = FALSE;
                SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);                
            }
            else if ((i == mainApple.position[0]) && (j == mainApple.position[1])) {
                info.bVisible        = TRUE;
                SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
                
                cout << "@";

                info.bVisible        = FALSE;
                SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);                
            }
            else {
                for (int k{1}; k < mainSnake.length; ++k) {
                    if ((i == mainSnake.position[k][0]) && (j == mainSnake.position[k][1])) {
                        info.bVisible        = TRUE;
                        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
                
                        
                        cout << "o";

                        info.bVisible        = FALSE;
                        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);                             
                        
                        isBody = true;
                        break;
                    }
                }

                if (!isBody) {
                    cout << " ";
                }
            }
        }
        info.bVisible        = TRUE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
                
        cout << "#" << endl;

        info.bVisible        = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);                                     
    }

    info.bVisible        = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 1});
}