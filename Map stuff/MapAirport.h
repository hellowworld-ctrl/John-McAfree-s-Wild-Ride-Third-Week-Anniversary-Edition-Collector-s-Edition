#pragma once

#include <curses.h>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>
#include <Color.h>

using namespace std;


class MapAirport {

	vector<vector<char>> map;
	default_random_engine gen;
public:
	static const char MCAFREE = '@';
	static const char VIRUS = 'V';
	static const char WALL = '#';
	static const char PLANE = '*';
	static const char TREE = 't';
	static const char AIRPORT = 'A';
	static const char OPEN = ' ';
	static const char CHEST = 'c';
	static const size_t SIZE = 100;
	static const size_t DISPLAY = 60;

	void generateMap() {
		uniform_int_distribution<int> d100(1,1000);
		map.clear();
		map.resize(SIZE);
		for (auto &v : map) v.resize(SIZE,' ');
		for (size_t i = 0; i < SIZE; i++) {
			for (size_t j = 0; j < SIZE; j++) {
				if (i == 0 or j == 0 or i == SIZE-1 or j == SIZE-1)
					map.at(i).at(j) = WALL;
				else if (i == SIZE/2 and j == SIZE/2)
					map.at(i).at(j) = MCAFREE;
				else {
					if (d100(gen) <= 3) {
						map.at(i).at(j) = VIRUS; 
					}
					else if (d100(gen) <= 1) {
						map.at(i).at(j) = CHEST; 
					}
					else if (d100(gen) <= 3) {
						map.at(i).at(j) = TREE; 
					}
					else {
						map.at(i).at(j) = OPEN;
					}
				}
			}
		}
		for (size_t i = 10; i < 33; i++) { //COL
			for (size_t k = 13; k < 49; k++) { //ROWS
				map.at(i).at(k) = AIRPORT;
			}
		}
		for (size_t i = 0; i < 33; i++) { //COL
			for (size_t k = 60; k < 61; k++) { //ROWS
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 25; i < 39; i++) { //COL
			for (size_t k = 80; k < 85; k++) { //ROWS
				map.at(i).at(k) = PLANE;
			}
		}
		for (size_t i = 25; i < 26; i++) { //COL
			for (size_t k = 76; k < 89; k++) { //ROWS
				map.at(i).at(k) = PLANE;
			}
		}
		for (size_t i = 26; i < 40; i++) { //COL
			for (size_t k = 81; k < 84; k++) { //ROWS
				map.at(i).at(k) = PLANE;
			}
		}
		for (size_t i = 27; i < 41; i++) { //COL
			for (size_t k = 82; k < 83; k++) { //ROWS
				map.at(i).at(k) = PLANE;
			}
		}



		for (size_t i = 31; i < 32; i++) { //ROW
			for (size_t k = 70; k < 80; k++) { //COL
				map.at(i).at(k) = PLANE;
			}
		}
		for (size_t i = 31; i < 32; i++) { //ROW
			for (size_t k = 85; k < 95; k++) { //COL
				map.at(i).at(k) = PLANE;
			}
		}

	}

	bool puzz() {
		//int height = 0, width = 0;
		int x = 30, y = 30, yMax = 50, xMax = 50;
		// moves the cursor
		move(y, x);
		getmaxyx(stdscr, yMax, xMax);

		WINDOW* puzzwin = newwin(18, xMax / 2, yMax / 2, 80);

		box(puzzwin, 0, 0);
		refresh();
		wborder(puzzwin, '|', '|', '-', '-', '/', '*', '+', '+');
		mvwprintw(puzzwin, 1, 1, "If [John McAfee] was born in [Sept, 1945] and [commited suicide] in [June, 2021], how old was [he] when [he] died?");
		mvwprintw(puzzwin, 2, 2, "Press [enter] to select an answer. :)");
		wrefresh(puzzwin);

		// makes it so we can use arrow keys
		keypad(puzzwin, true);

		string choices[4] = { "I'm not dead WTF?", "75 years old", "69 years old. Nice.", "76 years old?" };
		int choice;
		int highlight = 0;

		while (true) {
			for (int i = 0; i < 4; i++) {
				mvwprintw(puzzwin, i + 3, 4, choices[i].c_str());
			}
			for (int i = 0; i < 4; i++) {
				if (i == highlight) {
					wattron(puzzwin, A_REVERSE);
					mvwprintw(puzzwin, i + 3, 4, choices[i].c_str());
					wattroff(puzzwin, A_REVERSE);
				}
			}
			choice = wgetch(puzzwin);

			switch (choice) {
			case 'w':
				highlight--;
				if (highlight == -1)
					highlight = 0;
				break;
			case 's':
				highlight++;
				if (highlight == 4)
					highlight = 3;
				break;
			default:
				break;
			}
			if (choice == '\r')
				break;
		}
		wrefresh(puzzwin);
		move(20, 75);
		printw("YOU CHOSE: %s", choices[highlight].c_str());
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLACK);

		if (highlight == 1) {
			attron(COLOR_PAIR(1));
			move(22, 75);
			printw("CORRECT! YOU WIN!");
			return true;
			attroff(COLOR_PAIR(1));
		}
		else {
			attron(COLOR_PAIR(2));
			move(22, 75);
			printw("INCORRECT! YOU SUCK!");
			return false;
			attroff(COLOR_PAIR(2));
		}

		getch();
		clear();
		refresh();
	}

