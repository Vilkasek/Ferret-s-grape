#include "map_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_map_from_csv(TileMap *map, const char *csv_path) {
  FILE *file = fopen(csv_path, "r");
  if (!file) {
    TraceLog(LOG_ERROR, "Could not open map file: %s", csv_path);
    return;
  }

  char line[1024];
  int row = 0;
  int max_col = 0;

  for (int i = 0; i < MAX_MAP_HEIGHT; i++) {
    for (int j = 0; j < MAX_MAP_WIDTH; j++) {
      map->data[i][j] = 0;
    }
  }

  while (fgets(line, sizeof(line), file) && row < MAX_MAP_HEIGHT) {
    int col = 0;
    char *token = strtok(line, ",\n");
    while (token && col < MAX_MAP_WIDTH) {
      map->data[row][col] = atoi(token);
      token = strtok(NULL, ",\n");
      col++;
    }
    if (col > max_col) {
      max_col = col;
    }
    row++;
  }

  map->width = max_col;
  map->height = row;

  map->tile_size = 32;

  fclose(file);

  TraceLog(LOG_INFO, "Loaded map: %dx%d tiles", map->width, map->height);
}
void load_tileset(TileMap *map, const char *tileset_path) {
  map->tileset = LoadTexture(tileset_path);
}

void unload_tilemap(TileMap *map) { UnloadTexture(map->tileset); }

void draw_tilemap(const TileMap *map) {
  for (int y = 0; y < map->height; y++) {
    for (int x = 0; x < map->width; x++) {
      int tile_id = map->data[y][x];
      if (tile_id == 0)
        continue;

      Rectangle src = {(float)((tile_id -1) * map->tile_size), 0.0f,
                       (float)map->tile_size, (float)map->tile_size};

      Vector2 pos = {(float)(x * map->tile_size), (float)(y * map->tile_size)};

      DrawTextureRec(map->tileset, src, pos, WHITE);
    }
  }
}
