#include "cs225/HSLAPixel.h"
#include "Image.h"
#include <iostream>
#include <cmath>



Image::Image(Image const &other): PNG(other)
{
}

Image::Image()
{    
}

Image::~Image()
{ 
}

void Image::lighten()
{
    for (unsigned int i = 0; i < this->width(); i++){
           for (unsigned int j = 0; j < this->height(); j++){
            if (this->getPixel(i, j).l < 0.9){
                ((this->getPixel(i, j)).l) = ((this->getPixel(i, j)).l) + 0.1;
            }
            else {
                this->getPixel(i, j).l = 1;
            } 
        }
    }
}
void Image::lighten(double amount){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            if (((this->getPixel(i, j)).l + amount) < 1){
                (this->getPixel(i, j)).l = (this->getPixel(i, j)).l + amount;
            }
            else {
                this->getPixel(i, j).l = 1;
            }
            
        }
    }
}
void Image::darken(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            if (((this->getPixel(i, j)).l) > 0.1){
                (this->getPixel(i, j)).l = (this->getPixel(i, j)).l - 0.1;
            }
            else {
                this->getPixel(i, j).l = 0;
            }
            
        }
    }
}
void Image::darken(double amount){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            if (((this->getPixel(i, j)).l - amount) > 0){
                (this->getPixel(i, j)).l = (this->getPixel(i, j)).l - amount;
            }
            else {
                this->getPixel(i, j).l = 0;
            }
        }
    }
}
void Image::saturate(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            if (((this->getPixel(i, j)).s) < 0.9){
                (this->getPixel(i, j)).s = (this->getPixel(i, j)).s + 0.1;
            }
            else {
                this->getPixel(i, j).s = 1;
            }
        }
    }
}
void Image::saturate(double amount){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            if (((this->getPixel(i, j).s) + amount) < 1){
                (this->getPixel(i, j)).s = (this->getPixel(i, j)).s + amount;
            }
            else {
                this->getPixel(i, j).s = 1;
            }
        }
    }
}
void Image::desaturate(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            if ((this->getPixel(i, j).s) > 0.1){
                (this->getPixel(i, j)).s = (this->getPixel(i, j)).s - 0.1;
            }
            else {
                this->getPixel(i, j).s = 0;
            }
        }
    }
}
void Image::desaturate(double amount){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            if (((this->getPixel(i, j).s) - amount) > 0){
                (this->getPixel(i, j)).s = (this->getPixel(i, j)).s - amount;
            }
            else {
                this->getPixel(i, j).s = 0;
            }
        }
    }
}
void Image::grayscale(){
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {
            this->getPixel(x, y).s = 0;
    }
  }
}
void Image::rotateColor(double degrees){
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {
            if((this->getPixel(x,y).h + degrees) > 360){
                getPixel(x,y).h = getPixel(x,y).h + degrees - 360;
            }
            else if ((this->getPixel(x,y).h + degrees) < 0){
                getPixel(x,y).h = 360 + (getPixel(x,y).h + degrees);
            }
            else {
                this->getPixel(x,y).h = this->getPixel(x,y).h + degrees;
            }     
            
        }   
    }
}
void Image::illinify(){
    for (unsigned int x = 0; x < this->width(); x++){
        for (unsigned int y = 0; y < this->height(); y++){
            double orange_difference= 0.0;
            double blue_difference = 0.0;
            if (this->getPixel(x,y).h > 11 && this->getPixel(x,y).h < 216){
                orange_difference = this->getPixel(x,y).h - 11;
                blue_difference = 216 - this->getPixel(x,y).h;
            }
            else if (this->getPixel(x,y).h < 11){
                orange_difference = 11 - this->getPixel(x,y).h;
                blue_difference = this->getPixel(x,y).h + (360-216);
            }
            else if (this->getPixel(x,y).h > 216){
                orange_difference = 11 + (360 - this->getPixel(x,y).h);
                blue_difference = this->getPixel(x,y).h - 216;
            }
            if (orange_difference > blue_difference){
                this->getPixel(x,y).h = 216;
            }
            else {
                this->getPixel(x,y).h = 11;
            }
        }
    }
}
void Image::scale(double factor){
    if (factor < 1.0){
        for(int x = (this->width()*factor)-1; x >= 0 ; x--){
            for(int y = (this->height()*factor)-1; y >= 0; y--){
                this->getPixel(x,y) = this->getPixel(x / factor,y / factor);
            }
        }
        this->resize(this->width()*factor, this->height()*factor);
    }
    if (factor > 1){
        this->resize(this->width()*factor, this->height()*factor);
        for(int x = (this->width()/factor)-1; x >= 0 ; x--){
            for(int y = (this->height()/factor)-1; y >= 0; y--){
                for (int i = 0; i < factor; i++){
                    for (int j = 0; j < factor; j++){
                        this->getPixel(x * factor + i,factor * y + j) = this->getPixel(x,y);
                    }
                }
            }
        }
    }
    
}
void Image::scale(unsigned w, unsigned h){
    double height_scaling_factor = double(h)/double(this->height());
    double width_scaling_factor = double(w)/double(this->width());
    double factor = 0;
    if (height_scaling_factor < width_scaling_factor){
        factor = height_scaling_factor;
    }
    else {
        factor = width_scaling_factor;
    }
    if (factor < 1){
        for(int x = (this->width()*factor)-1; x >= 0 ; x--){
            for(int y = (this->height()*factor)-1; y >= 0; y--){
                this->getPixel(x,y) = this->getPixel(x / factor,y / factor);
            }
        }
        this->resize(this->width()*factor, this->height()*factor);
    }
    if (factor > 1){
        this->resize(this->width()*factor, this->height()*factor);
        for(int x = (this->width()/factor)-1; x >= 0 ; x--){
            for(int y = (this->height()/factor)-1; y >= 0; y--){
                for (int i = 0; i < factor; i++){
                    for (int j = 0; j < factor; j++){
                        this->getPixel(x * factor + i,factor * y + j) = this->getPixel(x,y);
                    }
                }
            }
        }
    }
}
