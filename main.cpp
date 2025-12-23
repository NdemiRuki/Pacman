#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>

#include "windows.h"
#include "2D_graphics.h"
#include "Map.h"
#include "Pacman.h"
#include "Ghosts.h"
#include "Audio.h"
#include "Gamedefs.h"

using namespace std;


int frameCount = 0;

int main(){

    double x = 0.0, y = 0.0; // pacman position
    double xt, yt; // ghost position
    double scale = 2.0, theta = 0.0;
    const double speed = 5.0;

    bool mute = false;
    bool paused = false;
    bool prevKeyM = false;
    bool prevKeyP = false;

    int idWall = -1;
    int idPellet = -1;
    int idPelletPowerUp = -1;
    int idPacmanOpen = -1;
    int idPacmanClosed = -1;
    int idLife = -1;
    int idGhost = -1;
    int deathTimer = 0;
    const int DEATH_DELAY = 30; // frames to wait on death

    initialize_graphics();

    create_sprite("PacmanOpen_16x16.png", idPacmanOpen); // Open mouth sprite
    create_sprite("PacmanClosed_16x16.png", idPacmanClosed); // Closed mouth sprite
    create_sprite("Pellet_9x9.png", idPellet); // Pellet sprite
    create_sprite("Pellet_16x16.png", idPelletPowerUp); // Power-up sprite
    create_sprite("Wall.png", idWall); // Wall sprite
    create_sprite("life_9x9.png", idLife); // Life icon sprite
    
    // add ghost sprite creation here //
    
    Map map; // Create map instance
    map.initializeMap(); // Initialize the maze layout

    int startTileX = 1;
    int startTileY = 1;

    x = tileToPixelX(startTileX); // Starting position of Pacman
    y = tileToPixelY(startTileY);

    Ghosts ghostArray[NUM_GHOSTS]; // Create array of ghosts

    ghostArray[0].setPosition(tileToPixelX(10), tileToPixelY(3)); // Set initial positions
    ghostArray[1].setPosition(tileToPixelX(14), tileToPixelY(3));
    ghostArray[2].setPosition(tileToPixelX(10), tileToPixelY(7));
    ghostArray[3].setPosition(tileToPixelX(14), tileToPixelY(7));


    Pacman pacman(x, y, ghostArray, NUM_GHOSTS); // Create Pacman instance

    xt = tileToPixelX(10); // Starting position of Ghost
    yt = tileToPixelY(3);

    create_sprite("ghost.png", idGhost);

    while(1){

        clear();

        frameCount++;

        if(!paused) update();

        if(pacman.getLives() <= 0){ // Game over condition
          text((char*)"Game Over!", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2, 2.0);
          Sleep(200);
          break;
        }

        if(deathTimer > 0){ // freezes the game briefly on pacman death
            deathTimer--;
            Sleep(120);
            continue; // Skip the rest of the loop while in death delay
        } 
        if(KEY('D')){
            pacman.setDirection(1, 0);
        } else if(KEY('A')) {
            pacman.setDirection(-1, 0);
        }else if(KEY('W')) {
            pacman.setDirection(0, -1);
        }else if(KEY('S')) {
            pacman.setDirection(0, 1);
        }

    pacman.update(map); // Update Pacman's position and check for pellet eating

        // pacman direction for drawing //
        int dx = pacman.getDirX(); // Get current direction
        int dy = pacman.getDirY(); 

        if(dx == 1 && dy == 0) theta = 0.0; // Right
        else if(dx == -1 && dy == 0) theta = PI; // Left
        else if(dx == 0 && dy == -1) theta = -PI / 2; // Up
        else if(dx == 0 && dy == 1) theta = PI / 2; // Down

        // Ghost collision detection //
    for(int i = 0; i < NUM_GHOSTS; i++){
        double dx = pacman.getX() - ghostArray[i].getX();
        double dy = pacman.getY() - ghostArray[i].getY();
        if(sqrt(dx*dx + dy*dy) < TILE_SIZE / 2){
            pacman.loselife();
            deathTimer = DEATH_DELAY; // Set death delay
        }
                // toggle keys //
        bool keyM = KEY('M');
        if(keyM && !prevKeyM){
            mute = !mute; // toggle mute
        }
        prevKeyM = keyM;

        bool keyP = KEY('P');
        if(keyP && !prevKeyP){
            paused = !paused; // toggle pause
        }
        prevKeyP = keyP;

        // Drawing the map //
    map.drawMap(idWall, idPellet, idPelletPowerUp, theta, scale);

    
        // Drawing Pacman //
    pacman.draw(idPacmanOpen, idPacmanClosed, theta, scale);

        // add ghost drawing here //
        for(int i = 0; i < NUM_GHOSTS; i++){
            ghostArray[i].draw(idGhost, theta, scale);
        }

        // score & lives display //
        
    string scoreText = "Score: " + std::to_string(pacman.getScore());
    text((char*)scoreText.c_str(), 10, 10, 1.0);  

         int lives = pacman.getLives();
        for(int i = 0; i < lives; i++){
        double lx = 10 + i * LIFE_ICON_SPACING;
        double ly = 40;

        draw_sprite(idLife, lx, ly, 0.0, LIFE_ICON_SCALE);
    }


    Sleep(120); // Control frame rate

}

    return 0;
    }
}



