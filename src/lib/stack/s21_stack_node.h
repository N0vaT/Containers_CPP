#ifndef S21_LIB_STACK_NODE_H
#define S21_LIB_STACK_NODE_H

#include "s21_stack.h"

template <class T>
struct StackNode {
  explicit StackNode(T val) : value(val), nextNode(nullptr) {}

  StackNode(T val, StackNode* next) : StackNode(val) { nextNode = next; }

  T value;
  StackNode* nextNode;
};

#endif  // S21_LIB_STACK_NODE_H