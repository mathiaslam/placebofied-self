class Smallpark { 
  int smallpark_x, smallpark_y, smallpark_size;

  Smallpark(int x, int y, int size) {
    smallpark_x = x;
    smallpark_y = y;
    smallpark_size = size;
  }

  void display() {
    fill(25, 200, 200);
    rect(smallpark_x, smallpark_y, smallpark_size, smallpark_size);
    pushMatrix();
    translate(smallpark_x, smallpark_y);
    textSize(10);
    fill(0);
    text("P", 4, 14); 
    popMatrix();
  }
} 