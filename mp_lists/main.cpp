#include "List.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "./tests/tests_helper.h"

int main() {
  //eturn 0;

  List<int> list1;
  List<int> list2;
  list1.insertBack(1);
  list1.insertBack(3);
  list1.insertBack(5);
  list2.insertBack(2);
  list2.insertBack(4);
  list2.insertBack(6);
  list1.mergeWith(list2);
  //list1.reverse();
  list1.reverseNth(2);

  stringstream s;
  list1.print(s);
  std::cout<<s.str()<<std::endl;
  return 0;
}
