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
  /** @todo [Part 1] */
  traversal = NULL;
  
}

ImageTraversal::Iterator::Iterator(ImageTraversal* t, Point c) {
  traversal = t;
  current = c;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (!traversal->empty()) {
    current = traversal->pop();
    traversal->add(current);
    current = traversal->peek();
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

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (traversal==NULL) {
    return false;
  }
  if (!traversal->empty() && other.traversal == NULL) {
    return true;
  }
  if (traversal->empty() && other.traversal == NULL) {
    return false;
  }
  if (traversal->empty() && other.traversal->empty()) {
    return false;
  }
  if (traversal->empty() || other.traversal->empty()) {
    return true;
  } else {
    return (current.x==other.current.x && current.y==other.current.y);
  }
  // return false;
}

double ImageTraversal::getDiff(const PNG & png, const Point & a, const Point & b) {
  HSLAPixel p1 = png.getPixel(a.x,a.y);
  HSLAPixel p2 = png.getPixel(b.x,b.y);
  double diff = calculateDelta(p1,p2);
  return diff;
}