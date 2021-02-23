#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"
StickerSheet::StickerSheet(const Image& picture, unsigned max) {
  baseImage = new Image(picture);
  maxStickers = max;
  stickerArr = new Image* [max];
  stickerX = new unsigned [max];
  stickerY = new unsigned [max];
  for (unsigned k = 0; k < max; k++) {
    stickerArr[k] = NULL;
    //stickerX[k] = -1;
    //stickerY[k] = -1;
  }
}

StickerSheet::~StickerSheet() {
  _destroy();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
  _copy(other);
}

void StickerSheet::_copy(const StickerSheet & other) {
  maxStickers = other.maxStickers;
  baseImage = new Image(*other.baseImage);
  stickerArr = new Image* [maxStickers];
  stickerX = new unsigned [maxStickers];
  stickerY = new unsigned [maxStickers];

  for(unsigned k = 0; k < maxStickers; k++) {
    stickerArr[k] = NULL;
    //stickerX[k] = -1;
    //stickerY[k] = -1;
  }

  for (unsigned k = 0; k < maxStickers; k++) {
    if (other.stickerArr[k] != NULL) {
    stickerArr[k] = new Image(*other.stickerArr[k]);
    stickerX[k] = other.stickerX[k];
    stickerY[k] = other.stickerY[k];
    }
  }
}

void StickerSheet::_destroy() {
  //try just delete
  for (unsigned k = 0; k < maxStickers; k++) {
    //if (stickerArr[k] != NULL) {
      delete stickerArr[k];
      stickerArr[k] = NULL;
    //}
  }
    delete[] stickerArr;
    delete[] stickerX;
    delete[] stickerY;
    delete baseImage;
    stickerArr = NULL;
    stickerX = NULL;
    stickerY = NULL;
    maxStickers = 0;
  }
StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
  _destroy();
  _copy(other);
  return *this;
}
void StickerSheet::changeMaxStickers(unsigned number) {
  if (number > maxStickers) {
    Image** tempStickerArr = new Image*[number];
    unsigned* tempStickerX = new unsigned[number];
    unsigned* tempStickerY = new unsigned[number];
    for (unsigned k = 0; k < number; k++) {
      tempStickerArr[k] = NULL;
      tempStickerX[k] = -1;
      tempStickerY[k] = -1;
      if (k < maxStickers && stickerArr[k] != NULL) {
        tempStickerArr[k] =  stickerArr[k]; //new Image(*stickerArr[k]);
        tempStickerX[k] = stickerX[k];
        tempStickerY[k] = stickerY[k];
        //delete stickerArr[k];
        stickerArr[k] = NULL;
      }
    }
    delete[] stickerArr;
    stickerArr = tempStickerArr;
    delete[] stickerX;
    stickerX = tempStickerX;
    delete[] stickerY;
    stickerY = tempStickerY;
    maxStickers = number;
  }
  //use copy constructor of something
  if (number < maxStickers) {
    Image** tempStickerArr = new Image*[number];
    unsigned* tempStickerX = new unsigned[number];
    unsigned* tempStickerY = new unsigned[number];

    for (unsigned k = 0; k < number; k++) {
      tempStickerArr[k] = NULL;
      tempStickerX[k] = -1;
      tempStickerY[k] = -1;
    }
    for (unsigned k = 0; k < number; k++) {
      if (stickerArr[k] != NULL) {
        tempStickerArr[k] = stickerArr[k]; //new Image(*stickerArr[k]);
        tempStickerX[k] = stickerX[k];
        tempStickerY[k] = stickerY[k];
        //delete stickerArr[k];
        stickerArr[k] = NULL;
      }
    }
    for (unsigned k = number; k < maxStickers; k++) {
      delete stickerArr[k];
      stickerArr[k] = NULL;
    }
    delete[] stickerArr;
    stickerArr = tempStickerArr;
    delete[] stickerX;
    stickerX = tempStickerX;
    delete[] stickerY;
    stickerY = tempStickerY;
    maxStickers = number;
  }
}
int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {
  for (unsigned k = 0; k < maxStickers; k++) {
    if (stickerArr[k] == NULL) {
      stickerArr[k] = new Image(sticker);
      stickerX[k] = x;
      stickerY[k] = y;
      return k;
    }
  }
  return -1;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index >= maxStickers || index < 0) {
    return false;
  }
  //check null
  if (stickerArr[index] == NULL) {
    return false;
  }
  stickerX[index] = x;
  stickerY[index] = y;
  return true;
}
void StickerSheet::removeSticker(unsigned index) {
  if (index >= maxStickers || index < 0) {
    return;
  }
  delete stickerArr[index];
  //shift sticekrs over?
  stickerArr[index] = NULL;
  //delete stickerX[index];
  stickerX[index] = -1;
  //delete stickerY[index];
  stickerY[index] = -1;
}
Image* StickerSheet::getSticker(unsigned index) {
  if (index >= maxStickers || index < 0) {
    return NULL;
  }
  return stickerArr[index];
}

Image StickerSheet::render() const {
  unsigned maxW = baseImage->width();
  unsigned maxH = baseImage->height();
  Image* temp = new Image(*baseImage);
  for (unsigned k = 0; k < maxStickers; k++) {
    if (stickerArr[k] != NULL) {
    unsigned xLBound = stickerX[k];
    unsigned xRBound = stickerX[k] + stickerArr[k]->width();
    unsigned yTBound = stickerY[k];
    unsigned yDBound = stickerY[k] + stickerArr[k]->height();
    if (xRBound > maxW) {
      maxW = xRBound;
    }
    if (yDBound > maxH) {
      maxH = yDBound;
    }
    temp->resize(maxW, maxH);
    }
  }

  for(unsigned k = 0; k < maxStickers; k++) {
    if(stickerArr[k] != NULL){
      unsigned xLBound = stickerX[k];
      unsigned xRBound = stickerX[k] + stickerArr[k]->width();
      unsigned yTBound = stickerY[k];
      unsigned yDBound = stickerY[k] + stickerArr[k]->height();
    for (unsigned x = xLBound; x < xRBound; x++) {
      for (unsigned y = yTBound; y < yDBound; y++) {
        cs225::HSLAPixel & tempPix = temp->getPixel(x, y);
        cs225::HSLAPixel & tempPix2 = stickerArr[k]->getPixel(x - xLBound, y - yTBound);
        //tempPix2 = tempPix;
        if(tempPix2.a != 0) {
          tempPix = tempPix2;
        }
      }
    }
  }
}
 Image new_Image = *temp;
 delete temp;
 return new_Image;
}
