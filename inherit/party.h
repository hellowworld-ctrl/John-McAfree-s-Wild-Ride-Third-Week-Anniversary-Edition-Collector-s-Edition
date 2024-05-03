#ifndef PARTY_H
#define PARTY_H

#include <algorithm>
#include <vector>
#include <memory>
#include "actor.h"
#include "point.h"

template <typename T>
class Party
{
public:
	Party(const std::vector<std::shared_ptr<Actor>>& actors = std::vector<std::shared_ptr<Actor>>(), const std::shared_ptr<Point> point = std::make_shared<Point>(0, 0)) : inventory(std::make_shared<Inventory>()) {
		for (const std::shared_ptr<Actor>& actor : actors)
		{
			try_add_actor(actor);	
		}

		this->point = point;
	}

	// Rule of three
	Party(const Party &other) = delete;
	Party& operator=(const Party &other) = delete;
	~Party() = default;

	// Functions
	void equip() {
		// Sort weapon
		std::vector<std::shared_ptr<Weapon>> weapons_sort;	
		for (std::shared_ptr<Item> item : get_inventory()->get_items())
		{
			if (std::dynamic_pointer_cast<Weapon>(item)) weapons_sort.push_back(std::dynamic_pointer_cast<Weapon>(item));	
		}
		std::sort(weapons_sort.begin(), weapons_sort.end(), [](const std::shared_ptr<Weapon>& a, const std::shared_ptr<Weapon>& b) { return a->get_damage() > b->get_damage(); });
		// Sort power
		std::vector<std::shared_ptr<Actor>> actors_sort;
		for (std::shared_ptr<Actor> actor : get_actors())
		{
			actors_sort.push_back(actor);
		}
		std::sort(actors_sort.begin(), actors_sort.end(), [](const std::shared_ptr<Actor>& a, const std::shared_ptr<Actor>& b) { return a->get_power() > b->get_power(); });
		// Equip weapon
		for (int i = 0; i < static_cast<int>(actors_sort.size()); i++)
		{
			actors_sort.at(i)->set_weapon(weapons_sort.at(i));
		}

		// Sort apparel
		std::vector<std::shared_ptr<Apparel>> apparel_sort;	
		for (std::shared_ptr<Item> item : get_inventory()->get_items())
		{
			if (std::dynamic_pointer_cast<Apparel>(item)) apparel_sort.push_back(std::dynamic_pointer_cast<Apparel>(item));	
		}
		std::sort(apparel_sort.begin(), apparel_sort.end(), [](const std::shared_ptr<Apparel>& a, const std::shared_ptr<Apparel>& b) { return a->get_block() > b->get_block(); });
		// Sort health
		std::sort(actors_sort.begin(), actors_sort.end(), [](const std::shared_ptr<Actor>& a, const std::shared_ptr<Actor>& b) { return a->get_health() < b->get_health(); });
		// Equip apparel
		for (int i = 0; i < static_cast<int>(actors_sort.size()); i++)
		{
			actors_sort.at(i)->set_apparel(apparel_sort.at(i));
		}
	}
	bool try_add_actor(std::shared_ptr<Actor> actor) {
		std::shared_ptr<T> derived = std::dynamic_pointer_cast<T>(actor);
		if (derived) 
		{
			actors.push_back(derived);
			return true;
		}

		return false;
	}
	bool try_remove_actor(std::shared_ptr<Actor> actor) {
		for (int i = actors.size() - 1; i >= 0; i--)
		{
			if (actors.at(i) == actor) 
			{
				actors.erase(actors.begin() + i);
				return true;
			}
		}

		return false;
	}
	
	// Getters
	int get_size() const { return actors.size(); }
	std::shared_ptr<Point> get_point() const { return point; } 
	std::shared_ptr<Inventory> get_inventory() const { return inventory; }
	std::vector<std::shared_ptr<T>> get_actors() const { return actors; }

	// Setters
	void set_point(int x, int y) { point = std::make_shared<Point>(Point(x, y)); }
private:
	std::vector<std::shared_ptr<T>> actors;
	std::shared_ptr<Inventory> inventory;	
	std::shared_ptr<Point> point;
};

#endif
