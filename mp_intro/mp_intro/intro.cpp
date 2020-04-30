#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

#include <string>
using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG* image = new PNG();

  if (image->readFromFile(inputFile)){
    unsigned width = image->width();
    unsigned height = image->height();
    PNG* output = new PNG(width,height);
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel & pixel1 = output->getPixel(width - 1 - x, height - 1 - y);
        HSLAPixel & pixel2 = image->getPixel(x, y);
        pixel1 = pixel2;
      }
    }  
  output->writeToFile(outputFile);
  }
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned x = 0; x < width; x++){
    for (unsigned y = 0; y < height; y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.a = rand();
      pixel.h = fmod(sqrt(x + y),360);
      pixel.s = rand();
      pixel.l = rand();
    }
  }
  return png;
}
