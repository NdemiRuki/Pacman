#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H

#include <string>
#include <vector>
#include "Gamedefs.h"

// Simple tile-based Map for Pac-Man
// - Loads from a text file or from a vector of strings
// - Exposes tile queries, pellet tracking, and spawn-finding



enum TileType { WALL, PATH, TUNNEL, EMPTY };
enum PelletState { EATEN, NOT_EATEN, POWER_PELLET };


class Map {
    private:
    TileType tileMap[MAZE_HEIGHT][MAZE_WIDTH]; // 2D array representing the maze tiles
    PelletState** pellets; // 2D array representing pellet states



    public:

    int getWidth() const;
    int getHeight() const;
    
    Map(); // constructor to initialize the map and pellets
    ~Map(); // destructor to clean up dynamic memory

    void initializeMap(); // Initialize the maze layout
    void drawMap(int idWall, int idPellet,int idPelletPowerUp, double theta, double scale); // Draw the maze and pellets

    bool isWall(int x, int y) const; // Check if a position is a wall
    bool hasPellet(int x, int y); // Check if a pellet exists at position
    void eatPellet(int x, int y); // Eat pellet at position
    bool hasPowerUp(int tileX, int tileY); // Check for power-up at position
    void eatPowerUp(int tileX, int tileY); // Eat power-up at position
    bool collidesWithWall(double x, double y, int radius) const; // Check for wall collision
    TileType tileAt(int x, int y) const; // Get tile type at position
};

double tileToPixelX(int tx) {
    return tx * TILE_SIZE + TILE_SIZE / 2.0;
}

double tileToPixelY(int ty) {
    return ty * TILE_SIZE + TILE_SIZE / 2.0;
}


#endif // PACMAN_MAP_H
