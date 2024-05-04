#ifndef COMBAT_H
#define COMBAT_H

#include <vector>
#include <memory>
#include <utility>
#include "party.h"

class Combat
{
public:
	Combat(const std::shared_ptr<Party<Hero>>& heroes, const std::shared_ptr<Party<Monster>>& monsters);
	// Rule of three
	Combat(const Combat &other) = delete;
	Combat& operator=(const Combat &other) = delete;
	~Combat() = default;

	// Functions		
	std::pair<std::string, bool> do_combat();

	// Getters
	const std::vector<std::shared_ptr<Actor>>& get_combatants() const { return combatants; }
	int get_index() const { return index; }
private:
	std::vector<std::shared_ptr<Actor>> combatants;
	std::shared_ptr<Party<Hero>> heroes;
	std::shared_ptr<Party<Monster>> monsters;
	int index;
};

#endif 
