/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++){
    elements.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (elements[elem] < 0){
    return elem;
  } else {
    return find(elements[elem]);
  }
}

void DisjointSets::setunion(int a, int b) {
  int rootA = find(a);
  int rootB = find(b);
  int size = elements[rootA] + elements[rootB];
  if(rootA == rootB){
    return;
  } else if (elements[rootB] <= elements[rootA]){
    elements[rootA] = rootB;
    elements[rootB] = size;
  } else {
    elements[rootB] = rootA;
    elements[rootA] = size;
  }
}

int DisjointSets::size(int elem) {
  while (elem >= 0){
    elem = elements[elem];
  }
  return -elem;
}
