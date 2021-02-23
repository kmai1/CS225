/* Your code here! */
//add #include ...
#pragma once
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
class SquareMaze {
public:
  SquareMaze();
  ~SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  std::vector<int> solveMaze(); //include vector
  cs225::PNG* drawMaze() const; //include PNG class
  cs225::PNG* drawMazeWithSolution();
  std::vector<int> findActualPath(std::vector<int> parentPath, int finalSpot);
  int findMaxDistanceFromOrigin(std::vector<int> tempPath);
  cs225::PNG* drawCreativeMaze(); //uncomment once at part3

private:
  int width_;
  int height_;
  DisjointSets mazes_;
  std::vector<bool> downWalls; //+y 1
  std::vector<bool> rightWalls; //+x 0
};

//dir = 0 represents a rightward step (+1 to the x coordinate)
// dir = 1 represents a downward step (+1 to the y coordinate)
// dir = 2 represents a leftward step (-1 to the x coordinate)
// dir = 3 represents an upward step (-1 to the y coordinate)
