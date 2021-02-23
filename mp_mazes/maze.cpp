/* Your code here! */
#include "maze.h"
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
using namespace cs225;
using namespace std;
#include <iostream>
#include <queue>
//need destructor?
SquareMaze::SquareMaze() {
}
SquareMaze::~SquareMaze() {
}
//randomly pick wawll
//using maze_ check if the nodes are in the same set, if not remove wall and unino them into a set.
//keep going?
//cycle happens when a pair of nodes comes back to itself
//find sees if the "walls" are in same set
void SquareMaze::makeMaze(int width, int height) {
  width_ = width;
  height_ = height;
  downWalls.resize(width_ * height_);
  rightWalls.resize(width_ * height_);
  for (int k = 0; k < (width_ * height_); k++) {
    downWalls[k] = true;
    rightWalls[k] = true;
  }
  //mazes_ holds #of disjoint (independent) sets, all sets are disjoint at start
  mazes_.addelements(width_ * height_);
  int sets = width_ * height_;
  //once you have 1 disjoin set left ur done bc one big conneceted tree
  while (sets != 1) {
    int randX = rand() % width_;
    int randY = rand() % height_;
    int randDir = rand() % 2;
    //+x check rightWalls
    if (randDir == 0) {
      if (rightWalls[(width_ * randY) + randX]) {
        //if not in same set, comibine, might need to boundry check the randX + 1 if randX is maxed out
        if (randX + 1 != width_) {
          if (mazes_.find((width_ * randY) + randX) != mazes_.find((width_ * randY) + randX + 1)) {
            setWall(randX, randY, 0, false);
            mazes_.setunion((width_ * randY) + randX, (width_ * randY) + randX + 1);
            sets--;
          }
        }
      }
    }
    //+y checkDownWalls
    if (randDir == 1) {
      if (downWalls[(width_ * randY) + randX]) {
        //if not in same set combine migh need to boundary check the randX + 1? if randX is maxed out
        if (randY + 1 != height_) {
          if (mazes_.find((width_ * randY) + randX) != mazes_.find((width_ * (randY + 1)) + randX)) {
            setWall(randX, randY, 1, false);
            mazes_.setunion((width_ * randY) + randX, (width_ * (randY + 1)) + randX);
            sets--;
          }
        }
      }
    }
  }
}

//might need basecase for dir < 0 dir > 3
bool SquareMaze::canTravel(int x, int y, int dir) const {
  //+x
  if (dir == 0) {
    return !(x + 1 >= width_ || rightWalls[(width_ * y) + x]);
  }
  //+y
  if (dir == 1) {
    return !(y + 1 >= height_ || downWalls[(width_ * y) + x]);
  }
  //-x
  if (dir == 2) {
    return !(x - 1 < 0 || rightWalls[(width_ * y) + (x - 1)]);
  }
  //-y
  if (dir == 3) {
    return !(y - 1 < 0 || downWalls[(width_ * (y - 1)) + x]);
  }
  //prevent reach end of nonvoid function error
  //should cause no problem unless assuming  0 <= dir <= 3
  return false;
}

//might need basecase for x y too big ?
//
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  if (dir == 0) {
    rightWalls[(width_ * y) + x] = exists;
  }
  if (dir == 1) {
    downWalls[(width_ * y) + x] = exists;
  }
}

