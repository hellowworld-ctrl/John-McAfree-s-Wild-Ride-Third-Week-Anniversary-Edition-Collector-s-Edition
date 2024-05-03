#ifndef TIER_H
#define TIER_H

#include <string>

// Invariants
// 1. max_tier must equal the largest enum Tier value

enum Tier
{
	Common = 0,
	Uncommon = 1,
	Rare = 2,
	Epic = 3,
	Legendary = 4
};

namespace Stats
{
const int max_tier = 4;
const int base_skill = 10;
const int health_skill = base_skill * 4;
const int apparel_skill = base_skill / 2;

std::string get_tier_name(enum Tier tier);
};

#endif