	void screen(int x, int y) {
		int start_x = x - DISPLAY/2;
		int end_x = x + DISPLAY/2;
		int start_y = y - DISPLAY/2;
		int end_y = y + DISPLAY/2;

		init_pair(1,COLOR_BLACK,COLOR_RED);
		init_pair(2,COLOR_BLUE,COLOR_WHITE);
		init_pair(3,COLOR_BLACK,COLOR_GREEN);
		init_pair(4,COLOR_MAGENTA,COLOR_YELLOW);
		init_pair(5,COLOR_BLACK,COLOR_BLACK);
		init_pair(6,COLOR_MAGENTA,COLOR_WHITE);
		init_pair(7,COLOR_BLUE,COLOR_WHITE);
		init_pair(8,COLOR_BLACK,COLOR_WHITE);
		init_pair(9,COLOR_BLACK,COLOR_BLACK);

		if (start_x < 0) {
			end_x = end_x - start_x;
			start_x = 0;
		}
		if (end_x > SIZE-1) {
			start_x = start_x - (end_x - (SIZE-1));
			end_x = SIZE-1;
		}
		if (start_y < 0) {
			end_y = end_y - start_y;
			start_y = 0;
		}
		if (end_y > SIZE-1) {
			end_y = start_y - (end_y - (SIZE-1));
			end_y = SIZE-1;
		}

		for (size_t i = start_y; i <= end_y; i++) {
			for (size_t k = start_x; k <= end_x; k++) {
				if (i == y and k == x) {
					attron(A_UNDERLINE | A_BOLD);
					mvaddch(i-start_y,k-start_x, MCAFREE);
					attroff(A_UNDERLINE | A_BOLD);
				}
				else {
					int color = 1;
					if (map.at(i).at(k) == WALL) color = 6;
					else if (map.at(i).at(k) == PLANE) color = 7;
					else if (map.at(i).at(k) == MCAFREE) color = 5;
					else if (map.at(i).at(k) == CHEST) color = 4;
					else if (map.at(i).at(k) == TREE) color = 3;
					else if (map.at(i).at(k) == AIRPORT) color = 8;
					else if (map.at(i).at(k) == VIRUS) color = 1;
					else if (map.at(i).at(k) == OPEN) color = 9;

					attron(COLOR_PAIR(color));
					mvaddch(i-start_y,k-start_x, map.at(i).at(k));
					attroff(COLOR_PAIR(color));
				}
				wrefresh(stdscr);
			}
		}

	}
	bool getPlayerLoc(int x, int y) {
		return map.at(y).at(x) == OPEN;
	}
	bool isChest(int &x,int &y) {
		return map.at(y).at(x) == CHEST;
	}

	bool isEnemy(int &x,int &y) {
		return map.at(y).at(x) == VIRUS;
	}
	void monsterMove() {
		
		int randomNum = ((rand() % 4) + 1);

		for (size_t i = 0; i < SIZE; i++) {
			for (size_t j = 0; j < SIZE; j++) {
				if (i == 0 or j == 0 or i == SIZE-1 or j == SIZE-1)
					map.at(i).at(j) = WALL;
				else if (map.at(i).at(j) == VIRUS) {
					if (randomNum == 1) {
						if (map.at(i-1).at(j) == WALL or map.at(i-1).at(j) == PLANE or map.at(i-1).at(j) == AIRPORT) {
							map.at(i).at(j) = VIRUS; 
						} else {
							map.at(i-1).at(j) = VIRUS; 
							map.at(i).at(j) = OPEN;
						}
					}
					else if (randomNum == 2) {
						//map.at(i).at(j) = VIRUS; //BROKEN!
						//map.at(i).at(j) = OPEN; 
					}
					else if (randomNum == 3) {
						if (map.at(i).at(j-1) == WALL or map.at(i).at(j-1) == PLANE or map.at(i).at(j-1) == AIRPORT) {
							map.at(i).at(j) = VIRUS; 
						} else {
							map.at(i).at(j-1) = VIRUS; 
							map.at(i).at(j) = OPEN;
						}
					}
					else if (randomNum == 4) {
						//map.at(i).at(j) = VIRUS;//BROKEN! 
						//map.at(i).at(j) = OPEN; 
					}
				}
			}
		}
	}


	MapAirport() {
		generateMap();
	}
	~MapAirport() = default;


};
