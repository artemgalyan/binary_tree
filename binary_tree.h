#pragma once

#include <stdexcept>
#include <iostream>

template<class T>
class BinaryTree {
 private:
  template<class U>
  class Node {
   public:
    explicit Node(int key, U value, Node<U> *prev = nullptr) : value_(value), prev_(prev), key_(key) {};
    Node<U> *prev_ = nullptr;
    Node<U> *left_ = nullptr;
    Node<U> *right_ = nullptr;
    int key_;
    U value_;
  };
 private:
  Node<T> *root_ = nullptr;
  size_t size_ = 0;
 public:
  ~BinaryTree();
  explicit BinaryTree() = default;
  explicit BinaryTree(int key, T value) : root_(new Node<T>(key, value)), size_(0) {};
  bool Push(int push_key, T push_value);
  T &Get(int search_key);
  T &operator[](int search_key);
  [[nodiscard]] bool IsEmpty() const;
  int Count(const T& value) const;
  bool Contains(const T& value) const;
  void Print() const;
 private:
  T &SearchInSubTree(int search_key, Node<T> *finder);
  int TreeTraversal(bool (*function)(Node<T>*, T), T value, Node<T>* start_point = nullptr) const;
};