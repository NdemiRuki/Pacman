#pragma once
#include <cstdio>

const int TILE_SIZE   = 32;
const int MAZE_WIDTH  = 28;
const int MAZE_HEIGHT = 31;
const int SCREEN_WIDTH  = MAZE_WIDTH * TILE_SIZE;
const int SCREEN_HEIGHT = MAZE_HEIGHT * TILE_SIZE;
const double LIFE_ICON_SCALE = 0.5;
const int LIFE_ICON_SPACING = 28;
const int NUM_GHOSTS = 4;

const double PI = 3.141592653589793;
const double PIXELS_PER_FRAME = 1.0;