#include <iostream>
#include "generate.h"
using namespace std;

shared_ptr<Monster> Generate::generate_monster(enum Tier tier) {
	return make_shared<Monster>(generate_special(), generate_name(false), generate_power(try_lower_tier(tier)), generate_health(try_lower_tier(tier)), generate_speed(try_lower_tier(tier)));
}
shared_ptr<Hero> Generate::generate_hero(enum Tier tier) {
	return make_shared<Hero>(generate_special(), generate_name(true), generate_power(try_lower_tier(tier)), generate_health(try_lower_tier(tier)), generate_speed(try_lower_tier(tier)));
}

enum Special Generate::generate_special() {
	int special = rand() % (Actor::max_special + 1);
	return static_cast<Special>(special);
}
string Generate::generate_name(bool is_hero) {
	if (is_hero)
	{
		int index = 0;

		do 
		{
			index = rand() % Name::hero_names.size();
		}
		while (Name::used_hero_index.find(index) != Name::used_hero_index.end());
	
		Name::used_hero_index.insert(index);
		return Name::hero_names.at(index);
	}
	else
	{
		int index = 0;

		do 
		{
			index = rand() % Name::monster_names.size();
		}
		while (Name::used_monster_index.find(index) != Name::used_monster_index.end());
	
		Name::used_monster_index.insert(index);
		return Name::monster_names.at(index);
	}
}
int Generate::generate_power(enum Tier tier) {
	int base = tier * Stats::base_skill;
	int add = rand() % Stats::base_skill;
	int sum = base + add;

	if (sum < 1) return 1;
	return sum;
}
int Generate::generate_health(enum Tier tier) {
	int base = tier * Stats::health_skill;
	int add = rand() % Stats::health_skill;
	int sum = base + add;

	if (sum < 1) return 1;
	return sum;
}
int Generate::generate_speed(enum Tier tier) {
	int base = tier * Stats::base_skill;
	int add = rand() % Stats::base_skill;
	int sum = base + add;

	if (sum < 1) return 1;
	return sum;
}

string Generate::generate_weapon_name() {
	int index = rand() % Name::weapon_names.size();
	return Name::weapon_names.at(index);	
}
shared_ptr<Weapon> Generate::generate_weapon(enum Tier tier) {
	int base = tier * Stats::base_skill;
	int add = rand() % Stats::base_skill;
	int sum = base + add;

	if (sum < 1) sum = 1;
	return make_shared<Weapon>(generate_weapon_name(), sum);
}
shared_ptr<Potion> Generate::generate_potion(enum Tier tier) {
	int base = tier * Stats::base_skill;
	int add = rand() % Stats::base_skill;
	int sum = base + add;

	if (sum < 1) sum = 1;
	return make_shared<Potion>("Potion", sum);	
}
string Generate::generate_apparel_name() {
	int index = rand() % Name::apparel_names.size();
	return Name::apparel_names.at(index);	
}
shared_ptr<Apparel> Generate::generate_apparel(enum Tier tier) {
	int base = tier * Stats::apparel_skill;
	int add = rand() % Stats::apparel_skill;
	int sum = base + add;

	if (sum < 1) sum = 1;
	return make_shared<Apparel>(generate_apparel_name(), sum);		
}

enum Tier Generate::try_lower_tier(enum Tier tier) {
	enum Tier new_tier = tier;

	if (tier > 0)
	{
		int power_int = tier - (rand() %  2);
		new_tier = static_cast<Tier>(power_int);
	}	

	return new_tier;
}
