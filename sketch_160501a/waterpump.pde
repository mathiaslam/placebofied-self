class Waterpump { 
  int waterpump_x, waterpump_y, waterpump_size;

  Waterpump(int x, int y, int size) {
    waterpump_x = x;
    waterpump_y = y;
    waterpump_size = size;
  }

  void display() {
    fill(25, 200, 200);
    rect(waterpump_x, waterpump_y, waterpump_size, waterpump_size);
    pushMatrix();
    translate(waterpump_x, waterpump_y);
    textSize(10);
    fill(0);
    text("W", 4, 14); 
    popMatrix();
  }
} 