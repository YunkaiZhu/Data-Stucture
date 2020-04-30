#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "cs225/RGB_HSL.h"

#include <string>
#include <vector>
using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base = new Image();
    *base = picture;
    max_stickers = max;
}

StickerSheet::~StickerSheet(){
    sticker_exist.clear();
    x_coordinates.clear();
    y_coordinates.clear();
    stickers.clear();
    delete base;
    max_stickers = 0;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    max_stickers = other.max_stickers;
    for (unsigned x = 0; x < other.stickers.size(); x++) {
        stickers.push_back(other.stickers[x]);
        x_coordinates.push_back(other.x_coordinates[x]);
        y_coordinates.push_back(other.y_coordinates[x]);
        sticker_exist.push_back(other.sticker_exist[x]);
    }
    base = new Image();
    *base = *(other.base);
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &other){
    *(this->base) = *(other.base);
    this->max_stickers = other.max_stickers;
    this->stickers = other.stickers;
    this->sticker_exist = other.sticker_exist;
    this->x_coordinates = other.x_coordinates;
    this->y_coordinates = other.y_coordinates;
    return *this;
}
void StickerSheet::changeMaxStickers(unsigned max) {
    this->stickers.resize(max);
    this->x_coordinates.resize(max);
    this->y_coordinates.resize(max);
    this->sticker_exist.resize(max);
    max_stickers = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    for (unsigned i = 0; i < stickers.size(); i++) {
        if (sticker_exist[i] == 0) {
            Image s = Image(sticker);
            x_coordinates[i] = x;
            y_coordinates[i] = y;
            stickers[i] = s;
            sticker_exist[i] = 1;
            return i;
        }
    }
    unsigned index = stickers.size();
    if (index < max_stickers) {
        Image s = Image(sticker);
        stickers.push_back(s);
        x_coordinates.push_back(x);
        y_coordinates.push_back(y);
        sticker_exist.push_back(1);
        return index;
    } else {
        return -1;
    }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
   if (index >= stickers.size()) {
       return false;
   }
   if (sticker_exist[index] == 0) {
       return false;
   }
    x_coordinates[index] = x;
    y_coordinates[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index){
    if (index < stickers.size()) {
        this->sticker_exist[index] = 0;
    }
}

Image* StickerSheet::getSticker(unsigned index){
    if (index >= 0 && index < stickers.size()) {
        if (sticker_exist[index] == 1) {
            Image* p = &stickers[index];
            return p;
        }
    }
    return nullptr;
}

Image StickerSheet::render() const {
    Image scene = Image(*base);
    unsigned w = scene.width();
    unsigned h = scene.height();
    for (unsigned i = 0; i < stickers.size(); i++) {
        if (sticker_exist[i] == 1) {
            if (w < stickers[i].width() + x_coordinates[i]) {
                w = stickers[i].width() + x_coordinates[i];
                scene.resize(w,h);
                if (h < stickers[i].height() + y_coordinates[i]) {
                    h = stickers[i].height() + y_coordinates[i];
                    scene.resize(w, h);
                }
            } else if (h < stickers[i].height() + y_coordinates[i]) {
                h = stickers[i].height() + y_coordinates[i];
                scene.resize(w, h);
            }
            for (unsigned x = 0; x < stickers[i].width(); x++) {
                for (unsigned y = 0; y < stickers[i].height(); y++) {
                    cs225::HSLAPixel & base_pixel = scene.getPixel(x + x_coordinates[i],y + y_coordinates[i]);
                    if (stickers[i].getPixel(x,y).a != 0) {
                        base_pixel = stickers[i].getPixel(x,y);
                    }
                }
            }
        }
        
    }
    return scene;

}

