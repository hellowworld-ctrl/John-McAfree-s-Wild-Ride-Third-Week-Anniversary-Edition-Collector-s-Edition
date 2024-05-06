#include <cstdlib>
#include "/public/read.h"
#include <curses.h>
#include "Map.h"
#include "MapBeach.h"
#include "MapRoad.h"
#include "MapCity.h"
#include "MapAirport.h"
#include <stdlib.h>
#include <ncurses.h>
#include <random>
#include <menu.h>
#include <signal.h>
#include <iostream>
#include <cctype>

using namespace std;


void Menu() {
	static MapHouse map;
	WINDOW *menuwin = newwin(20, 60, 20, 100);
	box(menuwin, 0, 0);
	keypad(menuwin, TRUE);
	noecho();

	vector<string> escMenu = {"Continue\n", "Inventory\n", "Control\n"};
	vector<string> inventory = {"Weapons", "Armour", "Other", "QUIT"};
	int choice = -1;
	int highlight = 0;

	wmove(menuwin, 1, 1);
	clear();
	wrefresh(menuwin);
	while (true) {
		for (int i = 0; i < escMenu.size(); i++) {
			if (i == highlight) wattron(menuwin, A_REVERSE);
			wmove(menuwin, i + 1, 1);
			waddstr(menuwin, escMenu.at(i).c_str());
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch (choice) {
			case 'w':
				highlight--;
				if (highlight == -1)
					highlight = 0;
			break;
			case 's':
				highlight++;
				if (highlight == 3)
					highlight = 2;
				break;
			default:
			break;
		}
		wrefresh(menuwin);
		if (choice == '\r')
		break;

	}
	if (highlight == 0) {
		endwin();
	clear();
		int x = 0, y = 0;
		getyx(stdscr, y, x);
		map.screen(x, y);
		return;
	} else if (highlight == 1) {
		//TODO Display inventory using a menu thingie 👌
		highlight = 0;
	clear();
		for (int i = 0; i < inventory.size(); i++) {
			if (i == highlight) wattron(menuwin, A_REVERSE);
			wmove(menuwin, i + 1, 1);
			waddstr(menuwin, inventory.at(i).c_str());
			wattroff(menuwin, A_REVERSE);
		}
		wrefresh(menuwin);
		int choice = -1;
		while (true) {
			for (int i = 0; i < inventory.size(); i++) {
				if (i == highlight) wattron(menuwin, A_REVERSE);
				wmove(menuwin, i + 1, 1);
				waddstr(menuwin, inventory.at(i).c_str());
				wattroff(menuwin, A_REVERSE);
			}
			wrefresh(menuwin);
			choice = getch();
			switch (choice) {
				case 'w':
					highlight--;
					if (highlight < 0)
					highlight = 0;
				break;
				case 's':
					highlight++;
					if (highlight >= inventory.size())
						highlight = inventory.size() - 1;
				break;
				default:
				break;
			}
		}
		if (choice == '\r') {
			//TODO: Implement an equip system.
			endwin();
			clear();
			int x = 0, y = 0;
			getyx(stdscr, y, x);
			map.screen(x, y);
			wrefresh(stdscr);
			return;
		}
	} else if (highlight == 2) {
		printw("'q' - quit");
		mvprintw(1, 0, "'w' - right");
		mvprintw(2, 0, "'a' - left");
		mvprintw(3, 0, "'s' - down");
		mvprintw(4, 0, "'d' - right");
		mvprintw(5, 0, "'enter' - select");
	}
	wrefresh(menuwin);
}


template<typename MapType>
void Move(const int &ch, MapType&map, WINDOW *win) {
	int x = 0, y = 0;
	getyx(win, y, x);

	int newX = x;
	int newY = y;

	int randomNum = ((rand() % 4) + 1);

	if (randomNum == 1) {
		
	}

	if (ch == 'W' || ch == KEY_UP) newY -= 1;
	else if (ch == 'A' || ch == KEY_LEFT) newX -= 1;
	else if (ch == 'S' || ch == KEY_DOWN) newY += 1;
	else if (ch == 'D' || ch == KEY_RIGHT) newX += 1;

	if (map.isEnemy(newX, newY) == true) {
	} else if (map.isChest(newX, newY) == true) {
		mvprintw(0, 80, "OPENED CHEST BUT DOES NOTHING YET");
		refresh();
		getch();
		clear();
		refresh();
	} else if (map.getPlayerLoc(newX, newY)) {
		map.screen(newX, newY);
		wmove(win, newY, newX);
		wrefresh(win);
	} else {
		wmove(win, y, x);
		wrefresh(win);
	}
}


int main() {
	int playerMove = 0;
	int FPS = 60;
	initscr();
	scrollok(stdscr, TRUE);
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();
	/*
	system("figlet FREEDOM FIGHTERS - John McAfree");
	string startButton = read("Enter \'p\' to go into the world!\n");
	if (startButton == "p") {
		(void) initscr();
		(void) scrollok(stdscr, TRUE);
		keypad(stdscr, TRUE);
		(void) nonl();
		(void) cbreak();
		(void) noecho();
	*/
	int yMax = 24, xMax = 80;
	// moves the cursor
	
	getmaxyx(stdscr, yMax, xMax);
	WINDOW * mainwin = newwin(yMax/2, xMax/2, 1, 1);

	start_color();
	if (has_colors()) {
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		init_pair(5, COLOR_CYAN, COLOR_BLACK);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_WHITE, COLOR_BLACK);
	}

	box(mainwin, 1, 1);
	refresh();
	wattron(mainwin, COLOR_PAIR(5));
	wborder(mainwin, '{', '}', '~', '~', '*', '*', '*', '*');
	wattroff(mainwin, COLOR_PAIR(5));
	wattron(mainwin, COLOR_PAIR(6));
	mvwprintw(mainwin, 2, 6, "FREEDOM FIGHTERS - John McAfee");
	mvwprintw(mainwin, 2, 60, "F1 key for menu in game");
	wattroff(mainwin, COLOR_PAIR(6));

	// makes it so we can use arrow keys
	keypad(mainwin, true);

	int choice;
	int highlight = 0;
	string Choices[5] = {"Level 1 - House", "Level 2 - Beach", "Level 3 - Road", "Level 4 - City", "Level 5 - Airport"};

	while(true) {
		for (int i = 0; i < 5; i++) {
			wattron(mainwin, COLOR_PAIR(5));
			mvwprintw(mainwin, i+4, 4, Choices[i].c_str());
			wattroff(mainwin, COLOR_PAIR(5));
		}
		for (int i = 0; i < 5; i++) {
			if (i == highlight) {
				wattron(mainwin, A_REVERSE | COLOR_PAIR(6));
				mvwprintw(mainwin, i+4, 4, Choices[i].c_str());
				wattroff(mainwin, A_REVERSE | COLOR_PAIR(6));
			}
		}
		choice = wgetch(mainwin);

		switch(choice) {
			case 'w' :
				highlight--;
				if(highlight == -1)
				highlight = 0;
			break;
			case 's' :
				highlight++;
				if(highlight == 5)
				highlight = 4;
			break;
			default:
			break;
		}
		if(choice == '\r')
		break;
	}
	wrefresh(mainwin);
	clear();
	refresh();
	WINDOW * playwin = newwin(100, 100, 50, 50);
	wmove(playwin, 50, 50);

	if (highlight == 0) {
		MapHouse map;
	map.screen(50, 50);
	while ((playerMove = wgetch(stdscr)) != 'q') {

		cin >> playerMove;

		if (playerMove == KEY_F(1)) {
			Menu();
		} else if (playerMove == KEY_F(2)) {
			map.puzz();
		}

		else if (playerMove == ERR) usleep(1'000'000 / FPS);

			else {
			playerMove = toupper(playerMove);
			map.monsterMove();
			Move(playerMove, map, playwin);

		}
	}
	}
	else if (highlight == 1) {
		MapBeach map;
	map.screen(50, 50);
	while ((playerMove = wgetch(stdscr)) != 'q') {

		cin >> playerMove;

		if (playerMove == KEY_F(1)) {
			Menu();
		} else if (playerMove == KEY_F(2)) {
			map.puzz();
		}

		else if (playerMove == ERR) usleep(1'000'000 / FPS);

			else {
			playerMove = toupper(playerMove);
			Move(playerMove, map, playwin);

		}
	}
		}
	else if (highlight == 2) {
		MapRoad map;
	map.screen(50, 50);
	while ((playerMove = wgetch(stdscr)) != 'q') {

		cin >> playerMove;

		if (playerMove == KEY_F(1)) {
			Menu();
		} else if (playerMove == KEY_F(2)) {
			map.puzz();
		}

		else if (playerMove == ERR) usleep(1'000'000 / FPS);

			else {
			playerMove = toupper(playerMove);
			Move(playerMove, map, playwin);

		}
	}
	}
	else if (highlight == 3) {
		MapCity map;
	map.screen(50, 50);
	while ((playerMove = wgetch(stdscr)) != 'q') {

		cin >> playerMove;

		if (playerMove == KEY_F(1)) {
			Menu();
		} else if (playerMove == KEY_F(2)) {
			map.puzz();
		}

		else if (playerMove == ERR) usleep(1'000'000 / FPS);

			else {
			playerMove = toupper(playerMove);
			Move(playerMove, map, playwin);

		}
	}
	}
	else if (highlight == 4) {
		MapAirport map;
	map.screen(50, 50);
	while ((playerMove = wgetch(stdscr)) != 'q') {

		cin >> playerMove;

		if (playerMove == KEY_F(1)) {
			Menu();
		} else if (playerMove == KEY_F(2)) {
			map.puzz();
		}

		else if (playerMove == ERR) usleep(1'000'000 / FPS);

			else {
			playerMove = toupper(playerMove);
			Move(playerMove, map, playwin);

		}
	}
	}

	/*
	map.screen(50, 50);
	while ((playerMove = wgetch(stdscr)) != 'q') {

		cin >> playerMove;

		if (playerMove == KEY_F(1)) {
			Menu();
		} else if (playerMove == KEY_F(2)) {
			puzz();
		}

		else if (playerMove == ERR) usleep(1'000'000 / FPS);

			else {
			playerMove = toupper(playerMove);
			Move(playerMove, map, playwin);

		}
	}
	*/
	
 //else usleep(500'00);

attroff(COLOR_PAIR(1));
clear();
refresh();
endwin();
}
