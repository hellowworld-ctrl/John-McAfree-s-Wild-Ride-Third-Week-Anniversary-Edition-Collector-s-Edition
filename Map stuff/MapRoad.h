#pragma once

#include <curses.h>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>
#include <Color.h>

using namespace std;


class MapRoad {

	vector<vector<char>> map;
	default_random_engine gen;
public:
	static const char MCAFREE = '@';
	static const char VIRUS = 'V';
	static const char WALL = '#';
	static const char GRASS = '`';
	static const char CAR = '8';
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
					if (d100(gen) <= 2) {
						map.at(i).at(j) = VIRUS; 
					}
					else if (d100(gen) <= 1) {
						map.at(i).at(j) = CHEST; 
					}
		else if (d100(gen) <= 3) {
						map.at(i).at(j) = CAR;
					}
					/*
					else if (d100(gen) <= 20) { //WHEN TREE, HIGH CHANCE ANOTHER TREE NEXT TO IT
						if (map.at(i-1).at(j) == TREE or map.at(i+1).at(j) == TREE or map.at(i).at(j-1) == TREE or map.at(i).at(j+1) == TREE) {
							map.at(i).at(j) = TREE;
						}
					}
					else if (d100(gen) <= 20) { //WHEN WALL, HIGH CHANCE TREE NEXT TO IT
						if (map.at(i-1).at(j) == WALL or map.at(i+1).at(j) == WALL) {
							map.at(i).at(j) = TREE;
						}
					}
					*/
					else {
						map.at(i).at(j) = OPEN;
					}
				}
			}
		}

		for (size_t i = 0; i < 100; i++) { //COL
			for (size_t k = 0; k < 20; k++) { //ROWS
				map.at(i).at(k) = GRASS;
			}
		}
		for (size_t i = 0; i < 100; i++) { //COL
			for (size_t k = 80; k < 100; k++) { //ROWS
				map.at(i).at(k) = GRASS;
			}
		}
		for (size_t i = 0; i < 15; i++) { //COL
			for (size_t k = 51; k < 53; k++) { //ROWS
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 28; i < 36; i++) { //COL
			for (size_t k = 51; k < 53; k++) { //ROWS
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 51; i < 73; i++) { //COL
			for (size_t k = 51; k < 53; k++) { //ROWS
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 84; i < 91; i++) { //COL
			for (size_t k = 51; k < 53; k++) { //ROWS
				map.at(i).at(k) = WALL;
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
		mvwprintw(puzzwin, 1, 1, "Which politcal party did [John McAfee] try to become the [presidential candidate] for?");
		mvwprintw(puzzwin, 2, 2, "Press [enter] to select an answer. :)");
		wrefresh(puzzwin);

		// makes it so we can use arrow keys
		keypad(puzzwin, true);

		string choices[4] = { "The Libertarian Party!", "The Republican Party", "The Communist Party?", "*bong rip* The Green Party, man..." };
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

		if (highlight == 0) {
			attron(COLOR_PAIR(1));
			move(22, 75);
			printw("CORRECT! YOU WIN A PRIZE!");
			return true;
			attroff(COLOR_PAIR(1));
		}
		else {
			attron(COLOR_PAIR(2));
			move(22, 75);
			printw("INCORRECT! REFRESH ON YOUR (John McAfee) KNOWLEDGE!");
			return false;
			attroff(COLOR_PAIR(2));
		}

		getch();
		clear();
		refresh();
	}
	void lore() {
		//int height = 0, width = 0;
		int x = 0, y = 0, yMax = 0, xMax = 0;
		// moves the cursor
		move(0, 0);
		getyx(stdscr, y, x);
		getmaxyx(stdscr, yMax, xMax);

		WINDOW* puzzwin = newwin(yMax, xMax, y, x);

		box(puzzwin, 0, 0);
		refresh();
		wborder(puzzwin, '{', '}', '~', '~', '%', '%', '%', '%');

		mvwprintw(puzzwin, 2, 3, "The streets are nearly empty, littered only with the brave souls who've chosen to disobey your authority.");
		mvwprintw(puzzwin, 4, 4, "Colonial houses arrange themselves parallel to each other, and telephone wires distort the sunny sky.");
		mvwprintw(puzzwin, 6, 5, "Your prisoners now oppoonents stand outside their homes with weapons across their arms or on their shoulders.");
		mvwprintw(puzzwin, 8, 6, "Snipers lurk in the distance. Things already seem to be bad. ");

		wrefresh(puzzwin);


		getch();
		clear();
		refresh();
	}

	void screen(int x, int y) {
		int start_x = x - DISPLAY/2;
		int end_x = x + DISPLAY/2;
		int start_y = y - DISPLAY/2;
		int end_y = y + DISPLAY/2;

		init_pair(1,COLOR_BLACK,COLOR_BLACK);
		init_pair(2,COLOR_WHITE,COLOR_RED);
		init_pair(3,COLOR_BLUE,COLOR_WHITE);
		init_pair(4,COLOR_MAGENTA,COLOR_YELLOW);
		init_pair(5,COLOR_BLACK,COLOR_BLACK);
		init_pair(6,COLOR_MAGENTA,COLOR_WHITE);
		init_pair(7,COLOR_WHITE,COLOR_GREEN);
		init_pair(8,COLOR_WHITE,COLOR_BLACK);

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
					else if (map.at(i).at(k) == GRASS) color = 7;
					else if (map.at(i).at(k) == MCAFREE) color = 1;
					else if (map.at(i).at(k) == CHEST) color = 4;
					else if (map.at(i).at(k) == CAR) color = 3;
					else if (map.at(i).at(k) == VIRUS) color = 2;
					else if (map.at(i).at(k) == OPEN) color = 5;

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
						if (map.at(i-1).at(j) == WALL or map.at(i-1).at(j) == GRASS) {
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
						if (map.at(i).at(j-1) == WALL or map.at(i).at(j-1) == GRASS) {
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
	MapRoad() {
		generateMap();
	}
	~MapRoad() = default;


};
