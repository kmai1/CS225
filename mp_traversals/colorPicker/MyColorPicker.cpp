#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <cmath>
using namespace cs225;
using namespace std;
MyColorPicker::MyColorPicker(int radius, double hue, Point start) {
  start_ = start;
  if (hue >= 360) {
    hue_ = 150;
  }
  if (hue < 0) {
    hue_ = 150;
  }
  radius_ = radius;
}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double h_ = hue_;
  double dist = sqrt(((x - start_.x) * (x - start_.x)) + ((y  - start_.y) * (y  - start_.y)));
  if (dist <= radius_) {
    h_ = hue_;
  } else {
    h_ /= 2;
  }
  return HSLAPixel(h_, 0.5, 0.5, 0.5);
}
