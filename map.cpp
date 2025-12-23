#include "Map.h"
#include <iostream>
#include <fstream>
#include "2D_graphics.h"

using namespace std;



Map::Map() {

    // Allocate dynamic memory for pellets 2D array
    pellets = new PelletState*[MAZE_HEIGHT];
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        pellets[i] = new PelletState[MAZE_WIDTH];
    }

}

Map::~Map() {
    // Clean up dynamic memory
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        delete[] pellets[i];
    }
    delete[] pellets;
}

void Map::initializeMap() {
    // Set up the maze layout and pellet positions
    // Example: tileMap[0][0] = WALL; pellets[1][1] = EATEN;

    for(int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            // Initialize tileMap and pellets based on maze design
            if(i == 0 || i == MAZE_HEIGHT - 1 || j == 0 || j == MAZE_WIDTH - 1) {
                tileMap[i][j] = WALL; // Set borders as walls
                pellets[i][j] = EATEN; // No pellets on walls
            } else {
                tileMap[i][j] = PATH; // Set inner area as path
                pellets[i][j] = NOT_EATEN; // Place pellets in empty spaces
            }
        }
    }

        int tunnelRow = MAZE_HEIGHT / 2;
    tileMap[tunnelRow][0] = TUNNEL; // Left tunnel
    tileMap[tunnelRow][MAZE_WIDTH - 1] = TUNNEL; // Right tunnel
    pellets[tunnelRow][0] = EATEN; // No pellet in tunnel
    pellets[tunnelRow][MAZE_WIDTH - 1] = EATEN; // No pellet in tunnel


     // Place power pellets//
    pellets[1][1] = POWER_PELLET;
    pellets[1][MAZE_WIDTH - 2] = POWER_PELLET;
    pellets[MAZE_HEIGHT - 2][1] = POWER_PELLET;
    pellets[MAZE_HEIGHT - 2][MAZE_WIDTH - 2] = POWER_PELLET;

}

void Map::drawMap(int idWall, int idPellet,int idPelletPowerUp, double theta, double scale) {
    // Draw the maze and pellets using the 2D graphics library
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            // Draw tiles based on tileMap[y][x]
            // Draw pellets based on pellets[y][x]
            double px = tileToPixelX(x);
            double py = tileToPixelY(y);

            if(tileMap[y][x] == WALL){
                draw_sprite(idWall, px, py, theta, scale);
            }
            else if(pellets[y][x] == NOT_EATEN){
                draw_sprite(idPellet, px, py, theta, scale);
            }
            else if(pellets[y][x] == POWER_PELLET){
                draw_sprite(idPelletPowerUp, px, py, theta, scale);
            }
        }
    }
}

bool Map::isWall(int x, int y) const{
    if(x < 0 || x >= MAZE_WIDTH || y < 0 || y >= MAZE_HEIGHT) {
        return true; // Out of bounds treated as wall
    }
    return tileMap[y][x] == WALL;
}

bool Map::hasPellet(int x, int y){
    if(x < 0 || x >= MAZE_WIDTH || y < 0 || y >= MAZE_HEIGHT) {
        return false; // Out of bounds
    }
    return pellets[y][x] == NOT_EATEN;
}

void Map::eatPellet(int x, int y){
  if(x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT){
    pellets[y][x] = EATEN;
  }
}

bool Map::hasPowerUp(int tileX, int tileY){
    if(tileX >= 0 && tileX < MAZE_WIDTH && tileY >= 0 && tileY < MAZE_HEIGHT){
        return pellets[tileY][tileX] == POWER_PELLET;
    }
  return false;
}

void Map::eatPowerUp(int tileX, int tileY){
  if(tileX >= 0 && tileX < MAZE_WIDTH && tileY >= 0 && tileY < MAZE_HEIGHT){
    pellets[tileY][tileX] = EATEN;
  }
  
}

bool Map::collidesWithWall(double x, double y, int radius) const{
    int left = (x - radius) / TILE_SIZE;
    int right = (x + radius) / TILE_SIZE;
    int top = (y - radius) / TILE_SIZE;
    int bottom = (y + radius) / TILE_SIZE;

    if(left < 0 || right >= MAZE_WIDTH || top < 0 || bottom >= MAZE_HEIGHT) {
        return true; // Out of bounds treated as wall
    }

    return isWall(left, top) || isWall(right, top) ||
           isWall(left, bottom) || isWall(right, bottom);

}

TileType Map::tileAt(int x, int y) const{
   if(x < 0 || x >= MAZE_WIDTH || y < 0 || y >= MAZE_HEIGHT) {
        return WALL; // Out of bounds treated as wall
    }
    return tileMap[y][x];
}

int Map::getWidth() const {
    return MAZE_WIDTH;
}

int Map::getHeight() const {
    return MAZE_HEIGHT;
}

