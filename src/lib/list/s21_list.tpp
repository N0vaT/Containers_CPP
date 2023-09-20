#include "s21_list.h"

template <class T>
List<T>::List() noexcept : size_(0U), ptr_head_(nullptr), ptr_tail_(nullptr) {}

template <class T>
List<T>::List(size_type n) : size_(0U), ptr_head_(nullptr), ptr_tail_(nullptr) {
  if (n > max_size()) {
    throw std::range_error("Invalid argument - n > max_size");
  }
  for (size_type i = 0; i < n; ++i) {
    Node* new_node = new Node();
    if (!ptr_head_) {
      ptr_head_ = ptr_tail_ = new_node;
    } else {
      ptr_tail_->ptr_next_ = new_node;
      Node* ptr_tmp = ptr_tail_;
      ptr_tail_ = new_node;
      ptr_tail_->ptr_prev_ = ptr_tmp;
    }
  }
  size_ = n;
}

template <class T>
List<T>::List(std::initializer_list<value_type> const& items)
    : size_(0U), ptr_head_(nullptr), ptr_tail_(nullptr) {
  for (value_type element : items) {
    push_back(element);
  }
}

template <class T>
List<T>::List(const List& l)
    : size_(0U), ptr_head_(nullptr), ptr_tail_(nullptr) {
  *this = l;
}

template <class T>
List<T>::List(List&& l) noexcept : List() {
  ptr_head_ = l.ptr_head_;
  ptr_tail_ = l.ptr_tail_;
  size_ = l.size_;
  l.size_ = 0;
  l.ptr_head_ = nullptr;
  l.ptr_tail_ = nullptr;
}

template <class T>
List<T>& List<T>::operator=(const List& q) {
  if (this != &q) {
    clear();
    size_ = 0;
    Node* ptr_q = q.ptr_head_;
    for (size_type i = 0; i < q.size_; ++i) {
      push_back(ptr_q->value_);
      ptr_q = ptr_q->ptr_next_;
    }
  }
  return *this;
}

template <class T>
List<T>& List<T>::operator=(List&& l) {
  if (this != &l) {
    clear();
    swap(l);
  }
  return *this;
}

template <class T>
List<T>::~List() {
  clear();
}

template <class T>
typename List<T>::const_reference List<T>::front() const {
  if (!ptr_head_) {
    throw std::range_error("Invalid List for front, List is empty");
  }
  return ptr_head_->value_;
}

template <class T>
typename List<T>::const_reference List<T>::back() const {
  if (!ptr_tail_) {
    throw std::range_error("Invalid List for back, List is empty");
  }
  return ptr_tail_->value_;
}

template <class T>
typename List<T>::iterator List<T>::begin() const noexcept {
  return ListIterator(ptr_head_);
}

template <class T>
typename List<T>::iterator List<T>::end() const noexcept {
  return ListIterator();
}

template <class T>
bool List<T>::empty() const noexcept {
  return size_ == 0;
}

template <class T>
typename List<T>::size_type List<T>::size() const noexcept {
  return size_;
}

template <class T>
typename List<T>::size_type List<T>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(Node) / 2;
}

template <class T>
void List<T>::clear() {
  while (ptr_head_) {
    pop_front();
  }
}

template <class T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == end()) {
    throw std::range_error("Invalid List for insert, List is empty");
  }
  Node* new_node = new Node(value);
  new_node->ptr_prev_ = pos.getNode()->ptr_prev_;
  new_node->ptr_next_ = pos.getNode();
  pos.getNode()->ptr_prev_ = new_node;
  if (new_node->ptr_prev_) {
    new_node->ptr_prev_->ptr_next_ = new_node;
  } else {
    ptr_head_ = new_node;
  }
  if (size_ == 0) {
    ptr_tail_ = new_node;
  }
  ++size_;
  return ListIterator(new_node);
}

template <class T>
void List<T>::erase(iterator pos) {
  Node* ptr_rm = pos.getNode();
  if (ptr_rm == nullptr) return;
  if (ptr_rm == ptr_head_) {
    pop_front();
  } else if (ptr_rm == ptr_tail_) {
    pop_back();
  } else {
    Node* prev = ptr_rm->ptr_prev_;
    Node* next = ptr_rm->ptr_next_;
    prev->ptr_next_ = next;
    next->ptr_prev_ = prev;
    delete ptr_rm;
    --size_;
  }
}

template <class T>
void List<T>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  if (!ptr_head_) {
    ptr_head_ = ptr_tail_ = new_node;
  } else {
    ptr_tail_->ptr_next_ = new_node;
    Node* ptr_tmp = ptr_tail_;
    ptr_tail_ = new_node;
    ptr_tail_->ptr_prev_ = ptr_tmp;
  }
  ++size_;
}

template <class T>
void List<T>::pop_back() {
  if (!ptr_head_) {
    throw std::range_error("Invalid List for pop_back, List is empty");
  }
  if (size_ == 1) {
    delete ptr_tail_;
    ptr_tail_ = nullptr;
    ptr_head_ = nullptr;
  } else {
    Node* newTail = ptr_tail_->ptr_prev_;
    newTail->ptr_next_ = nullptr;
    delete ptr_tail_;
    ptr_tail_ = newTail;
  }
  --size_;
}

