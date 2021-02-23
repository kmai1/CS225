/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */
#pragma once
#include "cs225/PNG.h"
class Image: public cs225::PNG{
public:
  void lighten();
  void lighten(double amount);
  void darken();
  void darken(double amount);
  void saturate();
  void saturate(double amount);
  void desaturate();
  void desaturate(double amount);
  void scale(double factor);
  void scale(unsigned width, unsigned height);
  void rotateColor(double degrees);
  void illinify();
  void grayscale();
private:

};
