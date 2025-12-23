#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstdlib>
// #include "pacman.cpp" need to find the right name after Ndemeire pushed it

enum ghost_mode { CHASE, SCATTERED, FRIGHTENED }; // enumurate the  3different ghost modes
enum ghost_type { RED, PINK, ORANGE, BLUE }; // enumurate the different ghost types

class Ghosts {
private:
	int xt, yt; // Current position
	int dirX, dirY; // Current direction
	ghost_mode mode; // Current mode
	ghost_type type; // Type of ghost
	float distanceToPacman; // Distance to pacman for targeting logic
	int targetX, targetY; // need to put these here (I was getting tons of error before i did )
public:
	void update_ghost_position(const Pacman& pacman, Map& map); // Update position based on direction and mode, but need to have the stuff wrt to the map as well
	void decide(int pacmanX, int pacmanY, int PacmanDirX, int PacmanDirY); // AI logic for ghost movement
	void draw(); // For rendering ghost
	void set_mode(ghost_mode newMode); // Set the ghost's mode
	bool isWall(int x, int y); // placeholder function to check if a position is a wall
	int getX() const; // returns x position
	int getY() const; // returns y position

};