template <class T>
void List<T>::push_front(const_reference value) {
  Node* new_node = new Node(value);
  if (!ptr_head_) {
    ptr_head_ = ptr_tail_ = new_node;
  } else {
    ptr_head_->ptr_prev_ = new_node;
    new_node->ptr_next_ = ptr_head_;
    ptr_head_ = new_node;
  }
  ++size_;
}

template <class T>
void List<T>::pop_front() {
  if (!ptr_head_) {
    throw std::range_error("Invalid List for pop_front, List is empty");
  }
  if (ptr_head_->ptr_next_ != nullptr) {
    Node* newHead = ptr_head_->ptr_next_;
    newHead->ptr_prev_ = nullptr;
    delete ptr_head_;
    ptr_head_ = newHead;
  } else {
    delete ptr_head_;
    ptr_tail_ = nullptr;
    ptr_head_ = nullptr;
  }
  --size_;
}

template <class T>
void List<T>::swap(List& other) noexcept {
  std::swap(size_, other.size_);
  std::swap(ptr_head_, other.ptr_head_);
  std::swap(ptr_tail_, other.ptr_tail_);
}

template <class T>
void List<T>::merge(List& other) {
  sort();
  other.sort();
  iterator thisIter = begin();
  iterator otherIter = other.begin();
  List buffer;
  while (thisIter != end() && otherIter != end()) {
    if (*thisIter < *otherIter) {
      buffer.push_back(*thisIter);
      ++thisIter;
    } else {
      buffer.push_back(*otherIter);
      ++otherIter;
    }
  }
  while (thisIter != end()) {
    buffer.push_back(*thisIter);
    ++thisIter;
  }
  while (otherIter != end()) {
    buffer.push_back(*otherIter);
    ++otherIter;
  }
  *this = std::move(buffer);
}

template <class T>
void List<T>::splice(const_iterator pos, List& other) {
  if (pos == end()) {
    throw std::range_error("const_iterator pos == nullptr");
  }
  if (this != &other) {
    for (iterator itr = other.begin(); itr != other.end(); ++itr) {
      insert(pos, *itr);
    }
    other.clear();
  }
}

template <class T>
void List<T>::reverse() noexcept {
  if (size_ > 1) {
    Node tmp_head = *ptr_head_;
    Node tmp_tail = *ptr_tail_;
    Node* head_ptr = ptr_head_;
    Node* tail_ptr = ptr_tail_;
    for (size_type i = 0; i < size_ / 2; ++i) {
      head_ptr->value_ = tmp_tail.value_;
      tail_ptr->value_ = tmp_head.value_;
      head_ptr = head_ptr->ptr_next_;
      tail_ptr = tail_ptr->ptr_prev_;
      tmp_head = *head_ptr;
      tmp_tail = *tail_ptr;
    }
  }
}

template <class T>
void List<T>::unique() {
  if (size_ <= 1) {
    return;
  }
  iterator iter = begin();
  value_type value = *iter;
  ++iter;
  while (iter != end()) {
    iterator nextIter(iter.getNode()->ptr_next_);
    if (value == *iter) {
      erase(iter);
      iter = nextIter;
    } else {
      value = *iter;
      ++iter;
    }
  }
}

template <class T>
void List<T>::sort() {
  if (size_ <= 1) {
    return;
  }
  quickSort(ptr_head_, ptr_tail_);
}

template <class T>
template <class... Args>
typename List<T>::iterator List<T>::insert_many(List<T>::iterator pos,
                                                Args&&... args) {
  return insert_many_aux(pos, args...);
}

template <class T>
template <class... Args>
void List<T>::insert_many_back(Args&&... args) {
  insert_many_aux(end(), args...);
}

template <class T>
template <class... Args>
void List<T>::insert_many_front(Args&&... args) {
  insert_many_aux(begin(), args...);
}

template <class T>
typename List<T>::iterator List<T>::insert_many_aux(iterator pos) {
  return pos;
}

template <class T>
template <class U>
typename List<T>::iterator List<T>::insert_many_aux(iterator pos, U&& arg) {
  if (pos == end()) {
    push_back(arg);
  } else {
    pos = insert(pos, arg);
  }
  return pos;
}

template <class T>
template <class U, class... Args>
typename List<T>::iterator List<T>::insert_many_aux(iterator pos, U&& arg,
                                                    Args&&... args) {
  if (pos == end()) {
    push_back(arg);
  } else {
    pos = insert(pos, arg);
    ++pos;
  }
  pos = insert_many_aux(pos, args...);
  // ++pos;
  return pos;
}

template <class T>
typename List<T>::Node* List<T>::partition(Node* low, Node* high) {
  value_type pivotValue = high->value_;
  Node* i = low->ptr_prev_;
  for (Node* j = low; j != high; j = j->ptr_next_) {
    if (j->value_ <= pivotValue) {
      i = (i == nullptr) ? low : i->ptr_next_;
      std::swap(i->value_, j->value_);
    }
  }
  i = (i == nullptr) ? low : i->ptr_next_;
  std::swap(i->value_, high->value_);
  return i;
}

template <class T>
void List<T>::quickSort(Node* low, Node* high) {
  if (low != nullptr && high != nullptr && low != high &&
      low != high->ptr_next_) {
    Node* pivot = partition(low, high);
    quickSort(low, pivot->ptr_prev_);
    quickSort(pivot->ptr_next_, high);
  }
}
