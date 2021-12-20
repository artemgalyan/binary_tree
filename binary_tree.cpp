#include "binary_tree.h"

template<typename T>
bool BinaryTree<T>::IsEmpty() const {
  return root_ == nullptr;
}

template<typename T>
T &BinaryTree<T>::SearchInSubTree(int search_key, Node<T> *finder) {
  if (finder == nullptr)
    throw std::invalid_argument("No element with this key");
  else if (finder->key_ == search_key)
    return finder->value_;
  else if (search_key > finder->key_)
    return SearchInSubTree(search_key, finder->left_);
  else
    return SearchInSubTree(search_key, finder->right_);
}

template<typename T>
void BinaryTree<T>::Push(int push_key, T push_value) {
  ++size_;
  if (IsEmpty()) {
    root_ = new Node(push_key, push_value, root_);
    return;
  }
  Node<T> *push_node = new Node(push_key, push_value, root_);
  Node<T> *ahead_node = root_;
  Node<T> *this_node = root_;
  while (ahead_node != nullptr) {
    this_node = ahead_node;
    if (push_key > this_node->key_)
      ahead_node = this_node->left_;
    else
      ahead_node = this_node->right_;
  }
  if (push_key > this_node->key_)
    this_node->left_ = push_node;
  else
    this_node->right_ = push_node;
}

template<typename T>
T &BinaryTree<T>::Get(int search_key) {
  return SearchInSubTree(search_key, root_);
}

template<typename T>
T &BinaryTree<T>::operator[](int search_key) {
  return Get(search_key);
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
  if (!IsEmpty()) {
    auto delFunc = [](Node<T> *node, T value) -> bool {
      delete node;
      return true;
    };
    TreeTraversal(delFunc, root_->value_);
  }
}

template<typename T>
int BinaryTree<T>::TreeTraversal(bool (*function)(Node<T> *, T), T value, Node<T> *start_point) const {
  if (IsEmpty())
    throw std::logic_error("The container is empty!");
  if (start_point == nullptr)
    start_point = root_;
  int count = 0;
  if (start_point->left_ != nullptr && start_point->right_ != nullptr)
    count += TreeTraversal(&*function, value, start_point->left_)
        + TreeTraversal(&*function, value, start_point->right_);
  else if (start_point->left_ != nullptr && start_point->right_ == nullptr)
    count += TreeTraversal(&*function, value, start_point->left_);
  else if (start_point->left_ == nullptr && start_point->right_ != nullptr)
    count += TreeTraversal(&*function, value, start_point->right_);
  return count + static_cast<int>(function(start_point, value));
}

template<typename T>
int BinaryTree<T>::Count(const T &value) const {
  auto func = [](Node<T> *point, T val) -> bool {
    return point->value_ == val;
  };
  return TreeTraversal(func, value);
}

template<typename T>
bool BinaryTree<T>::Contains(const T &value) const {
  return Count(value);
}
