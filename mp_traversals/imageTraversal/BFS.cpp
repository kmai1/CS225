#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;
/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  tolerance_ = tolerance;
  point_ = start;
  png_ = png;
  traversal_.push(start);
  //[x][y];
  visited_.resize(png.width());
  //intiate all to false;
  for (unsigned int k = 0; k < png.width(); k++) {
    visited_[k].resize(png.height());
    for (unsigned int j = 0; j < png.height(); j++) {
      visited_[k][j] = false;
    }
  }
  //initilize start point;
  visited_[start.x][start.y] = true;
}
BFS::~BFS() {
}
/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS* temp = new BFS(png_, point_, tolerance_);
  return ImageTraversal::Iterator(temp, point_, png_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  traversal_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  if (traversal_.empty()) {
    return Point(-1, -1);
  }
  Point temp = traversal_.front();
  traversal_.pop();
  return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return traversal_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return traversal_.empty();
}

bool BFS::visitedYet(unsigned x, unsigned y) {
  if (x > png_.width() || x < 0 || y > png_.height() || y < 0) {
    return true;
  }
  return visited_[x][y];
}

void BFS::setVisited(unsigned x, unsigned y, bool value) {
  if (x > png_.width() || x < 0 || y > png_.height() || y < 0) {
    return;
  }
  visited_[x][y] = value;
}
double BFS::getTolerance_() {
  return tolerance_;
}
