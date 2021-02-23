#include "Image.h"
#include "cs225/PNG.h"

using namespace cs225;
using cs225::PNG;

void Image::lighten() {
  lighten(0.1);
}
void Image::lighten(double amount) {
  for (unsigned k = 0; k < this->width(); k++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & temp = this->getPixel(k, j);
      temp.l += amount;
      if (temp.l > 1.0) {
        temp.l = 1.0;
      }
    }
  }
}
void Image::darken() {
  darken(0.1);
}
void Image::darken(double amount) {
  for (unsigned k = 0; k < this->width(); k++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & temp = this->getPixel(k, j);
      temp.l -= amount;
      if (temp.l < 0.0) {
        temp.l = 0.0;
      }
    }
  }
}
void Image::saturate() {
  saturate(0.1);
}
void Image::saturate(double amount) {
  for (unsigned k = 0; k < this->width(); k++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & temp = this->getPixel(k, j);
      temp.s += amount;
      if (temp.s > 1.0) {
        temp.s = 1.0;
      }
    }
  }
}
void Image::desaturate() {
  desaturate(0.1);
}
void Image::desaturate(double amount) {
  for (unsigned k = 0; k < this->width(); k++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & temp = this->getPixel(k, j);
      temp.s -= amount;
      if (temp.s < 0.0) {
        temp.s = 0.0;
      }
    }
  }
}
void Image::scale(double factor) {
  PNG newImage = PNG(*this);
  resize(width() * factor, height() * factor);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel &temp1 = newImage.getPixel(x*1.0/factor, y*1.0/factor);
      HSLAPixel &temp = this->getPixel(x, y);
      temp = temp1;
  }
}
}
void Image::scale(unsigned width, unsigned height) {
  if ((width * 1.0/this->width()) > (height * 1.0/this->height())) {
    scale(height * 1.0/this->height());
  } else {
    scale(width * 1.0/this->width());
  }
}
//modular after adding doubles
void Image::rotateColor(double degrees) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this-> height(); y++) {
      HSLAPixel & temp = this->getPixel(x, y);
      temp.h += degrees;
      if (temp.h > 360) {
        temp.h = temp.h - 360;
      }
      if (temp.h < 0) {
        temp.h = 360 + temp.h;
      }
    }
  }
}

void Image::grayscale() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = 0;
    }
  }
}
void Image::illinify() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & temp = this->getPixel(x, y);
      if (temp.h > 114 && temp.h <= 294) {
        temp.h = 216;
      } else {
        temp.h = 11;
      }
    }
  }
}
