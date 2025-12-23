#include "Audio.h"
#include <iostream>
#include <cmath>
#include <windows.h> // has all the audio stuff in it
#include <cstdio>
#include "Gamedefs.h"
pragma comment(lib, "winmm.lib") // This is key for playing audio files


void  play_eat_dot();
{
	Beep(1000, 100); // I just learned about this beep function, built-in and pretty cool
}

void  play_eat_power_pellet();
{
	Beep(800, 200);
	Beep(1200, 200);
}

void  play_eat_ghost();
{
	// use the sounds asynchronously to avoid blocking
	PlaySounds("eat_ghost.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void  play_pacman_death();
{
	PlaySounds("pacman_death.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void play_background_music();
{
	PlaySounds("background_music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void stop_background_music();
// not sure about this one

void home_sound();
{
	PlaySounds("home_sound.wav", NULL, SND_FILENAME | SND_ASYNC);
}






#include "Audio.h"
#include <iostream>
#include <cmath>
#include <windows.h> // has all the audio stuff in it
#include <cstdio>
pragma comment(lib, "winmm.lib") // This is key for playing audio files


void  play_eat_dot();
{
	Beep(1000, 100); // I just learned about this beep function, built-in and pretty cool
}

void  play_eat_power_pellet();
{
	Beep(800, 200);
	Beep(1200, 200);
}

void  play_eat_ghost();
{
	// use the sounds asynchronously to avoid blocking
	PlaySounds("eat_ghost.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void  play_pacman_death();
{
	PlaySounds("pacman_death.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void play_background_music();
{
	PlaySounds("background_music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void stop_background_music();
// not sure about this one

void home_sound();
{
	PlaySounds("home_sound.wav", NULL, SND_FILENAME | SND_ASYNC);
}





