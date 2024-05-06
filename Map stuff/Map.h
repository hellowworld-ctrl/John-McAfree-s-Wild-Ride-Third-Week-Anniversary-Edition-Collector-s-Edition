#pragma once

#include <curses.h>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>
#include <Color.h>

using namespace std;


class MapHouse {

	vector<vector<char>> map;
	default_random_engine gen;
public:
	static const char MCAFREE = '@';
	static const char VIRUS = 'V';
	static const char WALL = '#';
	static const char TREE = 't';
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
		for (size_t i = 24; i < 25; i++) {//ROW
			for (size_t k = 0; k < 40; k++) {//COL
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 0; i < 20; i++) {//ROW
			for (size_t k = 39; k < 40; k++) {//COL
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 74; i < 75; i++) {//ROW
			for (size_t k = 60; k < 100; k++) {//COL
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 74; i < 94; i++) {//ROW
			for (size_t k = 59; k < 60; k++) {//COL
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 69; i < 70; i++) {//ROW
			for (size_t k = 0; k < 30; k++) {//COL
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 69; i < 80; i++) {//ROW
			for (size_t k = 29; k < 30; k++) {//COL
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 90; i < 100; i++) {//ROW
			for (size_t k = 29; k < 30; k++) {//COL
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 0; i < 30; i++) {//ROW
			for (size_t k = 70; k < 71; k++) {//COL
				map.at(i).at(k) = WALL;
			}
		}
		for (size_t i = 30; i < 31; i++) {//ROW
			for (size_t k = 80; k < 100; k++) {//COL
				map.at(i).at(k) = WALL;
			}
		}
		/* DEMO TO PLACE THINGS AT CERTAIN LOCATIONS
		for (size_t i = 1; i < 20; i++) {
			for (size_t k = 1; k < 20; k++) {
				map.at(i).at(k) = OPEN;
			}
		}
		*/
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
		mvwprintw(puzzwin, 1, 2, "He lies comfortably by the poolside. One hand strokes the chin of his lover, the other massages the cold steel of a Smith & Wesson revolver.");
		mvwprintw(puzzwin, 2, 2, "Belizean heat scorches his patchy blond hair and kisses the woefully tanned tribal tattoos on both of his shoulders.");
		mvwprintw(puzzwin, 3, 2, "A mind once preoccupied with malware prevention and proprietary software now faces the incessant jitters of death or, even worse, jail time. ");
		mvwprintw(puzzwin, 4, 2, "He is surrounded by a sort of impromptu paramilitary, whose faces speak of blind loyalty. ");
		mvwprintw(puzzwin, 5, 2, "John McAfee : a senior - aged mastermind in the art of evasion.He now assumes the role of virus, with fewer escapes on an ever dwindling horizon.");
		mvwprintw(puzzwin, 6, 2, "By this point, he has laid sovereignty on his small coastal abode in Ambergris Cave, enforcing curfews on the town’s helpless citizens");
		mvwprintw(puzzwin, 7, 2, "In true libertarian ethos, McAfee lies paranoid in a home devoid of a single tax document, contemplating a method of escape.Miami appears promising.");
		mvwprintw(puzzwin, 9, 2, "“The airport - sounds like the only way out of here” McAfee’s little militant says.");
		mvwprintw(puzzwin, 11, 2, "“We can try.The Fed has scoped the whole coast.More feds than a Lockeed Martin conference.” McAfee says, shaking through sips of scotch.");
		mvwprintw(puzzwin, 13, 2, "“I’m scared, Johnny.” mutters his underaged girlfriend.");
		mvwprintw(puzzwin, 15, 2, "“Why, darling ? ” John asks.");
		mvwprintw(puzzwin, 17, 2, "We've been here for months and they haven't even caught what we've been doing with the town. Everyone's a prisoner - I can only imagine what they'll bring out to fight us.");
		mvwprintw(puzzwin, 19, 2, "'She's got a point, John. I've been going up and down these streets for months maintaining the curfew. Chances are, some brave soul reported us to greater authorities.' inquires the taller militant.");
		mvwprintw(puzzwin, 21, 2, "I don't give a shit. There's not a single international contigency that can do anything about us. We're everywhere, we're decentralized, we're not even real - think crypto.");
		mvwprintw(puzzwin, 23, 2, "Does crypto have any intrinstic exchange value? Fuck no! I peddle it on my Twitter timeline because it's funny - it's just an append-only data structure.");
		mvwprintw(puzzwin, 25, 2, "'It's like walking around with a wallet that gets bigger or smaller depending on vibes.' John rants longingly.");
		mvwprintw(puzzwin, 27, 2, "'This is the second time you've said this this afternoon, sitting in that chair, drinking that cocktail.' the little militant says.");
		mvwprintw(puzzwin, 29, 2, "'And I'll do it again. My skin burns, I'm going inside.' John says staunchly.");
		mvwprintw(puzzwin, 30, 2, "* end of dialogue sequence *");
		mvwprintw(puzzwin, 32, 2, "John looks toward the oceanic horizon, a gorgeous view made meaningless by the numbing embrace of luxury.He adjusts his back, sprurring a loud rupture down his entire spine.");
		mvwprintw(puzzwin, 33, 2, "You would think his accomplicies would be concerned, but they all look at the sliding glass door.");
		mvwprintw(puzzwin, 34, 2, "The smell is beyond unique : a vague mixture of newly waxed walnut flooring, damp topsoil from the potted bromeliads, and the ammonnical stench of exotic animal urine.");
		mvwprintw(puzzwin, 35, 2, "Walk around, make yourself at home.");
		wrefresh(puzzwin);
		mvwprintw(puzzwin, 37, 2, "	* upon approaching the living room*");
		mvwprintw(puzzwin, 38, 2, "Pure Columbian cocaine runs in arrays along a mirror.Next to that is a clutter of USB drives, whose contents range from ancient bitcoin wallets to galleries of nudity.");
		mvwprintw(puzzwin, 39, 2, "Who or what is nude ? I can't really say. ");
		mvwprintw(puzzwin, 41, 2, "'All those antivirus royalties and you still couldn't hire a god damn cleaning lady' McAfee's girlfriend says begrudingly, her voice echoing upon the house's remarkable acoustics.");
		mvwprintw(puzzwin, 43, 2, "'I kinda' dig the look.' the tall militant remarks quietly.");
		mvwprintw(puzzwin, 44, 2, "* upon approaching the living room / hallway area *");
		mvwprintw(puzzwin, 45, 3, "	-A full bookshelf, titles seemingly arranged by how many grams of ketamine John injected while he organized it.John's eyes dart around the shelf, he sees: ");
		mvwprintw(puzzwin, 46, 3, "	- On Liberty - John Stuart Mill");
		mvwprintw(puzzwin, 47, 3, "	- All 18 Puranas Hindu scriptures");
		mvwprintw(puzzwin, 48, 3, "	- The Fountainhead - Ayn Rand");
		mvwprintw(puzzwin, 49, 3, "	- Structure and Interpretation of Computer Programs - Harold Abelson, Gerald Jay Sussman and Julie Sussman");
		mvwprintw(puzzwin, 50, 3, "	- Two Treatises on Government - John Locke");
		mvwprintw(puzzwin, 51, 3, "	- Learn Lines doing Lines : Riemannian Geometry for Today's Junkie - Erich von Hegel Marx Schopenhauer ");
		mvwprintw(puzzwin, 53, 2, "	'Shit, I've got a nice collection.' John mutters to himself.");
		mvwprintw(puzzwin, 55, 2, "* upon entering the main bedroom *");
		mvwprintw(puzzwin, 56, 2, "A California king sized mattress lies threadbare, stained with a hierarchical mush of unspeakable fluids - its memory foam nearly incapable of rising back to factory position.");
		mvwprintw(puzzwin, 57, 2, "End tables appear on each of the bed, endlessly branded by a thousand glass rings.One can imagine he'd be sipping mezcal when doing literally anything. ");
		mvwprintw(puzzwin, 58, 2, "His room window overlooks an aesthetic composite of tropical foliage: palm trees, heliconia, lush tapestries of green that arrange the sunlight into a beauty caressing the spirit of a man like McAfee.");
		mvwprintw(puzzwin, 59, 2, "Naturally, a mirror is on the ceiling. ");
		mvwprintw(puzzwin, 61, 2, "'God, I'm gonna miss this view.' John says.");
		mvwprintw(puzzwin, 63, 2, "'I know, babe. The helicondia is so beautiful.' his girlfriend responds.");
		mvwprintw(puzzwin, 65, 2, "'What? I'm talking about the mirrors.'");
		wrefresh(puzzwin);

		
		getch();
		clear();
		refresh();
	}

	void puzz() {
		//int height = 0, width = 0;
		int x = 30, y = 30, yMax = 50, xMax = 50;
		// moves the cursor
		move(y, x);
		getmaxyx(stdscr, yMax, xMax);

		WINDOW* puzzwin = newwin(18, xMax / 2, yMax / 2, 80);

		box(puzzwin, 0, 0);
		refresh();
		wborder(puzzwin, '|', '|', '-', '-', '/', '*', '+', '+');
		mvwprintw(puzzwin, 1, 1, "Which company did John McAfee found after leaving McAfee Associates(1994)?");
		mvwprintw(puzzwin, 2, 2, "Press [enter] to select an answer. :)");
		wrefresh(puzzwin);

		// makes it so we can use arrow keys
		keypad(puzzwin, true);

		string choices[4] = { "Bloatware.", "Tribal Voice?", "*sniffs* Got any coke?", "Get out of my way commie!" };
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
			printw("CORRECT! YOU WIN A PRIZE!");
			attroff(COLOR_PAIR(1));
		}
		else {
			attron(COLOR_PAIR(2));
			move(22, 75);
			printw("INCORRECT! REFRESH ON YOUR (John McAfee) KNOWLEDGE!");
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

		init_pair(1,COLOR_RED,COLOR_WHITE);
		init_pair(2,COLOR_BLUE,COLOR_WHITE);
		init_pair(3,COLOR_GREEN,COLOR_WHITE);
		init_pair(4,COLOR_YELLOW,COLOR_BLACK);
		init_pair(5,COLOR_WHITE,COLOR_WHITE);
		init_pair(6,COLOR_MAGENTA,COLOR_WHITE);
		init_pair(7,COLOR_RED,COLOR_RED);

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
					else if (map.at(i).at(k) == TREE) color = 3;
					else if (map.at(i).at(k) == MCAFREE) color = 5;
					else if (map.at(i).at(k) == CHEST) color = 4;
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
		randomNum = 2;
		int count = 0;

		for (size_t i = 0; i < SIZE; i++) {
			for (size_t j = 0; j < SIZE; j++) {
				if (i == 0 or j == 0 or i == SIZE-1 or j == SIZE-1)
					map.at(i).at(j) = WALL;
				else if (map.at(i).at(j) == VIRUS) {
					if (randomNum == 1) {
						map.at(i-1).at(j) = VIRUS; 
						map.at(i).at(j) = OPEN; 
					}
					else if (randomNum == 2) {
						if (count == 0) {
							map.at(i+1).at(j) = VIRUS; 
							map.at(i).at(j) = OPEN; 
							count++;
						}
					}
					else if (randomNum == 3) {
						map.at(i).at(j-1) = VIRUS; 
						map.at(i).at(j) = OPEN; 
					}
					else if (randomNum == 4) {
						map.at(i).at(j+1) = VIRUS; 
						map.at(i).at(j) = OPEN; 
					}
				}
			}
		}

	}


	MapHouse() {
		generateMap();
	}
	~MapHouse() = default;


};
