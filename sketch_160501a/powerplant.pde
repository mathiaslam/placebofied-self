class Powerplant { 
  int powerplant_x, powerplant_y, powerplant_size;

  Powerplant(int x, int y, int size) {
    powerplant_x = x;
    powerplant_y = y;
    powerplant_size = size;
  }

  void display() {
    fill(25, 200, 200);
    rect(powerplant_x, powerplant_y, powerplant_size, powerplant_size);
    pushMatrix();
    translate(powerplant_x, powerplant_y);
    textSize(24);
    fill(0);
    text("P", 8, 24); 
    popMatrix();
  }
} 