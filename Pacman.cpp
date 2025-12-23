#include "Pacman.h"
#include <iostream>
#include <cmath>
#include <cstdio>
#include "windows.h"
#include "2D_graphics.h"
#include "Map.h"
#include "Gamedefs.h"

using namespace std;

    const int TILE_SIZE   = 32;
    const int MAZE_WIDTH  = 28;
    const int MAZE_HEIGHT = 31;
    const int PACMAN_RADIUS = 14;

class Map; // Forward declaration

Pacman::Pacman(int startX, int startY, Ghosts* ghostArray, int numGhosts){

    

        // Set respawn position // 
    this -> startX = startX; 
    this -> startY = startY; 

    x = startX;
    y = startY;

    dirX = 0;
    dirY = 0;
    lives = 3;
    score = 0;

        // Initialize member variables //
    this->ghosts = ghostArray;
    this->numGhosts = numGhosts;
}

    // Set movement direction //
void Pacman::setDirection(int dx, int dy){
    dirX = dx;
    dirY = dy;
}

    // Move Pacman with collision detection //
void Pacman::move(int dx, int dy, Map &map){

    double nextX = x + dx;
    double nextY = y + dy;

   if(!map.collidesWithWall(nextX, y, PACMAN_RADIUS)) x = nextX;
   if(!map.collidesWithWall(x, nextY, PACMAN_RADIUS)) y = nextY;

   if(x < 0) x = (MAZE_WIDTH - 2) * TILE_SIZE;
   if(x > (MAZE_WIDTH -1) * TILE_SIZE) x = TILE_SIZE;
}
    // Set ghosts vulnerable for a duration //
void Pacman::setGhostVulnerable(int duration){
    // Implementation to set ghosts vulnerable for 'duration' frames
    for(int i = 0; i < numGhosts; i++){
        ghostArray[i].setVulnerable(duration);
    }
}

    // Update Pacman's position and check for pellet eating //
void Pacman::update(Map &map){

    if(lives <= 0) return; // No update if Pacman has no lives left

    const double speed = 5.0;
    move(dirX * speed, dirY * speed, map);

    int tileX = (int)((x + PACMAN_RADIUS) / TILE_SIZE);
    int tileY = (int)((y + PACMAN_RADIUS) / TILE_SIZE);

    if(map.hasPellet(tileX, tileY)){
        map.eatPellet(tileX, tileY);
        score += 10; // Increment score
    }

    if(map.hasPowerUp(tileX, tileY)){
        map.eatPowerUp(tileX, tileY);
        score += 50; // Increment score for power-up

        setGhostVulnerable(300); // duration for vulnerability
    }

    
}

    // Draw Pacman at current position //
void Pacman::draw(int idPacmanOpen, int idPacmanClosed, double theta, double scale){
    if(dirX != 0 || dirY != 0) {
        if(frameCount % 10 < 5)
            draw_sprite(idPacmanOpen, x, y, theta, scale);
        else
            draw_sprite(idPacmanClosed, x, y, theta, scale);
    } else {
        draw_sprite(idPacmanClosed, x, y, theta, scale);
    }
}


    // Respawn Pacman at starting position //
void Pacman::respawn(){
    x = startX;
    y = startY;
    dirX = 0;
    dirY = 0;
}

    // Decrease life count and respawn //
void Pacman::loselife(){
    lives--;
    respawn();
}

int Map::getWidth() const {
    return MAZE_WIDTH;
}

int Map::getHeight() const {
    return MAZE_HEIGHT;
}