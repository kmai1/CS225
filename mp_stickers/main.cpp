#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image base;
  Image pluto;
  Image donald;
  Image goofy;
  Image final;
  pluto.readFromFile("pluto.png");
  donald.readFromFile("donald.png");
  goofy.readFromFile("goofy.png");
  base.readFromFile("jimmyjohns.png");
  StickerSheet* sheet = new StickerSheet(base, 23);
  sheet->addSticker(pluto, 100, 100);
  sheet->addSticker(donald, 100, 1000);
  sheet->addSticker(goofy, 1000, 1000);
  final = sheet->render();
  final.writeToFile("myImage.png");
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  return 0;
}
