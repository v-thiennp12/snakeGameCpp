#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "apple.h"

using namespace std;

class Snake {
    public:
        Snake(vector<vector<int>> position, int velocity);
        Snake();

        void ChangeDirection(char direction);
        void move();
        bool CheckApple(Apple apple);

        vector<vector<int>> position; // {{0,0}}; [i][0] row, [i][0] col
        int length;                   // {1};
        int velocity;                 // {0};
        char direction;               // {'p'}; // p pause, u up, d down, l left, r right        

    private:
};

Snake::Snake(vector<vector<int>> position, int velocity) {
    this->position      = position;
    this->velocity      = velocity;
    this->length        = position.size();
    this->direction     = 'p';
}

Snake::Snake() {
    this->position      = {{1,1}};
    this->velocity      = 1;
    this->length        = 1;
    this->direction     = 'p';           
}

bool Snake::CheckApple(Apple apple) {
    bool appleEaten{false};

    if ((apple.position[0] == this->position[0][0]) && (apple.position[1] == this->position[0][1])) {
        appleEaten      = true;
        this->position.push_back(this->position[this->length - 1]);
        this->length   += 1;        
    }
    return appleEaten;
}

void Snake::ChangeDirection(char direction) {
    this->direction = direction;
}

void Snake::move() {
    // body's move
    switch (direction) {
        case 'u' :
        case 'd' :
        case 'l' :
        case 'r' :
            for (int i{this->length - 1}; i > 0; --i) {
                position[i] = position[i - 1];
            }
    }
    //head's move
    switch (direction) {
        case 'u' :
            position[0][0] -= 1;
            break;
        case 'd' :
            position[0][0] += 1;
            break;
        case 'l' :
            position[0][1] -= 1;
            break;
        case 'r' :
            position[0][1] += 1;
            break;
    }
}

#endif