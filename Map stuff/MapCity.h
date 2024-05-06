#pragma once

#include <curses.h>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>
#include <Color.h>

using namespace std;


class MapCity {

	default_random_engine gen;
public:
	vector<vector<char>> map;
	static const char MCAFREE = '@';
	static const char VIRUS = 'V';
	static const char WALL = '#';
	static const char WATER = '~';
	static const char TREE = 't';
	static const char HOUSE = 'H';
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
					else if (d100(gen) <= 1) {
						map.at(i).at(j) = WALL; 
					}
					else if (d100(gen) <= 1) {
						map.at(i).at(j) = TREE; 
					}
		else if (d100(gen) <= 7) {
						map.at(i).at(j) = HOUSE;
					}
					else if (d100(gen) <= 20) { //WHEN TREE, HIGH CHANCE ANOTHER TREE NEXT TO IT
						if (map.at(i-1).at(j) == HOUSE or map.at(i+1).at(j) == HOUSE or map.at(i).at(j-1) == HOUSE or map.at(i).at(j+1) == HOUSE ) {
							map.at(i).at(j) = HOUSE;
						}
					}
					else if (d100(gen) <= 20) { //WHEN WALL, HIGH CHANCE TREE NEXT TO IT
						if (map.at(i-1).at(j) == HOUSE or map.at(i+1).at(j) == HOUSE) {
							map.at(i).at(j) = WALL;
						}
					}
					else if (d100(gen) <= 20) { //WHEN WALL, HIGH CHANCE TREE NEXT TO IT
						if (map.at(i-1).at(j) == HOUSE or map.at(i+1).at(j) == HOUSE) {
							map.at(i).at(j) = TREE;
						}
					}
					else {
						map.at(i).at(j) = OPEN;
					}
				}
			}
		}
		/*
		for (size_t i = 35; i < 50; i++) { //COL
			for (size_t k = 40; k < 62; k++) { //ROWS
				map.at(i).at(k) = HOUSE;
			}
		}
		*/

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
		mvwprintw(puzzwin, 1, 1, "What was [John McAfee] wanted for in [Belieze]? And what was [he] charged with on [his] inevitable arrest?");
		mvwprintw(puzzwin, 2, 2, "Press [enter] to select an answer. :)");
		wrefresh(puzzwin);

		// makes it so we can use arrow keys
		keypad(puzzwin, true);

		string choices[4] = { "Wait what? They never caught me!", "Tax Evasion and First Degree Murder", "Possesion of cocain and distribution of cocain... *sniff*", "Suspicion of Murder and Tax Evasion." };
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

		if (highlight == 3) {
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

		mvwprintw(puzzwin, 2, 2, "After sweating off the trigger happy street - goers, you find your group in a more bourgeois, residential district near the beach.");
		mvwprintw(puzzwin, 3, 2, "Each house exudes an almost unreachable luxury to them, with their elaborate gated entrances and driveways that fade into a horizon of angular windows and walls.");
		mvwprintw(puzzwin, 4, 2, "You rub your eyes a bit.As the dots in your retinas dissolve, you see abstract blobs of black and purple along the perimeter of a couple properties.");
		mvwprintw(puzzwin, 5, 2, "The vaguely yellow blurbs on their clothing appear bright as day : F.B.I.Every one of them is decked out with an armored combat jacket smattered with holsters, carrying all manner of hostile devices.");
		mvwprintw(puzzwin, 6, 2, "Things are now worse.");

		mvwprintw(puzzwin, 8, 2, "The airport looms mockingly in the distance.Your group collectively feels a cold breeze sift through their loose clothing, and graze their humid skin.");
		mvwprintw(puzzwin, 9, 2, "The ocean is right next to you.A dozen wooden docks stretch out into the Caribbean Sea, each one sheltered by a thatched - roofed gazebo.");
		mvwprintw(puzzwin, 10, 2, "Along the docks, an alarming arrangment of people stand adorned in camouflage and high - caliber rifles.");
		mvwprintw(puzzwin, 11, 2, "They maneuver themselves with artifical precision, like a protocol for impending conquest.");
		mvwprintw(puzzwin, 12, 2, "Like a neural network, they identify you in a discrete sequence - instructions unfolding for your group's termination. ");
		mvwprintw(puzzwin, 13, 2, "The odds are completely against you.");
		mvwprintw(puzzwin, 14, 2, "The streets are nearly empty, littered only with the brave souls who've chosen to disobey your authority.");

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

		init_pair(1,COLOR_BLACK,COLOR_RED);
		init_pair(2,COLOR_BLUE,COLOR_WHITE);
		init_pair(3,COLOR_BLACK,COLOR_GREEN);
		init_pair(4,COLOR_MAGENTA,COLOR_YELLOW);
		init_pair(5,COLOR_WHITE,COLOR_WHITE);
		init_pair(6,COLOR_MAGENTA,COLOR_WHITE);
		init_pair(7,COLOR_WHITE,COLOR_WHITE);
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
					else if (map.at(i).at(k) == WATER) color = 7;
					else if (map.at(i).at(k) == MCAFREE) color = 5;
					else if (map.at(i).at(k) == CHEST) color = 4;
					else if (map.at(i).at(k) == TREE) color = 3;
					else if (map.at(i).at(k) == HOUSE) color = 8;
					else if (map.at(i).at(k) == VIRUS) color = 1;
					else if (map.at(i).at(k) == OPEN) color = 7;

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
						if (map.at(i-1).at(j) == WALL) {
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
						if (map.at(i).at(j-1) == WALL) {
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


	MapCity() {
		generateMap();
	}
	~MapCity() = default;


};
