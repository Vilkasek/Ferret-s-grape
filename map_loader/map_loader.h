#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "raylib.h"

#define MAX_MAP_WIDTH 32
#define MAX_MAP_HEIGHT 32

typedef struct {
  int data[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
  int width;
  int height;
  Texture2D tileset;
  int tile_size;
} TileMap;

void load_map_from_csv(TileMap *map, const char *csv_path);
void load_tileset(TileMap *map, const char *tileset_path);
void unload_tilemap(TileMap *map);
void draw_tilemap(const TileMap *map);

#endif
