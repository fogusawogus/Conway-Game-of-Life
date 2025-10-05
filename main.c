#include <raylib.h>

#define rows 100
#define columns 100
#define width 1200
#define height 800

// 0 = empty, 1 = alive, 2 = will die, 3 = will be born

int grid[rows][columns] = {0};

void drawGrid() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      DrawRectangleLines(j * width / columns, i * height / rows,
                         width / columns, height / rows, BLACK);
    }
  }
}

void drawTiles() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (grid[i][j] == 1) {
        DrawRectangle(j * width / columns, i * height / rows, width / columns,
                      height / rows, PURPLE);
      }
    }
  }
}

void gameCheck() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      int cellVal = grid[i][j];
      int aliveNeighborCount = 0;
      for (int x = -1; x < 2; x++) {
        for (int z = -1; z < 2; z++) {
          if (j + z < 0 || j + z > 50) {
            continue;
          }
          if (x + i < 0 || x + i > 50) {
            continue;
          }
          if (x == 0 && z == 0) {
            continue;
          }
          if (grid[x + i][j + z] == 1 || grid[x + i][j + z] == 2) {
            aliveNeighborCount++;
          }
        }
      }
      if ((aliveNeighborCount < 2 || aliveNeighborCount > 3) && cellVal == 1) {
        grid[i][j] = 2;
      }
      if (cellVal == 0 && aliveNeighborCount == 3) {
        grid[i][j] = 3;
      }
    }
  }
};

void updateGame() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      int cellVal = grid[i][j];
      switch (cellVal) {
      case 0:
        break;
      case 1:
        break;
      case 2:
        grid[i][j] = 0;
        break;
      case 3:
        grid[i][j] = 1;
        break;
      }
    }
  }
}

int main() {
  InitWindow(width, height, "Game of Life");
  grid[25][25] = 1;
  grid[25][24] = 1;
  grid[25][23] = 1;
  grid[24][24] = 1;
  SetTargetFPS(60);
  float timeSinceLastMove = 0;
  float timeInterval = .5f;

  while (!WindowShouldClose()) {
    timeSinceLastMove += GetFrameTime();
    BeginDrawing();
    ClearBackground(WHITE);
    if (timeSinceLastMove >= timeInterval) {
      gameCheck();
      updateGame();
      timeSinceLastMove = 0.f;
    }
    drawTiles();
    drawGrid();
    EndDrawing();
  }
  return 0;
}
