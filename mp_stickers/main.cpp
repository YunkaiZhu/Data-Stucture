#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image scene;
  scene.readFromFile("baseimage.png");
  Image s1;
  s1.readFromFile("pikachu.png");
  StickerSheet sheet(scene,20);
  for (unsigned i = 0; i < 5; i++) {
    for (unsigned j = 0; j < 4; j++) {
      sheet.addSticker(s1,100*i,100*j);
    }
  }
  Image newimage = sheet.render();
  newimage.writeToFile("myImage.png");
  return 0;
}
