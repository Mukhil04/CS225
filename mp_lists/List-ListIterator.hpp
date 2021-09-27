class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }

    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP3.1
        position_ = position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in MP3.1
        if (position_->next == NULL){
            ListNode* temp = position_;
            position_ = position_->next;
            return ListIterator(temp);
        }
        position_ = position_->next;
        return ListIterator(position_ -> prev);
    }
    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in MP3.1
        position_ = position_->prev;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in MP3.1
        if (position_->prev == NULL){
            ListNode* temp = position_;
            position_ = position_->prev;
            return ListIterator(temp);
        }
        position_ = position_->prev;
        return ListIterator(position_->next);
    }


    bool operator!=(const ListIterator& rhs) {

        // @TODO: graded in MP3.1
        return !(this->position_ == rhs.position_);
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }
    const T& operator*() {
        return position_->data;
    }
    const T* operator->() {
        return &(position_->data);
    }
};
