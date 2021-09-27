#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

#include <iostream>
#include <stdlib.h>

#include <math.h>
#include <cstdlib>

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG image;
  bool read;
  unsigned int width;
  unsigned int height;
  read = image.readFromFile(inputFile);
  width = image.width();
  height = image.height();
  int height_flag = 0;
  int width_flag = 0;
  if (height % 2 == 1){
    height_flag = 1;
  }
   if (width % 2 == 1){
    width_flag = 1;
  }
  unsigned int middle_height = (height - 1)/2;
  for (unsigned int x = 0; x < width; x++){
    for (unsigned int y = 0; y <= middle_height; y++){
      if (y == middle_height && x > (width - 1)/2 && height_flag == 1){
        continue;
      }
      cs225::HSLAPixel & pixel = image.getPixel(x,y);
      cs225::HSLAPixel & pixel_1 = image.getPixel(width - 1  - x,height - 1 - y);
      cs225::HSLAPixel temp;
      temp = pixel;
      pixel = pixel_1;
      pixel_1 = temp;
    }
  }
  
  bool write;
  write = image.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  double previous_hue = 140;
  for (unsigned int x = 0; x < width; x++){
    for (unsigned int y = 0; y < height; y++){
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      pixel.l = x * abs(sin(x));
      pixel.a = 0.5;
      pixel.s = y * abs(sin(y));
      pixel.h = previous_hue * abs(sin(x));
      previous_hue = pixel.h;
    }
  }

  return png;
}

