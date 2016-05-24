class Tree { 

  int tree_x, tree_y, tree_size;
  Tree(int x, int y, int size) {
    tree_x = x;
    tree_y = y;
    tree_size = size;
  }

  void display() {
    fill(0, 150, 56);
    rect(tree_x, tree_y, tree_size, tree_size);
  }
} 