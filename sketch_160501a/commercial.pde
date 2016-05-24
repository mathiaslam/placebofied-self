class Commercial { 
  int commercial_x, commercial_y, commercial_width, commercial_height;

  Commercial (int x, int y, int width, int height) {
    commercial_x = x;
    commercial_y = y;
    commercial_width = width;
    commercial_height = height;
  }

  void display() {
    fill(100, 140, 180);
    rect(commercial_x, commercial_y, commercial_width, commercial_height);
  }
} 