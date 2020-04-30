/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <string>
#include <iostream>
#include "cs225/PNG.h"
#include "Image.h"
#include <vector>
using namespace std;

class StickerSheet {
    private:
    unsigned int max_stickers;
    vector<Image> stickers;
    Image* base;
    vector<int> x_coordinates;
    vector<int> y_coordinates;
    vector<int> sticker_exist;
    public:
    StickerSheet (const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet& operator= (const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    Image render() const;
};
 
