#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

void rotate(std::string inputFile, std::string outputFile) {
  //
  cs225::PNG input;
  input.readFromFile(inputFile);
  int width_ = input.width();
  int height_ = input.height();
  cs225::PNG out(input.width(), input.height());
  //rotate
  for (int k = 0; k < width_; k++) {
    for (int j = 0; j < height_; j++) {
      cs225::HSLAPixel & temp = input.getPixel(k, j);
      cs225::HSLAPixel & temp2 = out.getPixel(width_ - k - 1, height_ - j - 1);
      temp2 = temp;
    }
  }
  out.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned int k = 0; k < png.width(); k++) {
    for (unsigned int j = 0; j < png.height(); j++) {
      cs225::HSLAPixel & temp = png.getPixel(k, j);
      temp.h = rand() % 360;
      temp.l = .5;
      temp.s = .5;
      temp.a = .5;
    }
  }
  return png;
}
