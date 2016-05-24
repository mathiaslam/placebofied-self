class River { 
  int river_x, river_y, river_size;

  River(int x, int y, int size) {
    river_x = x;
    river_y = y;
    river_size = size;
  }

  void display() {
    fill(0, 0, 255);
    rect(river_x, river_y, river_size, river_size);
  }
} 