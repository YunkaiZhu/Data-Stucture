#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

#include <string>
using namespace cs225;

void Image::darken() {
    for(unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l -= 0.1;
            if (pixel.l < 0) {
                pixel.l = 0;
            } else if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

void Image::darken(double amount) {
    for(unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l -= amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            } else if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

void Image::lighten() {
    for(unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l += 0.1;
            if (pixel.l < 0) {
                pixel.l = 0;
            } else if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for(unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l += amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            } else if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

void Image::saturate() {
    for(unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s += 0.1;
            if (pixel.s < 0) {
                pixel.s = 0;
            } else if (pixel.l > 1) {
                pixel.s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for(unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s += amount;
            if (pixel.s < 0) {
                pixel.s = 0;
            } else if (pixel.l > 1) {
                pixel.s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for(unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s -= 0.1;
            if (pixel.s < 0) {
                pixel.s = 0;
            } else if (pixel.l > 1) {
                pixel.s = 1;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for(unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s -= amount;
            if (pixel.s < 0) {
                pixel.s = 0;
            } else if (pixel.l > 1) {
                pixel.s = 1;
            }
        }
    }
}

void Image::grayscale() {
    for(unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s = 0;
        }
    }
}

void Image::illinify() {
    for(unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            double hue = fmod(pixel.h,360);
            if (hue < 11 && hue >= 0) {
                pixel.h = 11;
            } else if (hue >= 11 && hue < 216) {
                if (abs(hue-11) > abs(hue - 216)) {
                  pixel.h = 216;
                } else if (abs(hue - 11) <= abs(hue - 216)){
                  pixel.h = 11;
                }
            } else if (hue >= 216 && hue <= 360) {
                if (abs(hue - 216) > abs(11+360-hue)){
                  pixel.h = 11;
                } else if (abs(hue - 216) <= abs(11+360-hue)){
                  pixel.h = 216;
                }
            }
        }   
    }
}

void Image::scale(double factor) {
    int neww = factor * ((double)this->width());
    int newh = factor * ((double)this->height());
    Image newImage(*this);
    newImage.resize(neww, newh);
    for (unsigned x = 0; x < newImage.width(); x++) {
        for (unsigned y = 0; y < newImage.height(); y++) {
            HSLAPixel & pixel = newImage.getPixel(x,y);
            pixel = this->getPixel(x/factor,y/factor);
        }
    }
    this->resize(neww,newh);
    for (unsigned x = 0; x < newImage.width(); x++) {
        for (unsigned y = 0; y < newImage.height(); y++) {
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel = newImage.getPixel(x,y);
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double rw = (double)this->width()/(double)w;
    double rh = (double)this->height()/(double)h;
    unsigned maxw = w;
    unsigned maxh = h;
    if (rw < rh) {
        w = this->width()/rh;
    }
    double factor = (double)w/(double)this->width();
    this->scale(factor);
    if (this->height() > maxh) {
        this->scale((double)maxh/(double)this->height());
    }
    if (this->width() > maxw) {
        this->scale((double)maxw/(double)this->width());
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this -> getPixel(x,y);
            pixel.h += degrees;
            pixel.h = fmod(pixel.h, 360);
            while (pixel.h < 0) {
                pixel.h = 360 + pixel.h;
            }
        }
    }
}