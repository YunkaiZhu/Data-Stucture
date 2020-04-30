#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  start_ = start;
  tolerance_ = tolerance;
  points.push_back(start_);
  // visited.push_back(start_);
  png_ = png;
  unsigned x = png.width();
  unsigned y = png.height();
  v = std::vector<bool> (x*y,false);
  v[start_.x + start_.y*x] = true;

  if (start.x + 1 >= 0 && start.x + 1 < x) {
    Point a(start.x+1,start.y);
    double diff = getDiff(png_,start_,a);
    if (diff <= tolerance_) {
      points.push_back(a);
    }
  }
  if (start.y + 1 >= 0 && start.y + 1 < y) {
    Point a(start.x,start.y + 1);
    double diff = getDiff(png_,start_,a);
    if (diff <= tolerance_) {
      points.push_back(a);
    }
  }
  if (start.x - 1 >= 0 && start.x - 1 < x) {
    Point a(start.x - 1, start.y);
    double diff = getDiff(png,start_,a);
    if (diff <= tolerance) {
      points.push_back(a);
    }
  }
  if (start.y - 1 >= 0 && start.y - 1 < y) {
    Point a(start.x,start.y - 1);
    double diff = getDiff(png_,start_,a);
    if (diff <= tolerance) {
      points.push_back(a);
    }
  }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this,start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}
bool BFS::checkVisited(const Point& point) {
  return v[point.x + point.y * png_.width()];
}
bool BFS::checkAdded(const Point& point) {
  for (unsigned i = 0; i < points.size(); i++) {
    if (point == points[i]) {
      return true;
    }
  }
  return false;
}
/** 
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  // if (checkVisited(point)) {
  //   return;
  // }
  unsigned w = png_.width();
  unsigned h = png_.height();

  if (point.x < 0 || point.x >= w || point.y < 0 || point.y >= h) {
    return;
  }

  if ((!checkAdded(point)) && (!checkVisited(point))) {
    double diff = getDiff(png_,point,start_);
    if (diff <= tolerance_) {
      points.push_back(point);
    }
  }
  
  if (point.x < w - 1) {
    Point n1(point.x+1,point.y);
    if ((!checkVisited(n1)) && (!checkAdded(n1))) {
      if (getDiff(png_,n1,start_) < tolerance_) {
        points.push_back(n1);
      }
    }
  }
  if (point.y < h - 1) {
    Point n2(point.x,point.y + 1);
    if ((!checkVisited(n2)) && (!checkAdded(n2))) {
      if (getDiff(png_,n2,start_) < tolerance_) {
        points.push_back(n2);
      }
    }
  }
  if (point.x > 0) {
    Point n3(point.x - 1, point.y);
    if((!checkVisited(n3)) && (!checkAdded(n3))) {
      if (getDiff(png_,n3,start_) < tolerance_) {
        points.push_back(n3);
      }
    }
  }
  if (point.y > 0) {
    Point n4(point.x,point.y - 1);
    if ((!checkVisited(n4)) && (!checkAdded(n4))) {
      if (getDiff(png_,n4,start_) < tolerance_) {
        points.push_back(n4);
      }
    }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point returnPoint = points.front();
  v[returnPoint.x + png_.width() * returnPoint.y] = true;
  points.erase(points.begin());
  return returnPoint;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return points.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return points.empty();
}
