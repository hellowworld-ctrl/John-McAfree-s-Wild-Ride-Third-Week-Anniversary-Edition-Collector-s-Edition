#pragma once

#include <curses.h>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>
#include <Color.h>

using namespace std;


class Map {

	vector<vector<char>> map;
	default_random_engine gen;
public:
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

	bool isEnemy(int &x,int &y) {
		return map.at(y).at(x) == VIRUS;
	}

	Map() {
		generateMap();
	}
	~Map() = default;


};
