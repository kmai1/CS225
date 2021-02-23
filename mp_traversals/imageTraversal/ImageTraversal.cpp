#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

ImageTraversal::~ImageTraversal() {
}
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

ImageTraversal::Iterator::~Iterator() {
  if (!(traversal_ == NULL)) {
    delete traversal_;
  }
  traversal_ = NULL;
}
/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
  curr_ = Point(-1,-1);
  start_ = Point(-1,-1);
  //counter = 1;
  //done = false;
}
ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start, PNG base) {
  traversal_ = traversal;
  curr_ = start;
  start_ = start;
  //counter = 1;
  //done = false;
  baseImage = base;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //point
  traversal_->setVisited(curr_.x, curr_.y, true);
  unsigned int rightOf = (curr_.x) + 1;
  unsigned int bottomOf = (curr_.y) + 1;
  unsigned int leftOf = (curr_.x) - 1;
  unsigned int topOf = (curr_.y) - 1;
  //check  bound, visited yet?, tolerance, right
  if (rightOf < baseImage.width()) {
    if (!(traversal_->visitedYet(rightOf, curr_.y))) {
      HSLAPixel temp = baseImage.getPixel(start_.x, start_.y);
      HSLAPixel temp2 = baseImage.getPixel(rightOf, curr_.y);
      if (calculateDelta(temp, temp2) < traversal_->getTolerance_()) {
        traversal_->add(Point(rightOf, curr_.y));
        //traversal_->setVisited(rightOf, curr_.y, true);
      }
    }
  }
  //check down
  if (bottomOf < baseImage.height()) {
    if (!(traversal_->visitedYet(curr_.x, bottomOf))) {
      HSLAPixel temp = baseImage.getPixel(start_.x, start_.y);
      HSLAPixel temp2 = baseImage.getPixel(curr_.x, bottomOf);
      if (calculateDelta(temp, temp2) < traversal_->getTolerance_()) {
        traversal_->add(Point(curr_.x, bottomOf));
        //traversal_->setVisited(curr_.x, bottomOf, true);
      }
    }
  }
  //check left
  if (leftOf >= 0 && leftOf < baseImage.width()) {
    if (!(traversal_->visitedYet(leftOf, curr_.y))) {
      HSLAPixel temp = baseImage.getPixel(start_.x, start_.y);
      HSLAPixel temp2 = baseImage.getPixel(leftOf, curr_.y);
      //std::cout << calculateDelta(temp, temp2) << std::endl;
      if (calculateDelta(temp, temp2) < traversal_->getTolerance_()) {
        traversal_->add(Point(leftOf, curr_.y));
        //traversal_->setVisited(leftOf, curr_.y, true);
      }
    }
  }
  //check top
  if (topOf >= 0 && topOf < baseImage.height()) {
    if (!(traversal_->visitedYet(curr_.x, topOf))) {
      HSLAPixel temp = baseImage.getPixel(start_.x, start_.y);
      HSLAPixel temp2 = baseImage.getPixel(curr_.x, topOf);
      if (calculateDelta(temp, temp2) < traversal_->getTolerance_()) {
        traversal_->add(Point(curr_.x, topOf));
        //traversal_->setVisited(curr_.x, topOf, true);
      }
    }
  }
  //traversal_->setVisited(curr_.x, curr_.y, true);
  //rid visited
  while (!(traversal_->empty()) && (traversal_->visitedYet(traversal_->peek().x, traversal_->peek().y))) {
    traversal_->pop();
  }
  if (traversal_->empty()) {
    end = true;
    return *this;
  }
  curr_ = traversal_->peek();
  //std::cout << curr_.x << " "<< curr_.y << std::endl;
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //check when whether or not iterator is finished
  //traversal_->pop();
  // std::cout << !(this->curr_ == other.curr_) << std::endl;
  return !end;
  // return !(this->curr_ == other.curr_);
}
