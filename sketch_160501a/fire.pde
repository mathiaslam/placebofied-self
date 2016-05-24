class Fire { 
  int fire_x, fire_y, fire_size;

  Fire(int x, int y, int size) {
    fire_x = x;
    fire_y = y;
    fire_size = size;
  }

  void display() {
    fill(218, 90, 34);
    rect(fire_x, fire_y, fire_size, fire_size);
    pushMatrix();
    translate(fire_x, fire_y);
    textSize(24);
    fill(0);
    text("F", 8, 24); 
    popMatrix();
  }
} 