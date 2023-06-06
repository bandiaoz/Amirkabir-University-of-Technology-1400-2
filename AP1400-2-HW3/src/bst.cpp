#include "bst.h"
#include <iostream>
#include <queue>

BST::Node::Node(int value, Node *left, Node *right) : value(value), left(left), right(right) {}

BST::Node::Node() : value(0), left(nullptr), right(nullptr) {}

BST::Node::Node(const Node &node) : Node(node.value, node.left, node.right) {}

std::ostream &operator<<(std::ostream &os, const BST::Node &node) {
  os << node.value;
  return os;
}

auto operator<(const int &a, const BST::Node &node) -> bool { return a < node.value; }
auto operator<=(const int &a, const BST::Node &node) -> bool { return a <= node.value; }
auto operator>(const int &a, const BST::Node &node) -> bool { return a > node.value; }
auto operator>=(const int &a, const BST::Node &node) -> bool { return a >= node.value; }
auto operator==(const int &a, const BST::Node &node) -> bool { return a == node.value; }
auto operator<(const BST::Node &node, const int &a) -> bool { return node.value < a; }
auto operator<=(const BST::Node &node, const int &a) -> bool { return node.value <= a; }
auto operator>(const BST::Node &node, const int &a) -> bool { return node.value > a; }
auto operator>=(const BST::Node &node, const int &a) -> bool { return node.value >= a; }
auto operator==(const BST::Node &node, const int &a) -> bool { return node.value == a; }

BST::BST() : root(nullptr) {}

BST::BST(std::initializer_list<int> list) {
  this->root = nullptr;
  for (auto &value : list) {
    add_node(value);
  }
}

BST::BST(const BST &bst) {
  auto copyTree = [](auto &&self, Node *node) -> Node * {
    if (node == nullptr) {
      return nullptr;
    }
    Node *newNode = new Node(node->value);
    newNode->left = self(self, node->left);
    newNode->right = self(self, node->right);
    return newNode;
  };
  this->root = copyTree(copyTree, bst.root);
}

BST::BST(BST&& bst) {
	this->root = bst.root;
  bst.root = nullptr;
}

BST& BST::operator=(BST& bst) {
  auto bst2 = new BST(bst);
  this->~BST();
  this->root = bst2->root;
  return *this;
}

BST& BST::operator=(BST&& bst) {
  this->root = bst.root;
  bst.root = nullptr;
  return *this;
}

BST::~BST() {
  bfs([](Node *&node) { delete node; });
}

auto BST::get_root() -> Node *& { return root; }

void BST::bfs(std::function<void(Node *&node)> func) const {
  if (root == nullptr) {
    return;
  }
  std::queue<Node *> q;
  q.push(root);
  while (!q.empty()) {
    Node *node = q.front();
    q.pop();
    func(node);
    if (node->left != nullptr) {
      q.push(node->left);
    }
    if (node->right != nullptr) {
      q.push(node->right);
    }
  }
}

auto BST::length() -> std::size_t {
  std::size_t length = 0;
  bfs([&length](Node *&node) { length++; });
  return length;
}

auto BST::add_node(int value) -> bool {
  if (root == nullptr) {
    root = new Node(value);
    return true;
  }
  if (find_node(value) != nullptr) {
    return false;
  }
  Node **node = &root;
  while (*node != nullptr) {
    if (value < (*node)->value) {
      node = &(*node)->left;
    } else {
      node = &(*node)->right;
    }
  }
  *node = new Node(value);
  return true;
}

auto BST::find_node(int value) -> Node ** {
  Node **node = &root;
  while (*node != nullptr) {
    if (value < (*node)->value) {
      node = &(*node)->left;
    } else if (value > (*node)->value) {
      node = &(*node)->right;
    } else {
      return node;
    }
  }
  return nullptr;
}

auto BST::find_parrent(int value) -> Node ** {
  Node **node = &root;
  Node **parrent = nullptr;
  while (*node != nullptr) {
    if (value < (*node)->value) {
      parrent = node;
      node = &(*node)->left;
    } else if (value > (*node)->value) {
      parrent = node;
      node = &(*node)->right;
    } else {
      return parrent;
    }
  }
  return nullptr;
}

auto BST::find_successor(int value) -> Node ** {
  Node **node = find_node(value);
  if (node == nullptr) {
    return nullptr;
  }
  if ((*node)->left != nullptr) {
    node = &(*node)->left;
    while ((*node)->right != nullptr) {
      node = &(*node)->right;
    }
    return node;
  } else {
    Node **parrent = find_parrent(value);
    while (parrent != nullptr && (*parrent)->right != *node) {
      node = parrent;
      parrent = find_parrent((*parrent)->value);
    }
    return parrent;
  }
}

auto BST::delete_node(int value) -> bool {
  Node **node = find_node(value);
  if (node == nullptr) {
    return false;
  }
  if ((*node)->left == nullptr && (*node)->right == nullptr) {
    delete *node;
    *node = nullptr;
  } else if ((*node)->left == nullptr) {
    Node *temp = *node;
    *node = (*node)->right;
    delete temp;
  } else if ((*node)->right == nullptr) {
    Node *temp = *node;
    *node = (*node)->left;
    delete temp;
  } else {
    Node **successor = find_successor(value);
    (*node)->value = (*successor)->value;
    Node *temp = *successor;
    *successor = (*successor)->left;
    delete temp;
  }
  return true;
}

auto operator<<(std::ostream &os, const BST &bst) -> std::ostream & {
  bst.bfs([&os](BST::Node *&node) { os << node->value << " "; });
  return os;
}

auto operator++(BST &bst) -> BST & {
  bst.bfs([](BST::Node *&node) { node->value++; });
  return bst;
}

auto operator++(BST &bst, int) -> BST {
  BST b = BST(bst);
  bst.bfs([](BST::Node *&node) { node->value++; });
  return b;
}