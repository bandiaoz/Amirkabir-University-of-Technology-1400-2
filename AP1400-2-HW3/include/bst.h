#ifndef BST_H
#define BST_H
#include <functional>

class BST {
 public:
  class Node;
  BST();
  BST(std::initializer_list<int> list);
  BST(const BST &bst); // copy constructor
  BST(BST&& bst); //move copy constructor
  BST& operator=(BST& bst); //copy assignment
  BST& operator=(BST&& bst); //move assignment
  ~BST();

  auto get_root() -> Node *&;
  void bfs(std::function<void(Node *&node)> func) const;
  auto length() -> std::size_t;
  auto add_node(int value) -> bool;
  auto find_node(int value) -> Node **;
  auto find_parrent(int value) -> Node **;
  auto find_successor(int value) -> Node **;
  auto delete_node(int value) -> bool;

  friend auto operator<<(std::ostream &os, const BST &bst) -> std::ostream &;
  friend auto operator++(BST &bst) -> BST &;
  friend auto operator++(BST &bst, int) -> BST;

 private:
  Node *root;
};

class BST::Node {
 public:
  Node(int value, Node *left = nullptr, Node *right = nullptr);
  Node();
  Node(const Node &node);
  friend auto operator<<(std::ostream &os, const Node &node) -> std::ostream &;
  friend auto operator<(const int &a, const Node &node) -> bool;
  friend auto operator<=(const int &a, const Node &node) -> bool;
  friend auto operator>(const int &a, const Node &node) -> bool;
  friend auto operator>=(const int &a, const Node &node) -> bool;
  friend auto operator==(const int &a, const Node &node) -> bool;
  friend auto operator<(const Node &node, const int &a) -> bool;
  friend auto operator<=(const Node &node, const int &a) -> bool;
  friend auto operator>(const Node &node, const int &a) -> bool;
  friend auto operator>=(const Node &node, const int &a) -> bool;
  friend auto operator==(const Node &node, const int &a) -> bool;

  int value;
  Node *left;
  Node *right;
};

#endif  // BST_H