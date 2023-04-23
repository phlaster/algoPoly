#include <iostream>
#include "Class_RBTree.cpp"


RedBlackTree::RedBlackTree() {
  ENDNULL = new Node;
  ENDNULL->color = BLACK;
  ENDNULL->left = nullptr;
  ENDNULL->right = nullptr;
  root = ENDNULL; // Указатель на родителя корня - пустой
}
void RedBlackTree::initializeNULLNode(NodePtr node, NodePtr parent) {
  node->data = 0;
  node->parent = parent;
  node->left = nullptr;
  node->right = nullptr;
  node->color = BLACK;
}
void RedBlackTree::balanceAfterDelete(NodePtr pivot) {
  NodePtr s;
  while (pivot != root && pivot->color == BLACK) {
    if (pivot == pivot->parent->left) {
      s = pivot->parent->right;
      if (s->color == RED) {
        s->color = BLACK;
        pivot->parent->color = RED;
        leftRotate(pivot->parent);
        s = pivot->parent->right;
      }

      if (s->left->color == BLACK && s->right->color == BLACK) {
        s->color = RED;
        pivot = pivot->parent;
      } else {
        if (s->right->color == BLACK) {
          s->left->color = BLACK;
          s->color = RED;
          rightRotate(s);
          s = pivot->parent->right;
        }

        s->color = pivot->parent->color;
        pivot->parent->color = BLACK;
        s->right->color = BLACK;
        leftRotate(pivot->parent);
        pivot = root;
      }
    } else {
      s = pivot->parent->left;
      if (s->color == RED) {
        s->color = BLACK;
        pivot->parent->color = RED;
        rightRotate(pivot->parent);
        s = pivot->parent->left;
      }

      if (s->right->color == BLACK && s->right->color == BLACK) {
        s->color = RED;
        pivot = pivot->parent;
      } else {
        if (s->left->color == BLACK) {
          s->right->color = BLACK;
          s->color = RED;
          leftRotate(s);
          s = pivot->parent->left;
        }

        s->color = pivot->parent->color;
        pivot->parent->color = BLACK;
        s->left->color = BLACK;
        rightRotate(pivot->parent);
        pivot = root;
      }
    }
  }
  pivot->color = BLACK;
  std::cout << "Tree balanced after deletion!" << std::endl;
}
void RedBlackTree::subtreeReplace(NodePtr oldBranch, NodePtr newBranch) {
  if (oldBranch->parent == nullptr) {
    root = newBranch;
  } else if (oldBranch == oldBranch->parent->left) {
    oldBranch->parent->left = newBranch;
  } else {
    oldBranch->parent->right = newBranch;
  }
  newBranch->parent = oldBranch->parent;
}
void RedBlackTree::deleteNodeHelper(NodePtr node, int value) {
  NodePtr z = ENDNULL;
  NodePtr x, y;
  while (node != ENDNULL) {
    if (node->data == value) {
      z = node;
    }
    if (node->data <= value) {
      node = node->right;
    } else {
      node = node->left;
    }
  }

  if (z == ENDNULL) {
    std::cout << "Value " << value << " was not found in the tree" << std::endl;
    return;
  }

  y = z;
  int y_original_color = y->color;
  if (z->left == ENDNULL) {
    x = z->right;
    subtreeReplace(z, z->right);
  } else if (z->right == ENDNULL) {
    x = z->left;
    subtreeReplace(z, z->left);
  } else {
    y = minimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      subtreeReplace(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    subtreeReplace(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  delete z;
  std::cout << "Node with value " << value << " deleted!" << std::endl;
  if (y_original_color == BLACK) {
    balanceAfterDelete(x);
  }
}
void RedBlackTree::balanceAfterInsert(NodePtr pivot) {
  NodePtr u;
  while (pivot->parent->color == RED) {
    if (pivot->parent == pivot->parent->parent->right) {
      u = pivot->parent->parent->left;
      if (u->color == RED) {
        u->color = BLACK;
        pivot->parent->color = BLACK;
        pivot->parent->parent->color = RED;
        pivot = pivot->parent->parent;
      } else {
        if (pivot == pivot->parent->left) {
          pivot = pivot->parent;
          rightRotate(pivot);
        }
        pivot->parent->color = BLACK;
        pivot->parent->parent->color = RED;
        leftRotate(pivot->parent->parent);
      }
    } else {
      u = pivot->parent->parent->right;

      if (u->color == RED) {
        u->color = BLACK;
        pivot->parent->color = BLACK;
        pivot->parent->parent->color = RED;
        pivot = pivot->parent->parent;
      } else {
        if (pivot == pivot->parent->right) {
          pivot = pivot->parent;
          leftRotate(pivot);
        }
        pivot->parent->color = BLACK;
        pivot->parent->parent->color = RED;
        rightRotate(pivot->parent->parent);
      }
    }
    if (pivot == root) {
      break;
    }
  }
  root->color = BLACK;
  std::cout << "Tree balanced after insertion!" << std::endl;
}
void RedBlackTree::leftRotate(NodePtr pivot) {
  NodePtr y = pivot->right;
  pivot->right = y->left;
  if (y->left != ENDNULL) {
    y->left->parent = pivot;
  }
  y->parent = pivot->parent;
  if (pivot->parent == nullptr) {
    this->root = y;
  } else if (pivot == pivot->parent->left) {
    pivot->parent->left = y;
  } else {
    pivot->parent->right = y;
  }
  y->left = pivot;
  pivot->parent = y;
}
void RedBlackTree::rightRotate(NodePtr pivot) {
  NodePtr y = pivot->left;
  pivot->left = y->right;
  if (y->right != ENDNULL) {
    y->right->parent = pivot;
  }
  y->parent = pivot->parent;
  if (pivot->parent == nullptr) {
    this->root = y;
  } else if (pivot == pivot->parent->right) {
    pivot->parent->right = y;
  } else {
    pivot->parent->left = y;
  }
  y->right = pivot;
  pivot->parent = y;
}
NodePtr RedBlackTree::maximum(NodePtr node) {
  while (node->right != ENDNULL) {
    node = node->right;
  }
  return node;
}
NodePtr RedBlackTree::minimum(NodePtr node) {
  while (node->left != ENDNULL) {
    node = node->left;
  }
  return node;
}
NodePtr RedBlackTree::successor(NodePtr thisNode) {
  if (thisNode->right != ENDNULL) {
    return minimum(thisNode->right);
  }
  NodePtr y = thisNode->parent;
  while (y != ENDNULL && thisNode == y->right) {
    thisNode = y;
    y = y->parent;
  }
  return y;
}
NodePtr RedBlackTree::predecessor(NodePtr thisNode) {
  if (thisNode->left != ENDNULL) {
    return maximum(thisNode->left);
  }
  NodePtr y = thisNode->parent;
  while (y != ENDNULL && thisNode == y->left) {
    thisNode = y;
    y = y->parent;
  }
  return y;
}
void RedBlackTree::addNode(int value) {
  NodePtr node = new Node;
  node->parent = nullptr; // По умолчанию указатель на родителя всегда пустой
  node->data = value;
  node->left = ENDNULL;
  node->right = ENDNULL;
  node->color = RED;

  NodePtr y = nullptr;
  NodePtr x = this->root;

  while (x != ENDNULL) {
    y = x;
    if (node->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  node->parent = y;
  if (y == nullptr) {
    root = node;
  } else if (node->data < y->data) {
    y->left = node;
  } else {
    y->right = node;
  }

  if (node->parent == nullptr) {
    node->color = BLACK;
    std::cout << "Value " << value << " inserted!" << std::endl;
    return;
  }

  if (node->parent->parent == nullptr) {
    std::cout << "Value " << value << " inserted!" << std::endl;
    return;
  }
  std::cout << "Value " << value << " inserted!" << std::endl;
  balanceAfterInsert(node);
}
void RedBlackTree::deleteNode(int data) {
  deleteNodeHelper(this->root, data);
}