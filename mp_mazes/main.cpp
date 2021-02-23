#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"
using namespace cs225;
using namespace std;

int main()
{
    // Write your own main here
    SquareMaze test;
    PNG* answer = test.drawCreativeMaze();
    answer->writeToFile("answer.png");
    return 0;
}
