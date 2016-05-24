class Library { 
  int library_x, library_y, library_size;

  Library(int x, int y, int size) {
    library_x = x;
    library_y = y;
    library_size = size;
  }

  void display() {
    fill(164, 242, 255);
    rect(library_x, library_y, library_size, library_size);
    pushMatrix();
    translate(library_x, library_y);
    textSize(20);
    fill(0);
    text("L", 8, 24); 

    popMatrix();
  }
} 