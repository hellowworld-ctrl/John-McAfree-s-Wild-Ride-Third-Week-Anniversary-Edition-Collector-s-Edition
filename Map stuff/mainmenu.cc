#include <curses.h>
#include <ncurses.h>
#include <string>
#include <menu.h>
#include "/public/read.h"
using namespace std;

int main(int argc, char ** argv) {

	initscr();
	cbreak();
	noecho();
	//void mainmenu()
	//int height = 0, width = 0;
	int yMax = 24, xMax = 80;
	// moves the cursor
	
	getmaxyx(stdscr, yMax, xMax);
	WINDOW * mainwin = newwin(yMax/2, xMax/2, 1, 1);
	
		start_color();
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

	box(mainwin, 1, 1);
	refresh();
	wattron(mainwin, COLOR_PAIR(1));
	wborder(mainwin, '{', '}', '~', '~', '*', '*', '*', '*');
	wattroff(mainwin, COLOR_PAIR(1));
	wattron(mainwin, COLOR_PAIR(2));
	mvwprintw(mainwin, 2, 6, "FREEDOM FIGHTERS - John McAfee");
	wattroff(mainwin, COLOR_PAIR(2));

	// makes it so we can use arrow keys
	keypad(mainwin, true);

	int choice;
	int highlight = 0;
	string Choices[5] = {"Level 1", "Level 2", "Level 3", "Level 4", "Level 5"};

	while(true) {
		for (int i = 0; i < 5; i++) {
			wattron(mainwin, COLOR_PAIR(1));
			mvwprintw(mainwin, i+4, 4, Choices[i].c_str());
			wattroff(mainwin, COLOR_PAIR(1));
		}
		for (int i = 0; i < 5; i++) {
			if (i == highlight) {
				wattron(mainwin, A_REVERSE | COLOR_PAIR(2));
				mvwprintw(mainwin, i+4, 4, Choices[i].c_str());
				wattroff(mainwin, A_REVERSE | COLOR_PAIR(2));
			}
		}
		choice = wgetch(mainwin);

		switch(choice) {
			case KEY_UP:
				highlight--;
				if(highlight == -1)
				highlight = 0;
			break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 5)
				highlight = 4;
			break;
			default:
			break;
		}
		if(choice == 10)
		break;
	}
	wrefresh(mainwin);
	clear();
	refresh();
	/*
int main() 
	initscr();
	cbreak();
	noecho();

	mainmenu();
*/
	getch();
	endwin();

	return 0;
}
