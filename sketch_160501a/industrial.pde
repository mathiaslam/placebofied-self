class Industrial { 
  int industrial_x, industrial_y, industrial_width, industrial_height;

  Industrial (int x, int y, int width, int height) {
    industrial_x = x;
    industrial_y = y;
    industrial_width = width;
    industrial_height = height;
  }

  void display() {
    fill(230, 225, 129);
    rect(industrial_x, industrial_y, industrial_width, industrial_height);
  }
} 