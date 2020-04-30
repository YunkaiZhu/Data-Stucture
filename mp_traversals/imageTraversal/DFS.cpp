#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  png_ = png;
  tolerance_ = tolerance;
  start_ = start;

  unsigned x = png.width();
  unsigned y = png.height();

  v = std::vector<bool> (x*y, false);

  if (start.x + 1 >= 0 && start.x + 1 < x) {
    Point a(start.x+1,start.y);
    double diff = getDiff(png,start,a);
    if (diff <= tolerance) {
      points.push_back(a);
    }
  }
  if (start.y + 1 >= 0 && start.y + 1 < y) {
    Point a(start.x,start.y + 1);
    double diff = getDiff(png,start,a);
    if (diff <= tolerance) {
      points.push_back(a);
    }
  }
  if (start.x - 1 >= 0 && start.x - 1 < x) {
    Point a(start.x - 1, start.y);
    double diff = getDiff(png,start,a);
    if (diff <= tolerance) {
      points.push_back(a);
    }
  }
  if (start.y - 1 >= 0 && start.y - 1 < y) {
    Point a(start.x,start.y - 1);
    double diff = getDiff(png,start,a);
    if (diff <= tolerance) {
      points.push_back(a);
    }
  }
  points.push_back(start_);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

bool DFS::checkVisited(const Point& point) {
  return v[point.x + point.y * png_.width()];
}
bool DFS::checkAdded(const Point& point) {
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
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  unsigned w = png_.width();
  unsigned h = png_.height();

  if (point.x < 0 || point.x >= w || point.y < 0 || point.y >= h) {
    return;
  }
  if (point.x < w - 1) {
    Point n(point.x+1,point.y);
    if (checkAdded(n)) {
      for (unsigned i = 0; i < points.size(); i++) {
        if (points[i] == n) {
          points.erase(points.begin() + i);
          points.push_back(n);
        }
      }
    } else if((!checkVisited(n)) && (!checkAdded(n))) {
      if (getDiff(png_,n,start_) < tolerance_) {
        points.push_back(n);
      }
    }
  }
  if (point.y < h - 1) {
    Point n(point.x,point.y + 1);
    if (checkAdded(n)) {
      for (unsigned i = 0; i < points.size(); i++) {
        if (points[i] == n) {
          points.erase(points.begin() + i);
          points.push_back(n);
        }
      }
    } else if((!checkVisited(n)) && (!checkAdded(n))) {
      if (getDiff(png_,n,start_) < tolerance_) {
        points.push_back(n);
      }
    }
  }
  if (point.x > 0) {
    Point n(point.x - 1, point.y);
    if (checkAdded(n)) {
      for (unsigned i = 0; i < points.size(); i++) {
        if (points[i] == n) {
          points.erase(points.begin() + i);
          points.push_back(n);
        }
      }
    } else if((!checkVisited(n)) && (!checkAdded(n))) {
      if (getDiff(png_,n,start_) < tolerance_) {
        points.push_back(n);
      }
    }
  }
  if (point.y > 0) {
    Point n(point.x,point.y - 1);
    if (checkAdded(n)) {
      for (unsigned i = 0; i < points.size(); i++) {
        if (points[i] == n) {
          points.erase(points.begin() + i);
          points.push_back(n);
        }
      }
    } else if((!checkVisited(n)) && (!checkAdded(n))) {
      if (getDiff(png_,n,start_) < tolerance_) {
        points.push_back(n);
      }
    }
  }
  if ((!checkAdded(point)) && (!checkVisited(point))) {
    double diff = getDiff(png_,point,start_);
    if (diff <= tolerance_) {
      points.push_back(point);
    }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point cur = points.back();
  points.pop_back();
  v[cur.x + cur.y * png_.width()] = true;
  return cur;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return empty() ? Point() : points.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return points.empty();
}
