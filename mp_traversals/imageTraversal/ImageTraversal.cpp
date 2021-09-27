#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */

bool ImageTraversal::Iterator::process_point(Point p){
  //Maybe vector empty error
  if (done[p.x][p.y] == 1){
    return false;
  }
  double tolerance = calculateDelta(png.getPixel(image_traversal->get_start().x,image_traversal->get_start().y),png.getPixel(p.x,p.y));
  if (image_traversal->get_tolerance() <= tolerance){
    return false;
  }
  else {
    done[p.x][p.y] = 1;
    return true;
  }
}
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */

ImageTraversal::Iterator::Iterator() {
  image_traversal = NULL;
  /** @todo [Part 1] */
}
ImageTraversal::Iterator::Iterator(ImageTraversal* image_traversal, PNG png, Point current)
  : image_traversal(image_traversal), current(current), png(png), done(png.width(), std::vector<int>(png.height()))
{  
  for (unsigned x = 0; x < png.width(); x++){
    for (unsigned y = 0; y < png.height(); y++){
      done[x][y] = 0;
    }
  }
  current = image_traversal->peek();
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
}
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(!image_traversal->empty()){
    current = image_traversal->pop();
    image_traversal->add(current);
    if (current == image_traversal->get_start()){
      done[current.x][current.y] = 1;
    }
    while(!image_traversal->empty() && !process_point(image_traversal->peek())){
        image_traversal->pop();
    }
    if (image_traversal->empty()){
      return *this;
    }
    else{
      current = image_traversal->peek();
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}
PNG ImageTraversal::Iterator::get_PNG(){
  return png;
}
/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (image_traversal == NULL) { thisEmpty = true; }
  if (other.image_traversal == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = image_traversal->empty(); }
  if (!otherEmpty) { otherEmpty = other.image_traversal->empty(); }
  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (image_traversal != other.image_traversal); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true
}

