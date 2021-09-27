#include "StickerSheet.h"
#include <iostream>
#include "Image.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    base_picture = new Image(picture);
    image_pointers = new Image*[max];
    x_coordinates = new int[max];
    y_coordinates = new int[max];
    maximum_stickers = max;
    sticker_count = 0;
}
StickerSheet::StickerSheet(const StickerSheet & other){
        base_picture = NULL;
        image_pointers = NULL;
        x_coordinates = NULL;
        y_coordinates = NULL;
        delete base_picture;
        delete[] image_pointers;
        delete[] x_coordinates;
        delete[] y_coordinates;
        base_picture = new Image(*other.base_picture);
        image_pointers = new Image*[other.maximum_stickers];
        x_coordinates = new int[other.maximum_stickers];
        y_coordinates = new int[other.maximum_stickers];
        for (int i = 0; i < other.maximum_stickers; i++){
            image_pointers [i] = other.image_pointers [i];
            x_coordinates [i] = other.x_coordinates [i];
            y_coordinates [i] = other.y_coordinates [i];
        }
        sticker_count = other.sticker_count;
        maximum_stickers =  other.maximum_stickers;
}
StickerSheet::~StickerSheet(){
    delete[] image_pointers;
    delete base_picture;
    delete[] x_coordinates;
    delete[] y_coordinates;
}
int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y ){
    if (sticker_count < maximum_stickers){
        (image_pointers[sticker_count]) = &sticker;
        x_coordinates[sticker_count] = int(x);
        y_coordinates[sticker_count] = int(y);
        sticker_count = sticker_count + 1;
        return sticker_count;
    }
    else {
        return -1;
    }
}

void StickerSheet::changeMaxStickers(unsigned max){
    if (max != 0){
        Image ** new_image_pointer = new Image* [max];
        int* new_x_coordinates = new int [max];
        int* new_y_coordinates = new int [max];
        if (int(max) < sticker_count){
            for (int i = 0; i < int(max); i++){
                new_image_pointer [i] = image_pointers [i];
                new_x_coordinates [i] = x_coordinates [i];
                new_y_coordinates [i] = y_coordinates [i];
                sticker_count = max;
            }
        }
        else if(int(max) >= sticker_count) {
            for (int i = 0; i < sticker_count; i++){
                new_image_pointer [i] = image_pointers [i];
                new_x_coordinates [i] = x_coordinates [i];
                new_y_coordinates [i] = y_coordinates [i];
            }
        }
        delete[] x_coordinates;
        delete[] y_coordinates; 
        delete[]image_pointers;
        image_pointers = new_image_pointer;
        x_coordinates = new_x_coordinates;
        y_coordinates = new_y_coordinates;
        maximum_stickers = max;
    }
    else if (max == 0){
        sticker_count = 0;
    }
}

Image* StickerSheet::getSticker (unsigned index){
    if (int(index) >= sticker_count || index < 0){
        return NULL;
    }
    else {
        return image_pointers[index];
    }
}

void StickerSheet::removeSticker(unsigned index){
    if (int(index) != int(sticker_count - 1)){
        for (int i = index; i < sticker_count - 1; i++){
            image_pointers[i] = image_pointers[i + 1];
            x_coordinates[i] = x_coordinates[i + 1];
            y_coordinates[i] = y_coordinates[i + 1];
;        }
    }
    else if (int(index) == sticker_count -1){
        image_pointers[index] = NULL;
        x_coordinates[index] = 0;
        y_coordinates[index] = 0;
    }
    sticker_count = sticker_count - 1;
}

const StickerSheet & StickerSheet::operator= (const StickerSheet & other){
        delete base_picture;
        delete[] image_pointers;
        delete[] x_coordinates;
        delete[] y_coordinates;
        base_picture = new Image(*(other.base_picture));
        image_pointers = new Image*[other.maximum_stickers];
        x_coordinates = new int[other.maximum_stickers];
        y_coordinates = new int[other.maximum_stickers];
        for (int i = 0; i < other.maximum_stickers; i++){
            image_pointers [i] = other.image_pointers [i];
            x_coordinates [i] = other.x_coordinates [i];
            y_coordinates [i] = other.y_coordinates [i];
        }
        sticker_count = other.sticker_count;
        maximum_stickers =  other.maximum_stickers;
        return *this;
}

bool StickerSheet::translate(unsigned int index, unsigned x, unsigned y){
    if (int(index) >= sticker_count || index < 0){
        return false;
    }
    else if (image_pointers[index] == NULL){
        return false;
    }
    else {
        x_coordinates [index] = int(x);
        y_coordinates [index] = int(y);
        return true;
    }
}

Image StickerSheet::render() const{
    Image final(*base_picture);
    for (int i = 0; i < sticker_count; i++){
        if (y_coordinates[i] + int(image_pointers[i]->height()) >= int(final.height())){
           final.resize(final.width(), unsigned(y_coordinates[i] + int(image_pointers[i]->height())));
        }
        if (x_coordinates[i] + int(image_pointers[i]->width()) >= int(final.width())){
            final.resize(unsigned(x_coordinates[i] + int(image_pointers[i]->width())), final.height());  
        }
        for (int x = x_coordinates[i]; x < x_coordinates[i] + int(image_pointers[i]->width()); x++){
            for (int y = y_coordinates[i]; y < y_coordinates[i] + int(image_pointers[i]->height()); y++){
                if (image_pointers[i]->getPixel(x - x_coordinates[i],y - y_coordinates[i]).a == 0){
                    continue;
                }
                else {
                  final.getPixel(x,y) = image_pointers[i]->getPixel(x - x_coordinates[i],y - y_coordinates[i]);
                } 
            }
        }
    }
    return final;
}