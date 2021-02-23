/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);
  ~BFS();
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  bool visitedYet(unsigned x, unsigned y);
  void setVisited(unsigned x, unsigned y, bool value);
  double getTolerance_();
private:
  /** @todo [Part 1] */
  /** add private members here*/
  double tolerance_;
  PNG png_;
  Point point_;
  std::queue<Point> traversal_;
  //2d array
  std::vector<std::vector<bool>> visited_;
};