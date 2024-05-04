#include <iostream>
#include "actor.h"
using namespace std;

Actor::Actor(enum Special special, string name, int power, int max_health, int speed) : special(special), name(name), power(power), max_health(max_health), health(max_health), speed(speed) {}
pair<string, bool> Actor::attack(shared_ptr<Actor> target) {
	int min_damage = get_weapon()->get_damage();
	if (power < min_damage) min_damage = power;

	int added_damage = rand() % (get_weapon()->get_damage() - min_damage + 1);
	int blocked_damage = target->get_apparel()->get_block();
	int total_damage = min_damage + added_damage - blocked_damage; 
	if (total_damage < 1) total_damage = 1;

	target->set_health(target->get_health() - total_damage);
	bool is_dead = (target->get_health() == 0) ? true : false;
	
	string result = get_name() + " deals " + to_string(total_damage) + " damage to " + target->get_name() + ". ";
	if (is_dead) result += get_name() + " killed " + target->get_name() + "!";

	return make_pair(result, is_dead);	
}
enum Tier Actor::get_tier() const { 
	int power_tier = power / Stats::base_skill;
	int health_tier = health / Stats::health_skill;
	int speed_tier = speed / Stats::base_skill;
	
	int max = 0;
	if (power_tier > max) max = power_tier;
	if (health_tier > max) max = health_tier;
	if (speed_tier > max) max = speed_tier;

	if (max > Stats::max_tier) max = Stats::max_tier;
	return static_cast<Tier>(max);
}
string Actor::get_special_name() const {
	enum Special special = get_special();

	if (special == Special::Fighter) return "Fighter";
	if (special == Special::Defender) return "Defender";
	if (special == Special::Healer) return "Healer";
	return "SPECIAL";
}
const shared_ptr<Weapon> Actor::get_weapon() {
	if (!weapon) weapon = make_shared<Weapon>("Fist", 1);
	return weapon;
}
const shared_ptr<Apparel> Actor::get_apparel() {
	if (!apparel) apparel = make_shared<Apparel>("Rags", 0);
	return apparel;
}

void Actor::set_health(int health) {
	if (health < 0) this->health = 0;
	else if (health > this->max_health) this->health = this->max_health;
	else this->health = health;
}
void Actor::set_max_health(int max_health) {
	if (max_health < 1) this->max_health = 1;
	else this->max_health = max_health;
}
void Actor::set_weapon(shared_ptr<Weapon>& weapon) {
	this->weapon = weapon;
}
void Actor::set_apparel(shared_ptr<Apparel>& apparel) {
	this->apparel = apparel;
}

Hero::Hero(enum Special special, string name, int power, int max_health, int speed) : Actor(special, name, power, max_health, speed) {}

string Hero::get_special_name() const {
	enum Special special = get_special();

	if (special == Special::Fighter) return "Human";
	if (special == Special::Defender) return "Dwarf";
	if (special == Special::Healer) return "Elf";
	return "SPECIAL";
}
string Hero::get_title() const {
	string tier_name = Stats::get_tier_name(get_tier());
	string special_name = get_special_name();

	return tier_name + " " + special_name;
}

Monster::Monster(enum Special special, string name, int power, int max_health, int speed) : Actor(special, name, power, max_health, speed) {}

string Monster::get_special_name() const {
	enum Special special = get_special();

	if (special == Special::Fighter) return "Goblin";
	if (special == Special::Defender) return "Troll";
	if (special == Special::Healer) return "Witch";
	return "SPECIAL";
}
string Monster::get_title() const {
	string tier_name = Stats::get_tier_name(get_tier());
	string special_name = get_special_name();

	return tier_name + " " + special_name;
}