//use cantravel to figure out next step
//backtrack to find combination of paths?
//once u find end return
//find lowest node, and then parent all the way up
//push_back backwards steps into answer, reverse
//bfs at eachh point to hold potential directions
//check each direction and if no good then pop it out of queue and vector
 std::vector<int> SquareMaze::solveMaze() {
   int currx = 0;
   int curry = 0;
   queue<int> possibleDirections;
   vector<int> parentnode;
   vector<int> paths; //use now
   vector<bool> visited;
   paths.resize(width_ * height_);
   parentnode.resize(width_ * height_);
   visited.resize(width_ * height_);
   visited[0] = true;
   possibleDirections.push(0);
   while (!possibleDirections.empty()) {
     int whereImAt = possibleDirections.front();
     int currx = whereImAt % width_;
     int curry = whereImAt / width_;
     possibleDirections.pop();
     if (canTravel(currx, curry, 0) && !visited[whereImAt + 1]) {
       possibleDirections.push(whereImAt + 1); //increment x by 1
       paths[whereImAt + 1] = paths[whereImAt] + 1; //increment how far away
       parentnode[whereImAt + 1] = whereImAt; //holds parent of respective "index" of "paths"
       visited[whereImAt + 1] = true; //makes sure you dont revisit
     }
     if (canTravel(currx, curry, 1) && !visited[whereImAt + width_]) {
       possibleDirections.push(whereImAt + width_); //increment y by 1
       paths[whereImAt + width_] = paths[whereImAt] + 1;
       parentnode[whereImAt + width_] = whereImAt;
       visited[whereImAt + width_] = true;
     }
     if (canTravel(currx, curry, 2) && !visited[whereImAt - 1]) {
       possibleDirections.push(whereImAt - 1); //increment x by -1
       paths[whereImAt - 1] = paths[whereImAt] + 1;
       parentnode[whereImAt - 1] = whereImAt;
       visited[whereImAt - 1] = true;
     }
     if (canTravel(currx, curry, 3) && !visited[whereImAt - width_]) {
       possibleDirections.push(whereImAt - width_); //increment y by -1
       paths[whereImAt - width_] = paths[whereImAt] + 1;
       parentnode[whereImAt - width_] = whereImAt;
       visited[whereImAt - width_] = true;
     }
   }
   return findActualPath(parentnode, findMaxDistanceFromOrigin(paths));
  }
  int SquareMaze::findMaxDistanceFromOrigin(vector<int> tempPath) {
    int answer = width_ * (height_ - 1);
    for (int k = 0; k < width_; k++) {
      if (tempPath[(width_ * (height_ - 1)) + k] > tempPath[answer]) {
        answer = (width_ * (height_ - 1) + k);
      }
    }
    return answer;
  }
  vector<int> SquareMaze::findActualPath(std::vector<int> parentNodes, int finalSpot) {
    vector<int> answer;
    int final = finalSpot;
    while (final != 0) {
      //parent is to the left of finalspot
      if (final - 1 == parentNodes[final]) {
        answer.push_back(0);
      }
      //parent is to the right of finalspot
      if (final + 1 == parentNodes[final]) {
        answer.push_back(2);
      }
      //parent is to the down of finalspot;
      if (final + width_ == parentNodes[final]) {
        answer.push_back(3);
      }
      //parent is to the top of finalspot;
      if (final - width_ == parentNodes[final]) {
        answer.push_back(1);
      }
      final = parentNodes[final];
    }
    reverse(answer.begin(), answer.end());
    return answer;
  }

 PNG* SquareMaze::drawMaze() const {
   PNG* new_png = new PNG(width_ * 10 + 1, height_ * 10 + 1);
   for (int x = 0; x < width_; x++) {
     for(int y = 0; y < height_; y++) {

       if (x == 0) {
         for (unsigned int k = 0; k < new_png->height(); k++){
           HSLAPixel& new_pix = new_png->getPixel(x, k);
           new_pix.l = 0.0;
         }
       }
       if (y == 0) {
         for (unsigned int k = x; k < new_png->width(); k++) {
           if (k + 10 < new_png->width()) {
             HSLAPixel& new_pix = new_png->getPixel(k + 10, y);
             new_pix.l = 0.0;
           }
         }
       }
       //right wall exists
       if (rightWalls[(width_ * y) + x]){
         for (unsigned int k = 0; k < 11; k++){
           HSLAPixel& new_pix = new_png->getPixel((x + 1) * 10, y * 10 + k);
           new_pix.l = 0.0;
         }
       }
      //down wall exists
      if (downWalls[(width_* y) + x]) {
        for (unsigned int k = 0; k < 11; k++) {
          HSLAPixel& new_pix = new_png->getPixel(x * 10 + k, (y + 1) * 10);
          new_pix.l = 0.0;
        }
      }
    }
  }
   return new_png;
 }

//drawMaze, then use solveMaze to find pathway
//then draw it on !
PNG* SquareMaze::drawMazeWithSolution() {
   //start at (5,5)
   PNG* new_png = drawMaze();
   std::vector<int> solved = solveMaze();
   int x = 5;
   int y = 5;

for(unsigned k = 0; k < solved.size() ; k++){
  //to the right
  if(solved[k] == 0) {
    for(int j = 0; j < 10; j++) {
      HSLAPixel& solution = new_png->getPixel(x,y);
      solution.h = 0.0;
      solution.s = 1.0;
      solution.l = 0.5;
      solution.a = 1.0;
      x++;
    }
  }
  //downward
  if(solved[k] == 1) {
    for(int j = 0; j < 10; j++) {
      HSLAPixel& solution = new_png->getPixel(x,y);
      solution.h = 0.0;
      solution.s = 1.0;
      solution.l = 0.5;
      solution.a = 1.0;
      y++;
    }
  }
  //to the left
  if(solved[k] == 2) {
    for(int j = 0; j < 10; j++) {
      HSLAPixel& solution = new_png->getPixel(x,y);
      solution.h =0.0;
      solution.s = 1.0;
      solution.l = 0.5;
      solution.a = 1.0;
      x--;
    }
  }
  //upward
  if(solved[k] == 3) {
    for(int j = 0; j < 10; j++) {
      HSLAPixel& solution = new_png->getPixel(x,y);
      solution.h =0.0;
      solution.s = 1.0;
      solution.l = 0.5;
      solution.a = 1.0;
      y--;
    }
  }
}
//create exit
  HSLAPixel& offByOne = new_png->getPixel(x, y);
  offByOne.h = 0.0;
  offByOne.s = 1.0;
  offByOne.l = 0.5;
  offByOne.a = 1.0;
  for(int i = 1; i < 10; i++) {
    HSLAPixel & exit = new_png->getPixel(x - 5 + i, new_png->height() - 1);
    exit.l = 1.0;
  }
  return new_png;
}

PNG* SquareMaze::drawCreativeMaze() {
  PNG* answer = new PNG(101, 101);
  for (int x = 0; x < 101; x++) {
    HSLAPixel& solution = answer->getPixel(x,0);
    solution.h =0.0;
    solution.s = 1.0;
    solution.l = 0.0;
    solution.a = 1.0;
  }
  for (int y = 0; y < 101; y++) {
    HSLAPixel& solution = answer->getPixel(100, y);
    solution.l = 0.0;
  }
  for (int k = 0; k < 10; k++) {
    HSLAPixel& solution = answer->getPixel(k + 1, 0);
    solution.l = 1.0;
  }
  for (int k = 0; k < 11; k++) {
    HSLAPixel& solution = answer->getPixel(0, k);
    solution.l = 0;
  }
  for (int x = 0; x < 91; x++) {
    HSLAPixel& solution = answer->getPixel(x, 10);
    solution.l = 0.0;
  }
  for (int y = 11; y < 101; y++) {
    HSLAPixel& solution = answer->getPixel(90, y);
    solution.l = 0.0;
  }
  return answer;
}
