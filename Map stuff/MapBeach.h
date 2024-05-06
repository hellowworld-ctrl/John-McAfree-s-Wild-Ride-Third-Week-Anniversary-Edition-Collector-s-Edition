#pragma once

#include <curses.h>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>
#include <Color.h>

using namespace std;


class MapBeach {

	default_random_engine gen;
public:
	vector<vector<char>> map;
	static const char MCAFREE = '@';
	static const char VIRUS = 'V';
	static const char WALL = '#';
	static const char WATER = '~';
	static const char BRANCH = 'B';
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
						map.at(i).at(j) = BRANCH;
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
				map.at(i).at(k) = WATER;
			}
		}
		for (size_t i = 95; i < 100; i++) { //COL
			for (size_t k = 0; k < 100; k++) { //ROWS
				map.at(i).at(k) = WATER;
			}
		}

		for (size_t i = 35; i < 50; i++) { //COL
			for (size_t k = 40; k < 62; k++) { //ROWS
				map.at(i).at(k) = HOUSE;
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
		mvwprintw(puzzwin, 1, 1, "Which company bought the [anti-virus software] that its creator, [John McAfee], called 'bloatware'");
		mvwprintw(puzzwin, 2, 2, "Press [enter] to select an answer. :)");
		wrefresh(puzzwin);

		// makes it so we can use arrow keys
		keypad(puzzwin, true);

		string choices[4] = { "Apple!", "McAfee Associates", "Intel.", "Whats an anti-virus?" };
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

		if (highlight == 2) {
			attron(COLOR_PAIR(1));
			move(22, 75);
			printw("CORRECT! YOU WIN A PRIZE!");
			getch();
			return true;
			attroff(COLOR_PAIR(1));
		}
		else {
			attron(COLOR_PAIR(2));
			move(22, 75);
			printw("INCORRECT! REFRESH ON YOUR (John McAfee) KNOWLEDGE!");
			getch();
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

		mvwprintw(puzzwin, 2, 2, "*Upon leaving the house from the back*");

		mvwprintw(puzzwin, 3, 2, "You finally leave.Take a look behind and see what you're gonna miss. ");
		mvwprintw(puzzwin, 4, 2, "Your heart flutters a bit, and your chest tightens, like an anvil of sorrow compressing your solar plexus, getting heavier with every heave of your upper body. ");
		mvwprintw(puzzwin, 5, 2, "A tear falls from one eye. You can't remember the last time you've done this. The saltiness of the tear upon your lip, crawling down to your tongue, is a radically foreign taste.");
		mvwprintw(puzzwin, 6, 2, "Recognizing that your masculinity can't withstand the newness of longing, you visibly shake and shrug your whole body, expecting the emotion to soar off of you and fall between the paving stones.");
		mvwprintw(puzzwin, 7, 2, "A whole cartography of pain you fail to confront maps little territories of guilt in your mind.This will never dissappear.");

		mvwprintw(puzzwin, 9, 2, "'I'm gonna have to thug this one out, guys.' John says.");

		mvwprintw(puzzwin, 11, 2, "'What?' the rest of the group asks in near - unison.");

		mvwprintw(puzzwin, 13, 2, "'Hmm, nothing. Let's move on.' John says amid a sniff. ");

		mvwprintw(puzzwin, 15, 2, "* the following dialogue is triggered if the group decides to not leave immediately, and visit the beach behind John's house.* ");

		mvwprintw(puzzwin, 17, 2, "Beyond the poolside and obsessively groomed plant assortments in John's backyard is a small beach. It nicely delimits the borders of his property, something he contemplates in casual libertarian essence.");
		mvwprintw(puzzwin, 18, 2, "It reminds him of the non-aggression principle, a sort of ethical axiom that declares property as divine permission to do anything with said property minus aggressive acts.");
		mvwprintw(puzzwin, 19, 2, "That, in turn, reminded him of Ayn Rand - someone so systematically averse to anything good as to probably not enjoy a beach as quaint yet picturesque as McAfee's abode.");

		mvwprintw(puzzwin, 21, 2, "'I don't visit this beach nearly as often as I should.' John comments, the Belizean heat glazing his elderly complexion. ");

		mvwprintw(puzzwin, 23, 2, "'We're not gonna be visiting this place again, you dumbass.' the little militant says. ");

		mvwprintw(puzzwin, 25, 2, "'What do you mean? I'm gonna be coming back here.' ");

		mvwprintw(puzzwin, 27, 2, "'John, we're literally heading to the airport because you're being extradited to the U.S. This is only half the battle. If we get to Miami, there's not gonna be a safe haven.' ");

		mvwprintw(puzzwin, 29, 2, "'I don't think you know how good I am at this.' John says. A solemn finality shows in his words. You can practically hear the pride come up to his larynx and vomit profusely on everyone else. ");

		mvwprintw(puzzwin, 31, 2, "* upon going along the beach *");

		mvwprintw(puzzwin, 33, 2, "You walk along the beach with your peers.You wish you could see your lover erotically douse herself in the tides");
		mvwprintw(puzzwin, 34, 2, "Suddenly, memories of that exact thing flood your immediate vision, you can even feel the presence of your bodyguards standing like obelisks behind you - except their real presence feels much different.");
		mvwprintw(puzzwin, 35, 2, "An inane frustration comes over you, as you realize you're feeling new emotions as a man in his seventies.  ");

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
		init_pair(3,COLOR_GREEN,COLOR_YELLOW);
		init_pair(4,COLOR_MAGENTA,COLOR_YELLOW);
		init_pair(5,COLOR_YELLOW,COLOR_YELLOW);
		init_pair(6,COLOR_MAGENTA,COLOR_WHITE);
		init_pair(7,COLOR_CYAN,COLOR_BLUE);
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
					else if (map.at(i).at(k) == BRANCH) color = 3;
					else if (map.at(i).at(k) == HOUSE) color = 8;
					else if (map.at(i).at(k) == VIRUS) color = 1;
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
						if (map.at(i-1).at(j) == WALL or map.at(i-1).at(j) == WATER or map.at(i-1).at(j) == HOUSE) {
							map.at(i).at(j) = VIRUS; 
						} else {
							map.at(i-1).at(j) = VIRUS; 
							map.at(i).at(j) = OPEN;
						}
					}
					else if (randomNum == 2) {
						if (map.at(i+1).at(j) == WALL  or map.at(i+1).at(j) == WATER or map.at(i+1).at(j) == HOUSE) {
							map.at(i).at(j) = VIRUS;
						} else {
							map.at(i+1).at(j) = VIRUS; //BROKEN!
							map.at(i).at(j) = OPEN; 
							break;
					}
					}
					else if (randomNum == 3) {
						if (map.at(i).at(j-1) == WALL or map.at(i).at(j-1) == WATER or map.at(i).at(j-1) == HOUSE) {
							map.at(i).at(j) = VIRUS; 
						} else {
							map.at(i).at(j-1) = VIRUS; 
							map.at(i).at(j) = OPEN;
						}
					}
					else if (randomNum == 4) {
						if (map.at(i).at(j+1) == WALL  or map.at(i).at(j+1) == WATER or map.at(i).at(j+1) == HOUSE) {
							map.at(i).at(j) = VIRUS;
						} else {
						map.at(i).at(j+1) = VIRUS;//BROKEN! 
						map.at(i).at(j) = OPEN; 
							break;
					}
					}
				}
			}
		}
	}

	MapBeach() {
		generateMap();
	}
	~MapBeach() = default;


};
