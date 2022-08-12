#ifndef FOOD_H
#define FOOD_H

#include <vector>
#include <ctime>
#include <stdlib.h>

using namespace std;

class Apple {
    public:
        Apple();
        Apple(int boundary_row, int boundary_col);

        vector<int> position;           //{0,0}; row, col
        int HEIGHT, WIDTH;

        void newApple();
    private:
};

Apple::Apple(int HEIGHT, int WIDTH){
    this->WIDTH         = WIDTH;
    this->HEIGHT        = HEIGHT;
    this->position      = {(int)((HEIGHT-2)/2 + 1), (int)((WIDTH-2)/2 + 1)};

    srand(time(NULL));
    this->position[0] = 1 + rand() % (HEIGHT-2 + 1 - 1);  // row 1..HEIGHT-1
    this->position[1] = 1 + rand() % (WIDTH-2 + 1 - 1);   // col 1..WIDTH-1
}

void Apple::newApple() {
    // int r = minN + rand() % (maxN + 1 - minN)

    srand(time(NULL));
    position[0] = 1 + rand() % (HEIGHT-2 + 1 - 1);  // row 1..HEIGHT-1
    position[1] = 1 + rand() % (WIDTH-2 + 1 - 1);   // col 1..WIDTH-1
}

#endif