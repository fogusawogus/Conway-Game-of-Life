#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define rows 75 * 2
#define columns 75 * 2
#define width 1200
#define height 800
#define maxWidth 5000
#define maxHeight 5000

// 0 = empty, 1 = alive, 2 = will die, 3 = will be born

int grid[rows][columns] = {0};

void drawGrid() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      DrawRectangleLines(j * maxWidth / columns, i * maxHeight / rows,
                         maxWidth / columns, maxHeight / rows, BLACK);
    }
  }
}

void drawTiles() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (grid[i][j] == 1) {
        DrawRectangle(j * maxWidth / columns, i * maxHeight / rows,
                      maxWidth / columns, maxWidth / rows, RAYWHITE);
      }
    }
  }
}

void gameCheck() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      int cellVal = grid[i][j];
      int aliveNeighborCount = 0;
      // checks the square around the selected point
      for (int x = -1; x < 2; x++) {
        for (int z = -1; z < 2; z++) {
          if (j + z < 0 || j + z >= columns) {
            continue;
          }
          if (x + i < 0 || x + i >= rows) {
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
      // checks what should be done to the point
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

void randomSeed() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      int num = rand() % 100;
      if (num > 75) {
        grid[i][j] = 1;
      }
    }
  }
}

int main() {
  srand(time(NULL));
  InitWindow(width, height, "Game of Life");
  SetTargetFPS(60);
  float timeSinceLastMove = 0;
  float timeInterval = .1f;
  int iterations = 0;

  Vector2 *target = &((Vector2){.x = maxWidth / 2.f, .y = maxHeight / 2.f});

  float zoom = 1.f;

  Camera2D camera = {0};
  camera.zoom = zoom;
  camera.rotation = 0;
  camera.offset = (Vector2){.x = width / 2.f, .y = height / 2.f};
  camera.target = *target;

  randomSeed();

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_W)) {
      target->y -= 50.f;
    }
    if (IsKeyDown(KEY_A)) {
      target->x -= 50.f;
    }
    if (IsKeyDown(KEY_S)) {
      target->y += 50.f;
    }
    if (IsKeyDown(KEY_D)) {
      target->x += 50.f;
    }
    if (IsKeyDown(KEY_I)) {
      zoom += .01f;
    }
    if (IsKeyDown(KEY_O)) {
      zoom -= .01f;
    }
    if (IsKeyDown(KEY_F))
      timeInterval -= .005f;
    if (IsKeyDown(KEY_R))
      timeInterval += .005f;
    if (timeInterval < .05f)
      timeInterval = .05f;
    if (timeInterval > .25f)
      timeInterval = .25f;
    if (zoom > 2.f)
      zoom = 2.f;
    if (zoom < .1f)
      zoom = .1f;
    camera.zoom = zoom;
    camera.target = *target;
    timeSinceLastMove += GetFrameTime();
    if (timeSinceLastMove >= timeInterval) {
      gameCheck();
      updateGame();
      iterations++;
      timeSinceLastMove = 0.f;
    }
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(BLACK);
    drawTiles();
    drawGrid();
    EndMode2D();
    DrawText(TextFormat("Iterations: %i", iterations), 0, height - 24, 24,
             RAYWHITE);
    DrawText(TextFormat("Time interval: %.3f", timeInterval), 0,
             height - 24 * 2, 24, RAYWHITE);
    DrawFPS(0, 0);
    EndDrawing();
  }
  return 0;
}
