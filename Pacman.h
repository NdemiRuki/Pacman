#include <string>
#include <vector>
#include "2D_graphics.h"
#include "Map.h"
#include "Ghosts.h"





enum TileType { WALL, PATH, TUNNEL, EMPTY };
enum PelletState { EATEN, NOT_EATEN, POWER_PELLET };

class Pacman {
public:

    Pacman(int startX, int startY, Ghosts* ghostArray, int numGhosts);

    void move(int dx, int dy , Map &map);
    void setDirection(int dx, int dy);
    void update(Map& map); // Update position based on direction
    void draw(int idPacmanOpen, int idPacmanClosed, double theta, double scale); // For rendering Pacman
    void loselife();
    void respawn();
    void setGhostVulnerable(int duration);


    // void eatPellet(); 
    // void eatPowerUp(); 

    int getX() const { return x; }
    int getY() const { return y; }
    int getDirX() const { return dirX; }
    int getDirY() const { return dirY; }
    int getLives() const { return lives; }
    int getScore() const { return score; }

private:
    int x, y; // Current position
    double startX, startY; // Respawn position
    int dirX, dirY; // Current direction
    int lives; // Remaining lives
    int score; // Current score

    Ghosts* ghostArray; // Pointer to ghosts for interaction
    int numGhosts; // Number of ghosts

};

