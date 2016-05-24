class Road { 
  int road_x, road_y, road_size;

  Road(int x, int y, int size) {
    road_x = x;
    road_y = y;
    road_size = size;
  }

  void display() {
    fill(120);
    rect(road_x, road_y, road_size, road_size);
  }
} 