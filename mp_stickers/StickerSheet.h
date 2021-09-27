/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
 class StickerSheet{
     public:
        //Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1.
        StickerSheet(const Image &picture, unsigned max);

        //Frees all space that was dynamically allocated by this StickerSheet.
        ~StickerSheet();

        //The copy constructor makes this StickerSheet an independent copy of the source.
        StickerSheet(const StickerSheet & other);

        //Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
        int addSticker(Image & sticker, unsigned x, unsigned y );

        //Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices.
        void changeMaxStickers(unsigned max);

        //Returns a pointer to the sticker at the specified index, not a copy of it.
        Image* getSticker(unsigned index);

        //The assignment operator for the StickerSheet class.
        
        const StickerSheet & operator=(const StickerSheet & other);

        //Removes the sticker at the given zero-based layer index.
        void removeSticker(unsigned index);

        //Renders the whole StickerSheet on one Image and returns that Image.
        Image render()const;

        //Changes the x and y coordinates of the Image in the specified layer.

        bool translate(unsigned index, unsigned x, unsigned y );

        

    private:
        Image* base_picture;
        Image** image_pointers;
        int * x_coordinates;
        int * y_coordinates;
        int sticker_count;
        int maximum_stickers;

 };
