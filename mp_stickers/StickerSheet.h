/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

class StickerSheet {
public:
  StickerSheet(const Image & picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet & other);
  StickerSheet & operator=(const StickerSheet & other);
  void changeMaxStickers(unsigned max);
  int addSticker(Image &sticker, unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);
  Image* getSticker(unsigned index);
  Image render() const;
  Image* baseImage;
  unsigned maxStickers;
  unsigned int* stickerX;
  unsigned int* stickerY;
  Image** stickerArr;
private:
void _copy(const StickerSheet & other);
void _destroy();
};
