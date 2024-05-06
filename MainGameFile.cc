#include <cstdlib>
#include "/public/read.h"
#include <curses.h>
#include "Map stuff/Map.h"
#include "Map stuff/MapBeach.h"
#include "Map stuff/MapRoad.h"
#include "Map stuff/MapCity.h"
#include "Map stuff/MapAirport.h"
#include "inherit/combat.h"
#include "inherit/generate.h"
#include "inherit/tier.h"
#include <stdlib.h>
#include <ncurses.h>
#include <random>
#include <menu.h>
#include <signal.h>
#include <iostream>
#include <cctype>
#include <thread>

using namespace std;

shared_ptr<Party<Hero>> mainParty;
int enemiesKilled = 0;
bool keyBeach = false;
bool keyRoad = false;
bool keyCity = false;
bool keyAirport = false;
int backToMenu = false;

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
	    int size = mainParty->get_inventory()->get_items().size();

		for(int i = 0; i < 0; i++)
		{
          string title = mainParty->get_inventory()->get_items().at(i)->get_title();
			wmove(menuwin, i + 5, 1);
			waddstr(menuwin, title.c_str());
		}
			wrefresh(menuwin);

		//clear();
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

    void CombatMode()
    {
        shared_ptr<Party<Monster>> MonsterCombat = Generate::generate_party<Monster>(Tier::Common, 5);

        int x = 30, y = 30, yMax = 50, xMax = 50;
        // moves the cursor
        move(y, x);
        getmaxyx(stdscr, yMax, xMax);

        WINDOW * puzzwin = newwin(18, xMax / 2, yMax / 2, 80);

        box(puzzwin, 0, 0);
        refresh();
        wborder(puzzwin, '|', '|', '-', '-', '/', '*', '+', '+');
        mvwprintw(puzzwin, 1, 35, "A Fight has Broken Out!");
        wrefresh(puzzwin);

        // makes it so we can use arrow keys
        keypad(puzzwin, true);

        string choices[4] = {"Fight.", "", "", ""};
        int choice;     
        int highlight = 1;     

        shared_ptr<Combat> combat = make_shared<Combat>(mainParty, MonsterCombat);
        int amountAdded = 0;

        string finalBout;

        while (true) {
        // Prepare to capture the result of the next combat.
        pair<string, bool> result;
        // Let the next combatant attack a random target.
        result = combat->do_combat();
         if(!result.second){
            finalBout = result.first;
            break;
        }
        mvwprintw(puzzwin, amountAdded+3, 35, result.first.c_str());  
        wrefresh(puzzwin);
        // The first result will describe the combat as a string.
         //cout << result.first << endl;

         amountAdded += 1;
         sleep(1);
        }

        wrefresh(puzzwin);
        move(20, 105);

        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);

        usleep(5);
        usleep(500'000);
        if (finalBout == "Heroes won the fight.") {
            attron(COLOR_PAIR(1));
            move(22, 105);
            printw(finalBout.c_str());
		    enemiesKilled+= 1;
            attroff(COLOR_PAIR(1));
        } else {
            attron(COLOR_PAIR(2));
            move(22, 105);
            printw(finalBout.c_str());
            attroff(COLOR_PAIR(2));
        }

        getch();
        clear();
        refresh();
    }




