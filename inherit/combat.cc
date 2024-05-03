#include <iostream>
#include <algorithm>
#include <typeinfo>
#include "combat.h"
using namespace std;

Combat::Combat(const shared_ptr<Party<Hero>>& heroes, const shared_ptr<Party<Monster>>& monsters) 
{
	index = 0;

	this->heroes = heroes;
	this->monsters = monsters;

	// Add actors to combatants
	for (const shared_ptr<Hero>& hero : heroes->get_actors())
	{
		combatants.push_back(hero);
	}
	for (const shared_ptr<Monster>& monster : monsters->get_actors())
	{
		combatants.push_back(monster);
	}

	// Organize combatants by their speed
	sort(combatants.begin(), combatants.end(), [](const shared_ptr<Actor>& a, const shared_ptr<Actor>& b) { return a->get_speed() > b->get_speed(); });
}

pair<string, bool> Combat::do_combat() {
	if (heroes->get_size() == 0)
	{
		return make_pair("Monsters won the fight.", false);
	}
	else if (monsters->get_size() == 0)
	{
		return make_pair("Heroes won the fight.", false);
	}
	else
	{
		// Get next living combatant
		if (combatants.at(index)->get_health() == 0)
		{
			do
			{
				index++;
				if (index >= static_cast<int>(combatants.size())) index = 0;
			} while (combatants.at(index)->get_health() == 0);
		}
		
		// Determine type
		bool is_hero = false;
		if (dynamic_pointer_cast<Hero>(combatants.at(index))) is_hero = true;

		// Get next target index
		shared_ptr<Actor> target;
		int targetIndex = index;
		bool redo = rand() % 2;

		do
		{
			targetIndex++;
			if (targetIndex >= static_cast<int>(combatants.size())) targetIndex = 0;
		} while ((is_hero && dynamic_pointer_cast<Hero>(combatants.at(targetIndex))) || (!is_hero && dynamic_pointer_cast<Monster>(combatants.at(targetIndex))));

		if (redo)
		{
			do
			{
				targetIndex++;
				if (targetIndex >= static_cast<int>(combatants.size())) targetIndex = 0;
			} while ((is_hero && dynamic_pointer_cast<Hero>(combatants.at(targetIndex))) || (!is_hero && dynamic_pointer_cast<Monster>(combatants.at(targetIndex))));
		}

		pair<string, bool> result = combatants.at(index)->attack(combatants.at(targetIndex));

		if (result.second)
		{
			// Handle death
			monsters->try_remove_actor(combatants.at(targetIndex));
			heroes->try_remove_actor(combatants.at(targetIndex));
		
			shared_ptr<Actor> current = combatants.at(index);
			combatants.erase(combatants.begin() + targetIndex);
		
			// Get correct index after erase
			for (int i = 0; i < static_cast<int>(combatants.size()); i++)
			{
				if (combatants.at(i) == current)
				{
					index = i;
					break;
				}
			}
		}
		
		// Increment index for next combat
		index++;
		if (index >= static_cast<int>(combatants.size())) index = 0;

		return make_pair(result.first, true);
	}
}
