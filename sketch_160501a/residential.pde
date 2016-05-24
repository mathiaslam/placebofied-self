class Residential { 
  int residential_x, residential_y, residential_width, residential_height;

  Residential(int x, int y, int width, int height) {
    residential_x = x;
    residential_y = y;
    residential_height = height;
    residential_width = width;
  }

  void display() {
    fill(125, 180, 54);
    rect(residential_x, residential_y, residential_width, residential_height);
  }
} 