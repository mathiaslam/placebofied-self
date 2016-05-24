class Police { 
  int police_x, police_y, police_size;

  Police(int x, int y, int size) {
    police_x = x;
    police_y = y;
    police_size = size;
  }

  void display() {
    fill(164, 242, 255);
    rect(police_x, police_y, police_size, police_size);
    pushMatrix();
    translate(police_x, police_y);
    textSize(24);
    fill(0);
    text("P", 8, 24); 

    popMatrix();
  }
} 