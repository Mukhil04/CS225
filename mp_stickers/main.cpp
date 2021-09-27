#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image Garden;
  Garden.readFromFile("Garden.png");
  Garden.scale(3.0);
  Image Heatran;
  Image Torterra;
  Image Kyogre;
  Heatran.scale(2.3);
  Torterra.scale(2.2);
  Kyogre.scale(2.1);
  Heatran.readFromFile("Heatran.png");
  Kyogre.readFromFile("Kyogre.png");
  Torterra.readFromFile("Torterra.png");
  StickerSheet sheet(Garden,3);
  sheet.addSticker(Heatran, 200, 300);
  sheet.addSticker(Kyogre, 700, 300 );
  sheet.addSticker(Torterra, 1300, 300);
  Image final_image = sheet.render();
  final_image.writeToFile("myImage.png");
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
