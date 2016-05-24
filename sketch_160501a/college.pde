class College { 
  int college_x, college_y, college_size;

  College(int x, int y, int size) {
    college_x = x;
    college_y = y;
    college_size = size;
  }

  void display() {
    fill(164, 242, 255);
    rect(college_x, college_y, college_size, college_size);
    pushMatrix();
    translate(college_x, college_y);
    textSize(24);
    fill(0);
    text("C", 8, 24); 

    popMatrix();
  }
} 