class School { 
  int school_x, school_y, school_size;

  School(int x, int y, int size) {
    school_x = x;
    school_y = y;
    school_size = size;
  }

  void display() {
    fill(25, 200, 200);
    rect(school_x, school_y, school_size, school_size);
    pushMatrix();
    translate(school_x, school_y);
    textSize(24);
    fill(0);
    text("S", 8, 24); 
    popMatrix();
  }
} 