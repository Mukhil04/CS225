/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
#include <cmath>
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
  return List<T>::ListIterator(tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode* iterator = head_;
  while(iterator != NULL){
    ListNode* temp = iterator->next;
    delete iterator;
    iterator = temp;
  }
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
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
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
  newNode -> next = NULL;
  newNode -> prev = tail_;
  
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  tail_ = newNode;
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
  if(splitPoint < 0){ 
    return start;
  }
  if(splitPoint > length_){ 
    return NULL;
  }
  if (splitPoint == 0){
    return start;
  }
  if(start == NULL){ 
    return NULL;
  }
  if (splitPoint == length_){
    return NULL;
  }
  ListNode * curr = start;
  ListNode * head = NULL;
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  if (curr != NULL) {
    head = curr->prev->next;
    curr->prev->next = NULL;
    curr->prev = NULL;
  }
  else {
    return NULL;
  }
  return head;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* iterator = head_;
  int flag = 0;
  while(true){
    ListNode* original_iterator = iterator;
    if(iterator == NULL){
      break;
    }
    for(int i = 0; i < 3; i++){
      iterator = iterator -> next;
      if (iterator == NULL && i < 2){
        flag = 1;
        break;
      }
    }
    if (flag == 1){
      break;
    }
    else {
      ListNode* next_set = iterator;
      iterator = original_iterator;
      if (iterator -> prev != NULL){
        iterator->prev->next = iterator->next;
        iterator->next->prev = iterator->prev;
      }
      if (iterator -> prev == NULL){
        head_ = iterator->next;
        iterator->next->prev = NULL;
      }
      iterator = iterator->next;
      iterator-> next -> next = original_iterator;
      original_iterator-> prev = iterator->next;
      original_iterator-> next = next_set;
      if (next_set != NULL){
        next_set -> prev = original_iterator;
      }
      iterator = next_set;
    }
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
  /// @todo Graded in MP3.2
  if (startPoint == NULL){
    return;
  }
  if (endPoint == NULL){
    return;
  }
  ListNode* iterator = startPoint;
  ListNode* temp = NULL;
  ListNode* temp2 = startPoint-> prev;
  startPoint-> prev = startPoint -> next;
  iterator = startPoint -> next;
  startPoint -> next = endPoint -> next;
  while(iterator != endPoint){
    temp = iterator -> next;
    iterator -> next = iterator -> prev;
    iterator -> prev = temp;
    iterator = temp;
  }
  if (iterator -> next != NULL){
    iterator -> next -> prev = startPoint;
  }
  if (temp2 != NULL){
    temp2 -> next = iterator;
  }
  iterator -> next = iterator -> prev;
  iterator -> prev = temp2;
  endPoint = startPoint;
  startPoint = iterator;
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
  if (n >= length_){
    reverse();
    return;
  }
  ListNode* startPoint = head_;
  ListNode* endPoint = head_;
  int reverse_blocks = trunc(length_/n);
  int leftover_blocks = length_ % n;
  for (int x = 0; x < n - 1; x++){
    endPoint = endPoint -> next;
  }
  reverse(startPoint,endPoint);
  head_ = startPoint;
  for (int y = 0; y < reverse_blocks - 1; y++){
    for (int x = 0; x < n; x++){
      startPoint = startPoint -> next;
      endPoint = endPoint -> next;
    }
    reverse(startPoint, endPoint);
  }
  for (int x = 0; x < n; x++){
    startPoint = startPoint -> next;
  }
  if (leftover_blocks > 1){
    reverse(startPoint, tail_);
    return;
  }
  else {
    tail_ = endPoint;
    return;
  }
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
  
  ListNode* iterator1 = first;
  ListNode* iterator2 = second;
  ListNode* iterator_final = NULL;
  ListNode* temp = NULL;
  ListNode* check = NULL;
  /*
  std::cout<<__LINE__<<std::endl;
  check = iterator1;
  while(check != NULL){
    std::cout<<__LINE__<<std::endl;
    std::cout<<check->data<<std::endl;
    std::cout<<__LINE__<<std::endl;
    check = check -> next;
  }
  check = iterator2;
  std::cout<<__LINE__<<std::endl;
  while(check != NULL){
    std::cout<<__LINE__<<std::endl;
    std::cout<<check->data<<std::endl;
    std::cout<<__LINE__<<std::endl;
    check = check -> next;
  }
  */
  int flag = 0;
  while(iterator1 -> next != NULL){
    iterator1 = iterator1 -> next;
  }
  while (iterator2 -> next != NULL){
    iterator2 = iterator2 -> next;
  }
  if (iterator2 -> data < iterator1-> data){
    iterator_final = iterator2;
    flag = 2;
  }
  else {
    iterator_final = iterator1;
    flag = 1;
  }
  iterator1 = first;
  iterator2 = second;
  if (!(iterator1-> data < iterator2->data)){
    if (iterator2-> next == NULL){
      iterator2->next = first;
      iterator2-> prev = first-> prev;
      first->prev = iterator2;
      return iterator2;
    }
    if (iterator2->next != NULL){
      temp = iterator2->next;
      iterator2->next = iterator1;
      iterator2 -> prev = iterator1-> prev;
      iterator1->prev = iterator2;
      first = iterator2;
      iterator2 = temp;
    }
  }
  while(iterator1 != iterator_final && iterator2 != iterator_final){
    if (iterator2 -> data < iterator1-> data){
      iterator1->prev->next = iterator2;
      iterator2->next->prev = iterator2->prev;
      iterator2->prev = iterator1->prev;
      iterator1->prev = iterator2;
      temp = iterator2->next;
      iterator2 -> next = iterator1;
      iterator2 = temp;
    }
    else{
      iterator1 = iterator1 -> next;
    }
  }
  if (flag == 1){
    while(iterator2 ->data < iterator1->data && iterator2 != NULL){
      iterator1->prev->next = iterator2;
      iterator2->prev = iterator1->prev;
      temp = iterator2->next;
      iterator2->next = iterator1;
      iterator2 = temp;
    }
    
    iterator1->next = iterator2;
    iterator2 -> prev = iterator1;
  }
  if (flag == 2){
    if (iterator1 -> prev == NULL){
      iterator2 -> prev = iterator1;
      iterator2 -> next = iterator1->next;
      iterator1 -> next = iterator2;
    }
    else{
      while(iterator1->data < iterator2->data && iterator1 -> next != NULL){
        iterator1 = iterator1->next;
      }
      iterator1-> prev -> next = iterator2;
      iterator2 -> next = iterator1;
      iterator2->prev = iterator1 -> prev;
    }
  
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
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength){
  /// @todo Graded in MP3.2
  if (chainLength == 1){
    return start;
  }
  ListNode* secondlist = NULL;
  ListNode* second = NULL;
  ListNode* first = NULL;
  int middle = chainLength/2;
  secondlist = split(start,middle);
  first = mergesort(start,middle);
  second = mergesort(secondlist, chainLength - middle);
  return merge(first,second);
}

