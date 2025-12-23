#include "Ghosts.h"
#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Pacman.h"
#include "Gamedefs.h"
#include "Map.h"


class Map 
{
public:
	bool isWall(int x, int y) const;
};

using namespace std;
// Ghost class implementation


static bool canMove(int x, int y, Map &map) // placeholder function to check if a position is a wall
{
	int tx = x / TILE_SIZE; 
	int ty = y / TILE_SIZE; 
	return !map.isWall(tx, ty); // assuming map.tile returns the tile type at given coordinates, I had them as TIleX and TileY and was shocked it wasn't working
}

void Ghosts::update_ghost_position(const Pacman& pacman, Map& map)
{
	int pacmanX = pacman.getX();
	int pacmanY = pacman.getY();

	// PRESERVATION: Keeping your distance logic, just adding explicit double casts
	this->distanceToPacman = sqrt(pow((double)this->xt - (double)pacmanX, 2.0) +
		pow((double)this->yt - (double)pacmanY, 2.0));

	this->decide(pacmanX, pacmanY, 0, 0);

	// Choose best direction before moving
	int bestDir = chosing_best_direction(this->xt, this->yt, this->targetX, this->targetY, map);

	int dx[4] = { 0, 0, -1, 1 };
	int dy[4] = { -1, 1, 0, 0 };

	this->dirX = dx[bestDir];
	this->dirY = dy[bestDir];
}

void Ghosts::decide(int pacmanX, int pacmanY, int PacmanDirX, int PacmanDirY) // THis is where the ghosts are supposed to "think " about what to do based on their mode and type
{
	if(mode==CHASE) 
	{
		if(type==RED) // It directly targets pacman
		{
				// Move towards pacman logic
			targetX = pacmanX;
			targetY = pacmanY;

		}
		else if(type==PINK) 
		{
			targetX = pacmanX + 4 * PacmanDirX; // the pink ghost always targets 4 tiles ahead of pacman in the direction pacman is moving
			targetY = pacmanY + 4 * PacmanDirY;
		}
		else if(type==BLUE) // It targets a position based on both pacman and red ghost
		{
			// Complex targeting logic based on pacman and red ghost position
		}
		else if(type==ORANGE) 
		{
			if(distanceToPacman > 8) // this is the stuff where the orange ghost targets pacman within 8 but otherwise does random stuff - like it goes towarsd corner 
			{
				targetX = pacmanX; // same as red ghost
				targetY = pacmanY;
			} 
			else 
			{
				targetX = 1;
				targetY = 1; // Move to corner logic
			}
		}
	}
	else if (mode == SCATTERED) // Each of the ghosts targets a seperate corner (I dindn't even know this but a guy on YT explained it to me)
	{
		if(type==RED) 
		{
			targetX = MAP_WIDTH - 1;
			targetY = 0; 
		}
		else if(type==PINK) 
		{
			targetX = 0;
			targetY = 0; 
		}
		else if(type==BLUE) 
		{
			targetX = MAP_WIDTH - 1;
			targetY = MAP_HEIGHT - 1; 
		}
		else if(type==ORANGE) 
		{
			targetX = 0;
			targetY = MAP_HEIGHT - 1; // Bottom-left corner
		}
	
	}
	else if(mode==FRIGHTENED) 
	{
		targetX = rand() % MAP_WIDTH; 
		targetY = rand() % MAP_HEIGHT; 
	}
}

int Ghosts::chosing_best_direction(int ghostX, int ghostY, int targetX, int targetY, const Map& map)
{
	int best_direction = 0;
	double shortest_distance = 1e9;

	int dX[4] = { 0, 0, -1, 1 };
	int dY[4] = { -1, 1, 0, 0 };

	for (int i = 0; i < 4; i++) {
		int nx = ghostX + dX[i];
		int ny = ghostY + dY[i];

		if (map.isWall(nx / TILE_SIZE, ny / TILE_SIZE))
			continue;

		double dist = sqrt(pow((double)nx - (double)targetX, 2.0) + pow((double)ny - (double)targetY, 2.0));
		if (dist < shortest_distance) {
			shortest_distance = dist;
			best_direction = i;
		}
	}
	return best_direction;
}

void Ghosts::draw()
{

}
