#include <iostream>
#include "tier.h"
using namespace std;

string Stats::get_tier_name(enum Tier tier) {
	if (tier == Tier::Common) return "Common";
	if (tier == Tier::Uncommon) return "Uncommon";
	if (tier == Tier::Rare) return "Rare";
	if (tier == Tier::Epic) return "Epic";
	if (tier == Tier::Legendary) return "Legendary";
	return "TIER";
}