template<typename MapType>
void Move(const int &ch, MapType&map, WINDOW *win) {
	int x = 0, y = 0;
	getyx(win, y, x);

	int newX = x;
	int newY = y;

	if (ch == 'W' || ch == KEY_UP) newY -= 1;
	else if (ch == 'A' || ch == KEY_LEFT) newX -= 1;
	else if (ch == 'S' || ch == KEY_DOWN) newY += 1;
	else if (ch == 'D' || ch == KEY_RIGHT) newX += 1;

	if (map.isEnemy(newX, newY) == true) {
		CombatMode();
		wmove(win, y, x);
		wrefresh(win);

		if(enemiesKilled == 3)
		{
           mvprintw(100, 100, "NEW MAP UNLOCKED!"); 
		  if(!keyBeach) keyBeach = true;
		  else if(!keyRoad) keyRoad = true;
		  else if(!keyCity) keyCity = true;
		  else keyAirport = true;
	
		  backToMenu = true;
		  enemiesKilled = 0;
		wrefresh(win);
			sleep(1);
		}
		map.map.at(newY).at(newX) = map.OPEN;
		wmove(win, y, x);
		wrefresh(win);
	} else if (map.isChest(newX, newY) == true) {
		mvprintw(0, 80, "OPENED A CHEST!");
	    shared_ptr<Weapon> weapon;
		int randomChance = rand() % 10 + 1;

		if(randomChance >= 9)weapon = Generate::generate_weapon(Tier::Legendary);
		else if(randomChance >= 6)weapon = Generate::generate_weapon(Tier::Rare);
		else weapon = Generate::generate_weapon(Tier::Uncommon);
	
		string itemName = "You obtained a " + weapon->get_title();

		mvprintw(5, 80, itemName.c_str());
		
		mainParty->get_inventory()->add_item(weapon);
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

//	flushinp();
}

int main() {
	srand(time(NULL));
	int playerMove = 0;
	int FPS = 60;
	initscr();
	scrollok(stdscr, TRUE);
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();

    mainParty = Generate::generate_party<Hero>(Tier::Rare, 5);
label:
	backToMenu = false;
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
	string Choices[6] = {"Level 1 - House", "Level 2 - Beach", "Level 3 - Road", "Level 4 - City", "Level 5 - Airport", "DEBUG: Unlock All Levels(If you want to check them out.)"};

	while(true) {
		for (int i = 0; i < 6; i++) {
			wattron(mainwin, COLOR_PAIR(5));
			mvwprintw(mainwin, i+4, 4, Choices[i].c_str());
			wattroff(mainwin, COLOR_PAIR(5));
		}
		for (int i = 0; i < 6; i++) {
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
				if(highlight == 6)
					highlight = 5;
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
		map.lore();
		clear();
		refresh();
		map.screen(50, 50);
		while ((playerMove = wgetch(stdscr)) != 'q') {

			cin >> playerMove;

			if (playerMove == KEY_F(1)) {
				Menu();
			} else if (playerMove == KEY_F(2)) {
				if (map.puzz()) {
					keyBeach = true;
					clear();
					refresh();
					getch();
					goto label;
				}
			}

			else if (playerMove == ERR) usleep(1'000'000 / FPS);

				else {
				playerMove = toupper(playerMove);
				map.monsterMove();
				Move(playerMove, map, playwin);
                if(backToMenu) goto label;
			}
		}
	}
	else if (highlight == 1 and keyBeach == true) {
		MapBeach map;
		map.lore();
		clear();
		refresh();
		map.screen(50, 50);
		while ((playerMove = wgetch(stdscr)) != 'q') {

			cin >> playerMove;

			if (playerMove == KEY_F(1)) {
				Menu();
			} else if (playerMove == KEY_F(2)) {
				if(map.puzz()) {
					keyRoad = true;
					clear();
					refresh();
					getch();
					goto label;
				}
			}

			else if (playerMove == ERR) usleep(1'000'000 / FPS);

				else {
				playerMove = toupper(playerMove);
				map.monsterMove();
				Move(playerMove, map, playwin);
                if(backToMenu) goto label;

			}
		}
	}
	else if (highlight == 2 and keyRoad == true) {
		MapRoad map;
		map.lore();
		clear();
		refresh();
		map.screen(50, 50);
		while ((playerMove = wgetch(stdscr)) != 'q') {

			cin >> playerMove;

			if (playerMove == KEY_F(1)) {
				Menu();
			} else if (playerMove == KEY_F(2)) {
				if(map.puzz()) {
					keyCity = true;
					clear();
					refresh();
					getch();
					goto label;
				}
			}

			else if (playerMove == ERR) usleep(1'000'000 / FPS);

				else {
				playerMove = toupper(playerMove);
				map.monsterMove();
				Move(playerMove, map, playwin);
                if(backToMenu) goto label;

			}
		}
	}
	else if (highlight == 3 and keyCity == true) {
		MapCity map;
		map.lore();
		clear();
		refresh();
		map.screen(50, 50);
		while ((playerMove = wgetch(stdscr)) != 'q') {

			cin >> playerMove;

			if (playerMove == KEY_F(1)) {
				Menu();
			} else if (playerMove == KEY_F(2)) {
				if(map.puzz()) {
					keyAirport = true;
					clear();
					refresh();
					getch();
					goto label;
				}
			}

			else if (playerMove == ERR) usleep(1'000'000 / FPS);

				else {
				playerMove = toupper(playerMove);
				map.monsterMove();
				Move(playerMove, map, playwin);
                if(backToMenu) goto label;

			}
		}
	}
	else if (highlight == 4 and keyAirport == true) {
		MapAirport map;
		map.lore();
		clear();
		refresh();
		map.screen(50, 50);
		while ((playerMove = wgetch(stdscr)) != 'q') {

			cin >> playerMove;

			if (playerMove == KEY_F(1)) {
				Menu();
			} else if (playerMove == KEY_F(2)) {
				if (map.puzz()) {
					clear();
					refresh();
					WINDOW * cong = newwin(100, 80, 0, 0);
					box(cong, 0, 0);
			wattron(cong, COLOR_PAIR(2));
					mvwprintw(cong, 25, 25, "YOUR FREE TRIAL HAS ENDED:");
					mvwprintw(cong, 28, 25, "https://www.mcafee.com/en-us/antivirus.html");
			wattroff(cong, COLOR_PAIR(2));
					wrefresh(cong);
					getch();
					break;
				}
			}

			else if (playerMove == ERR) usleep(1'000'000 / FPS);

				else {
				playerMove = toupper(playerMove);
				map.monsterMove();
				Move(playerMove, map, playwin);
                if(backToMenu) goto label;

			}
		}
	}
	else if(highlight == 5){
	 keyBeach = true;
		keyRoad = true;
		keyCity = true;
		keyAirport = true;
        mvwprintw(mainwin, 25, 90, "UNLOCKED ALL LEVELS");
		wrefresh(mainwin);
		getch();
		goto label;
	}
	else {
		mvwprintw(mainwin, 25, 90, "LEVEL NOT UNLOCKED!");
		wrefresh(mainwin);
		getch();
		goto label;
	}

	attroff(COLOR_PAIR(1));
	clear();
	refresh();
	endwin();
}
