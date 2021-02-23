/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (curDim < 0 || curDim > Dim) {
       return false;
     }
     // <operator ot break tie
     if (first[curDim] == second[curDim]) {
       return first < second;
     }
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     int bestDistance = 0;
     int potentialDistance = 0;
     for (int k = 0; k < Dim; k++) {
       int tempBD = pow(target[k] - currentBest[k], 2);
       int tempP = pow(target[k] - potential[k], 2);
       bestDistance += tempBD;
       potentialDistance += tempP;
     }
     if (bestDistance == potentialDistance) {
       return potential < currentBest;
     }
     return potentialDistance < bestDistance;
}

template <int Dim>
unsigned int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int left, int right, int pivotIndex, size_t dim) {
  Point<Dim> pivotPoint = newPoints[pivotIndex];
  std::swap(newPoints[pivotIndex], newPoints[right]);
  int swapIndex = left;
  for  (int k = left; k < right; k++) {
    if (smallerDimVal(newPoints[k], newPoints[right], dim)) {
      std::swap(newPoints[swapIndex], newPoints[k]);
      swapIndex++;
    }
  }
  std::swap(newPoints[right], newPoints[swapIndex]);
  return swapIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSort(vector<Point<Dim>>& newPoints, int left, int right, int k, size_t dim) {
  if (left == right) {
    return newPoints[left];
  }
  int pivot = (left + right) / 2;
  pivot = partition(newPoints, left, right, pivot, dim);
  if (k == pivot) {
    return newPoints[k];
  }
  else if (k < pivot && pivot > 0) {
    return quickSort(newPoints, left, pivot - 1, k, dim);
  }
  else {
    return quickSort(newPoints, pivot + 1, right, k, dim);
  }
}

template <int Dim>
void KDTree<Dim>::createKDT(vector<Point<Dim>>& newPoints, int left, int right, size_t dim, KDTreeNode*& root) {
  if (left > right) {
    return;
  }
  int middle = (left + right) / 2;
  Point<Dim> temp = quickSort(newPoints, left, right, middle, dim);
  root = new KDTreeNode(temp);
  createKDT(newPoints, left, middle - 1, (dim + 1) % Dim, root->left);
  createKDT(newPoints, middle + 1, right, (dim + 1) % Dim, root->right);
}
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     //empty case
     //prevent null
     size = 0;
     root = NULL;
     if (!newPoints.empty()) {
       //prevent passing in NULL
       //root = new KDTreeNode(Point<Dim>());
       vector<Point<Dim>> tempNewPoints = newPoints;
       createKDT(tempNewPoints, 0, newPoints.size() - 1, 0, root);
       size = newPoints.size();
     }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   copy(this->root, other);
   size = other.size;

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this == NULL) {
    remove(root);
  }
  copy(root, rhs.root);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   remove(root);
}
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& target, KDTreeNode* subroot, size_t dim) const {
  //leaf node
  Point<Dim> currBest = subroot->point;
  KDTreeNode* other = NULL;
  //leaf node case
  if (subroot->left == NULL && subroot->right == NULL) {
    return subroot->point;
  }
  //smallerDimVal true means go left
  if (smallerDimVal(target, subroot->point, dim)) {
    if (subroot->left != NULL) {
      currBest = findNearestNeighbor(target, subroot->left, (dim + 1) % Dim);
    other = subroot->right;
    } else {
      other = subroot->right;
    }
  } else {
      currBest = findNearestNeighbor(target, subroot->right, (dim + 1) % Dim);
      other = subroot->left;
    }
    //checking parent node
    if (shouldReplace(target, currBest, subroot->point)) {
      currBest = subroot->point;
    }
    //checking distances and comparing
    double currBestRadius = distance(target, currBest);
    if (distance(target, subroot->point) < currBestRadius) {
      currBestRadius = distance(target, subroot->point);
      currBest = subroot->point;
    }
    double split = pow(subroot->point[dim] - target[dim], 2);

    //checking split nodes
    if (split <= currBestRadius && other != NULL) {
      Point<Dim> temp = findNearestNeighbor(target, other, (dim + 1) % Dim);
      if (shouldReplace(target, currBest, temp)) {
        currBest = temp;
      }
    }

    return currBest;
  }

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     //finds leaf node
    return findNearestNeighbor(query, root, 0);
}

//copy helper
template <int Dim>
void KDTree<Dim>::copy(KDTreeNode* curr, KDTreeNode* other) {
  if (other == NULL) {
    return;
  }
  curr = new KDTreeNode();
  curr->point = other->point;
  copy(curr->left, other->left);
  copy(curr->right, other->right);
}
//remove helper
template <int Dim>
void KDTree<Dim>::remove(KDTreeNode* root) {
  if (root == NULL) {
    return;
  }
  remove(root->left);
  remove(root->right);
  delete root;
}
template <int Dim>
double KDTree<Dim>::distance(const Point<Dim>& first, const Point<Dim>& second) const {
  double ans = 0  ;
  for (int k = 0; k < Dim; k++) {
    ans += pow(first[k] - second[k], 2);
  }
  return ans;
}
