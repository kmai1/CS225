/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  if (head_ == NULL && tail_ == NULL) {
    //delete head_;
    //delete tail_;
    return;
  }
  while (head_ != NULL) {
    ListNode* temp = NULL;
    temp = head_->next;
    delete head_;
    head_ = temp;
  }

  head_ = NULL;
  tail_ = NULL;
  //curr = NULL;
  //temp = NULL;
  length_ = 0;
  //temp = NULL;

  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->next = NULL;
  newNode->prev = NULL;
  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
    length_++;
    return;
  }
  newNode -> next = head_;
  newNode -> prev = NULL;
  head_->prev = newNode;
  head_ = head_->prev;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (length_ == 0) {
    newNode->next = NULL;
    newNode->prev = NULL;
    head_ = newNode;
    tail_ = newNode;
    length_++;
    return;
  }
  newNode->prev = tail_;
  tail_->next = newNode;
  newNode->next = NULL;
  tail_ = tail_->next;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  ListNode * temp;
  if (splitPoint == 0) {
    return start;
  }
  for (int i = 0; i < splitPoint; i++) {
    temp = curr;
    curr = curr->next;
  }
  temp->next = NULL;
  if (curr != NULL) {
      //curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if (head_ == NULL) {
    return;
  }
  int counter = 1;
  ListNode* curr = head_;
  ListNode* temp;
  while (curr != NULL && curr != tail_) {
    if (counter== -1 ) {
      //removes all the pointers to curr and points it to the stuff in front/back
      temp = curr;
      curr = curr->next;
      temp->next->prev = temp->prev;
      temp->prev->next = temp->next;
      //bring temp to the back now
      temp->prev = tail_;
      tail_->next = temp;
      temp->next = NULL;
      tail_ = temp;
      //insertBack(temp->data);
    } else {
      curr = curr->next;
    }
    counter*= -1;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}
/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  //std::cout<<"im running the function again"<<std::endl;
  /// @todo Graded in MP3.2
  if (startPoint == endPoint) {
    return;
  }
  ListNode* startPrev = startPoint->prev;
  ListNode* endNext = endPoint->next;

  ListNode* curr = startPoint;
  ListNode* final = endPoint->next;
  ListNode* currNextHolder = curr->next; //remember this is for reassigning
  //switch all the pointesr from start to end
  while (curr != final) {
    currNextHolder = curr->next;
    curr->next = curr->prev;
    curr->prev = currNextHolder;
    curr = curr->prev; //this actually takes u to "next" spot bc next/prev flipped now
    //curr ends on last element
    //remember end and start switched spots now
  }
  //this mp sucks but this is reassigning those before/after start/end
  startPoint->next = endNext;
  endPoint->prev = startPrev;

  if (startPrev != NULL) {
    startPrev->next = endPoint;
  }
  if (endNext != NULL) {
    endNext->prev = startPoint;
  }
  if (startPrev == NULL) {
    head_ = endPoint;
  }
  if (endNext == NULL) {
    tail_ = startPoint;
  }
  //reassign start/emd
  final = startPoint;
  startPoint = endPoint;
  endPoint = final;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n <= 1 || head_ == NULL || tail_ == NULL) {
    return;
  }

  ListNode* start = head_;
  ListNode* end = start;
  int timesToDoIt = (length_/n);
  int count = 0;
  while (start != NULL) {
    end = start;
    for (int k = 1; k < n; k++) {
      if (end->next != NULL) {
        end = end->next;
      }
    }
    std::cout << "prereverse" << std::endl;
    std::cout << start->data << std::endl;
    std::cout << end->data << std::endl;
    cout<<__LINE__<<endl;
    reverse(start, end);
    cout<<__LINE__<<endl;

    std::cout << "postreverse" << std::endl;
    std::cout << start->data << std::endl;
    std::cout << end->data << std::endl;
    cout<<__LINE__<<endl;
    start = end->next;
    cout<<__LINE__<<endl;

    end = start;
    count++;
  }
  //if (end->next != NULL) {
  //  reverse(end->next, tail_);
  //}
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* secondNextHolder = second;
  ListNode* secondCurr = second;
  ListNode* curr = first;
  //secondCurr [ se]
  while (secondCurr != NULL) {
    while (curr != NULL) {
      if (secondCurr->data < first->data) {
        secondNextHolder = secondNextHolder->next;
        secondCurr->prev = NULL;
        secondCurr->next = first;
        first->prev = secondCurr;
        first = secondCurr;
        second = second->next;
        break;
      }
      if (secondCurr->data < curr->data) {
        secondNextHolder = secondNextHolder->next;
        secondCurr->next = curr;
        secondCurr->prev = curr->prev;
        curr->prev->next = secondCurr;
        curr->prev = secondCurr;
        break;
      }
      if(curr->next == NULL) {
        curr->next = secondCurr;
        secondCurr->prev = curr;
        secondNextHolder = NULL;
        break;
      }
      curr = curr->next;
    }
    secondCurr = secondNextHolder;
  }
  return first;
}


/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  //should work/right idea once i get merge working
  /// @todo Graded in MP3.2
  if (chainLength == 1) {
    return start;
  }
  ListNode* secondListStart = split(start, chainLength/2);
  return merge(mergesort(start, chainLength/2), mergesort(secondListStart, chainLength - chainLength/2));
}
