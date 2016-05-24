class Hospital { 
  int hospital_x, hospital_y, hospital_size;

  Hospital(int x, int y, int size) {
    hospital_x = x;
    hospital_y = y;
    hospital_size = size;
  }

  void display() {
    fill(25, 200, 200);
    rect(hospital_x, hospital_y, hospital_size, hospital_size);
    pushMatrix();
    translate(hospital_x, hospital_y);
    textSize(24);
    fill(0);
    text("H", 8, 24); 
    popMatrix();
  }
} 