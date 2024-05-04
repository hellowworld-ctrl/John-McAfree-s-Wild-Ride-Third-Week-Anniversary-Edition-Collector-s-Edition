#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std; 

int main() {

	initscr();
	timeout(1000 / 30);
	start_color(); 
	cbreak(); 
	noecho(); 
	keypad(stdscr, TRUE); 

	int screen_y, screen_x; 
	getmaxyx(stdscr, screen_y, screen_x); 

	int world_y = screen_y * 2; 
	int world_x = screen_x * 2;  

	int playY = screen_y / 2; 
	int playX = screen_x / 2; 

	char playerIcon = 'H'; 

	init_pair(4, COLOR_WHITE, 0);

	srand(time(NULL)); 

	// Screen error 
	if (initscr() == NULL) {
		printw("Screen initialization failure."); 
	} 

	init_color(COLOR_RED, 145 * 1000 / 255, 129 * 1000 / 255, 81 * 1000 / 255);

	init_pair(1, COLOR_WHITE, COLOR_BLACK); 
	init_pair(2, COLOR_RED, COLOR_YELLOW); 
	init_pair(3, COLOR_CYAN, COLOR_BLUE);

	// NO SUCH THING AS SELF-DOCUMENTING CODE! 

	// Measurements of sand  
	int heightSand = 50;
	int widthSand = 35; 

	// Measurements of the road  
	int heightRoad = 25; 
	int widthRoad= 25; 

	// Measurements of the waterfront 
	int heightWater = 50; 
	int widthWater = 40; 

	// Measurements of the house
	int heightHouse = 20;
	int widthHouse = 20; 

	int scrHeight = getmaxy(stdscr); 

	// Initialize the objects to the window 
	// Do not make y-adjustments, generally
	WINDOW * sand = newwin(heightSand, widthSand, 0 , scrHeight);
	WINDOW * road = newwin(heightRoad, widthRoad, scrHeight, 0 ); 
	WINDOW * water  = newwin(heightWater, widthWater, 0, 0 ); 
	WINDOW * house = newwin(heightHouse, widthHouse, 5, 75); 
	// Makes it so these things appear with color and text 
	for (int i = 0; i < heightRoad; i++) {
		mvwhline(road, i, 0, '#', widthRoad); 
	}

	for (int i = 0; i < heightSand; i++) {
		mvwhline(sand, i, 0, '.', widthSand); 
	}

	for (int i = 0; i < heightWater; i++) {
		mvwhline(water, i, 0, '~', widthWater); 
	}

	for (int i = 0; i < heightHouse; i++) {
		mvwhline(house, i, 0, '-', widthHouse); 
	} 

	// Randomly generated sand texture 
	for (int i = 0; i < heightSand; i++) {
		for (int j = 0; j < widthSand; j++) {
			int rand_thing = rand() % 100; 

			char texture; 
			if (rand_thing < 5) {
				texture =  '/'; 
			} 

			else if (rand_thing < 10) {
				texture = '/';
			}

			else if (rand_thing < 15) {
				texture = '`'; 
			}

			else {
				texture = ' '; 
			}

			mvwaddch(sand, i, j, texture);
		}    
	} 

	for (int i = 0; i < heightWater; i++) {
		for (int j = 0; j < widthWater; j++) {
			int rand_thing = rand() % 100; 

			char textureWater; 
			if (rand_thing < 5) {
				textureWater =  '`'; 
			} 

			else if (rand_thing < 10) {
				textureWater = '.';
			}

			else{
				textureWater = '~'; 
			} 
			mvwaddch(water, i, j, textureWater);
		} 
	}


	for (int i = 0; i < heightRoad; i++) {
		for (int j = 0; j < widthRoad; j++) {
			int rand_thing = rand() % 100; 

			char textureRoad; 
			if (rand_thing < 5) {
				textureRoad =  '#'; 
			} 

			else if (rand_thing < 10) {
				textureRoad = '*';
			}

			else{
				textureRoad = ';'; 
			} 
			mvwaddch(road, i, j, textureRoad);
		} 
	}

	// Doesn't work without all these annoying things 

	bool on = true; 
	while(on) {

		int prevY = playY; 
		int prevX = playX; 

		int in = getch(); 

		if (in == KEY_UP) {
			playY = max(0, playY - 1); 
		}

		else if (in == KEY_DOWN) {
			playY = min(screen_y - 1, playY + 1);
		} 

		else if (in == KEY_LEFT) {
			playX = max(0, playX - 1);
		} 

		else if (in == KEY_RIGHT) {
			playX = min(screen_x - 1, playX + 1);
		} 

		else if (in == 'f') {
			on = false; 
		}

		int start_y = max(0, playY - screen_y / 2); 	
		int start_x = max(0, playX - screen_x / 2); 
		start_y = min(start_y, world_y - screen_y); 
		start_y = min(start_x, world_x - screen_y); 

		mvwprintw(house, 10, 2, "McAfee Residence"); 

		wbkgd(sand, COLOR_PAIR(2));
		wbkgd(road, COLOR_PAIR(1));
		wbkgd(water, COLOR_PAIR(3));
		wbkgd(house, COLOR_PAIR(4));

		wrefresh(sand);
		wrefresh(road);
		wrefresh(water);  
		wrefresh(house); 

		move(prevY, prevX); 
		addch(' '); 

		move(playY, playX); 
		addch(playerIcon | COLOR_PAIR(4));

		refresh(); 
	} 

	// Doesn't work without all these annoying things 
	getch(); 
	getch(); 
	getch(); 
	getch(); 

	endwin(); 

	return 0;
}
