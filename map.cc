#include <cstdlib>
#include "/public/read.h"
#include <curses.h>
#include "Map.h"
#include <stdlib.h>
#include <ncurses.h>
#include <random>
#include <menu.h>
#include <signal.h>
#include <iostream>
#include <cctype>

using namespace std;

Map map;

void Menode() {
	WINDOW *menuwin = newwin(20,60,20,100);
	box(menuwin,0,0);
	keypad(menuwin,TRUE);
	noecho();

	vector<string> escMenu = {"Continue\n", "Inventory\n", "QUIT\n", "INFO\n"};
	vector<string> inventory = {"Weapons","Armour","Other","QUIT"};
	int choice = -1;
	int highlight = 0;

	wmove(menuwin,1,1);
	clear();
	wrefresh(menuwin);
	while (true) {
		for (int i = 0; i < escMenu.size(); i++) {
			if (i == highlight) wattron(menuwin,A_REVERSE);
			wmove(menuwin,i+1,1);
			waddstr(menuwin,escMenu.at(i).c_str());
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch(choice) {
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
				defualt:
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
		getyx(stdscr,y,x);
		map.screen(x,y);
		return;
	}
	else if (highlight == 1) {
		//TODO Display inventory using a menu thingie 👌
		highlight = 0;
		clear();
		for (int i = 0; i < inventory.size(); i++) {
			if (i == highlight) wattron(menuwin,A_REVERSE);
			wmove(menuwin,i+1,1);
			waddstr(menuwin,inventory.at(i).c_str());
			wattroff(menuwin, A_REVERSE);
		}
		wrefresh(menuwin);
		int choice = -1;
		while (true) {
			for (int i = 0; i < inventory.size(); i++) {
				if (i == highlight) wattron(menuwin,A_REVERSE);
				wmove(menuwin,i+1,1);
				waddstr(menuwin,inventory.at(i).c_str());
				wattroff(menuwin, A_REVERSE);
			}
			wrefresh(menuwin);
			choice = getch();
			switch(choice) {
				case 'w':
					highlight--;
					if (highlight < 0)
					highlight = 0;
				break;
				case 's':
					highlight++;
					if (highlight >= inventory.size())
						highlight = inventory.size()-1;
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
			getyx(stdscr,y,x);
			map.screen(x,y);
			wrefresh(stdscr);
			return;
		}
	}
	else if (highlight == 2) {
		//Quit!
	clear();
		wrefresh(stdscr);
		exit(EXIT_SUCCESS);
	}
	else if (highlight == 3) {
		printw("INFO LATER");
	}
	wrefresh(menuwin);
}

void Move(const int &ch, Map&map, WINDOW *win) {
	int x = 0, y = 0;
	int xtwo = 0, ytwo = 0;
	getyx(win,y,x);
	//cout << x << "|" << y << endl;
	xtwo = x;
	ytwo = y;
	if (ch == 'W' or ch == KEY_UP) {
		if (map.getCharChar(x,y-1) == ' ') {
			/*mvaddch(y,x,' ');
			mvaddch(y-1,x,'*');
			wmove(stdscr,y-1,x);

			wrefresh(stdscr);*/
			map.screen(x,y-1);
			wmove(win,y-1,x);
			wrefresh(win);
		}
		else {
			wmove(win,y,x);
			wrefresh(win);
		}
	}
	if (ch == 'A' or ch == KEY_LEFT) {
		if (map.getCharChar(x-1,y) == ' ') {
			/*	mvaddch(y,x,' ');
			mvaddch(y,x-1,'*');
			wmove(stdscr,y,x-1);
			wrefresh(stdscr);*/
			map.screen(x-1,y);
			wmove(win,y,x-1);
			wrefresh(win);


		}
		else {
			wmove(win,y,x);
			wrefresh(win);
		}
	}
	if (ch == 'S' or ch == KEY_DOWN) {
		if (map.getCharChar(x,y+1) == ' ') {
			/*mvaddch(y,x,' ');
			mvaddch(y+1,x,'*');
			wmove(stdscr,y+1,x);
			wrefresh(stdscr);*/
			map.screen(x,y+1);
			wmove(win,y+1,x);
			wrefresh(win);
		}
		else {
			wmove(win,y,x);
			wrefresh(win);
		}
	}
	if (ch == 'D' or ch == KEY_RIGHT) {
		if (map.getCharChar(x+1,y) == ' ') {
			/*mvaddch(y,x,' ');
			mvaddch(y,x+1,'*');
			wmove(stdscr,y,x+1);
			wrefresh(stdscr);*/
			map.screen(x+1,y);
			wmove(win,y,x+1);
			wrefresh(win);
		}
		else {
			wmove(win,y,x);
			wrefresh(win);
		}
	}
	if (map.isEnemy(xtwo,ytwo) == true) {
		//		enemyFound(xtwo,ytwo);
		//		keypad(stdscr,TRUE);
		//		wrefresh(stdscr);
	}
	//	if (ch == KEY_NPAGE) {
	//	form_driver(defualt,REQ_NEXT_FIELD);
	//	}

}

void puzz() {
	//int height = 0, width = 0;
	int x = 30, y = 30, yMax = 50, xMax = 50;
	// moves the cursor
	move(y, x);
	getmaxyx(stdscr, yMax, xMax);

	WINDOW * puzzwin = newwin(18, xMax/2, yMax/2, 80);

	box(puzzwin, 0, 0);
	refresh();
	wborder(puzzwin, '|', '|', '-', '-', '/', '*', '+', '+');
	mvwprintw(puzzwin, 1, 1, "Which company did John McAfee found after leaving McAfee Associates(1994)?");
	wrefresh(puzzwin);

	// makes it so we can use arrow keys
	keypad(puzzwin, true);

	string choices[4] = {"Bloatware.", "Tribal Voice?", "*sniffs* Got any coke?", "Get out of my way commie!"};
	int choice;
	int highlight = 0;

	while(true) {
		for (int i = 0; i < 4; i++) {
				mvwprintw(puzzwin, i+3, 4, choices[i].c_str());
		}
		for (int i = 0; i < 4; i++) {
			if (i == highlight) {
				wattron(puzzwin, A_REVERSE);
				mvwprintw(puzzwin, i+3, 4, choices[i].c_str());
				wattroff(puzzwin, A_REVERSE);
			}
		}
		choice = wgetch(puzzwin);

		switch(choice) {
			case KEY_UP:
				highlight--;
				if(highlight == -1)
					highlight = 0;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 4)
					highlight = 3;
				break;
			default:
				break;
		}
		if(choice == 32)
			break;
	}
	wrefresh(puzzwin);
	move(20, 75);
	printw("YOU CHOSE: %s", choices[highlight].c_str());
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);

	if(highlight == 1) {
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

int main() {
	char player = '*';
	char enemy = 'X';
	int playerMove = 0;
	int num = 0;
	int FPS = 60;
	int x = 0, y = 0;


	endwin();
	system("figlet FREEDOM FIGHTERS - John McAfree");
	string startButton = read("Enter \'p\' to go into the world!\n");
	if (startButton == "p") {
		(void) initscr();
		(void) scrollok(stdscr, TRUE);
		keypad(stdscr, TRUE);
		(void) nonl();
		(void) cbreak();
		(void) noecho();
		WINDOW * startMenu;
		WINDOW * levelOne;

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

		wrefresh(stdscr);
		wmove(stdscr,100,500);
		map.screen(100,500);
		while ((playerMove = wgetch(stdscr)) != KEY_F(11)) {

			cin >> playerMove;

			if (playerMove == KEY_F(1)) {
				Menode();
			}
			if (playerMove == KEY_F(2)) {
				puzz();
			}

			else if (playerMove == ERR) usleep(1'000'000/FPS);

				else {
				playerMove = toupper(playerMove);
				Move(playerMove,map,stdscr);		

			}
		}
	}
	else usleep(500'00);

	attroff(COLOR_PAIR(1));

	clear();
	refresh();
	endwin();
}
