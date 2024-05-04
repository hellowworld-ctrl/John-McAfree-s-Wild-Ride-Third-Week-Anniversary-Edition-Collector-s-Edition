#include <iostream>
#include "item.h"
using namespace std;

Item::Item(string name) : name(name) {}

bool Item::operator>(const Item &other) const {
	if (get_value() > other.get_value()) return true;
	return false;
}

Weapon::Weapon(string name, int damage) : Item(name), damage(damage) {}

enum Tier Weapon::get_tier() const {
	int damage_tier = damage / Stats::base_skill;
	
	int max = 0;
	if (damage_tier > max) max = damage_tier;

	if (max > Stats::max_tier) max = Stats::max_tier;
	return static_cast<Tier>(max);
}

Apparel::Apparel(string name, int block) : Item(name), block(block) {}

enum Tier Apparel::get_tier() const {
	int block_tier = block / Stats::apparel_skill;
	
	int max = 0;
	if (block_tier > max) max = block_tier;

	if (max > Stats::max_tier) max = Stats::max_tier;
	return static_cast<Tier>(max);
}
