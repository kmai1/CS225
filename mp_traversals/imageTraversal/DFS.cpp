#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
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
DFS::~DFS() {
}
/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS* temp = new DFS(png_, point_, tolerance_);
  return ImageTraversal::Iterator(temp, point_, png_);
}
/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  traversal_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  if (traversal_.empty()) {
    return Point(-1, -1);
  }
  Point temp = traversal_.top();
  traversal_.pop();
  return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return traversal_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return traversal_.empty();
}

bool DFS::visitedYet(unsigned x, unsigned y) {
  if (x > png_.width() || x < 0 || y > png_.height() || y < 0) {
    return true;
  }
  return visited_[x][y];
}

void DFS::setVisited(unsigned x, unsigned y, bool value) {
  if (x > png_.width() || x < 0 || y > png_.height() || y < 0) {
    return;
  }
  visited_[x][y] = value;
}
double DFS::getTolerance_() {
  return tolerance_;
}
