#ifndef GENERATE_H
#define GENERATE_H

#include <set>
#include <memory>
#include "party.h"
#include "item.h"

namespace Generate
{
const int max_party_size = 5;
const int min_party_size = 1;

enum Tier try_lower_tier(enum Tier tier);

std::string generate_weapon_name();
std::shared_ptr<Weapon> generate_weapon(enum Tier tier);
std::string generate_apparel_name();
std::shared_ptr<Apparel> generate_apparel(enum Tier tier);

std::shared_ptr<Monster> generate_monster(enum Tier tier);
std::shared_ptr<Hero> generate_hero(enum Tier tier);

template<typename T> inline std::shared_ptr<Party<T>> generate_party(enum Tier tier, int actorAmount) {}
template<> inline std::shared_ptr<Party<Monster>> generate_party<Monster>(enum Tier tier, int actorAmount) {
	std::shared_ptr<Party<Monster>> party = std::make_shared<Party<Monster>>();
	
	int actor_amount = actorAmount;
	if (actor_amount < min_party_size) actor_amount = min_party_size;
	if (actor_amount > max_party_size) actor_amount = max_party_size;

	for (int i = 1; i <= actor_amount; i++)
	{
		std::shared_ptr<Monster> monster = generate_monster(tier);
		party->try_add_actor(monster);
		
		party->get_inventory()->add_item(generate_weapon(try_lower_tier(tier)));
		party->get_inventory()->add_item(generate_apparel(try_lower_tier(tier)));
		
		if (monster->get_special() == Special::Healer) party->get_inventory()->add_item(generate_weapon(try_lower_tier(tier)));
	}

	party->equip();

	return party;	
}
template<> inline std::shared_ptr<Party<Hero>> generate_party<Hero>(enum Tier tier, int actorAmount) {
	std::shared_ptr<Party<Hero>> party = std::make_shared<Party<Hero>>();
	
	int actor_amount = actorAmount;
	if (actor_amount < min_party_size) actor_amount = min_party_size;
	if (actor_amount > max_party_size) actor_amount = max_party_size;

	for (int i = 1; i <= actor_amount; i++)
	{
		std::shared_ptr<Hero> hero = generate_hero(tier);
		party->try_add_actor(hero);
	
		party->get_inventory()->add_item(generate_weapon(try_lower_tier(tier)));
		party->get_inventory()->add_item(generate_apparel(try_lower_tier(tier)));
		
		if (hero->get_special() == Special::Healer) party->get_inventory()->add_item(generate_weapon(try_lower_tier(tier)));
	}
	
	party->equip();

	return party;		
}

enum Special generate_special();
std::string generate_name(bool is_hero);
int generate_power(enum Tier tier);
int generate_health(enum Tier tier);
int generate_speed(enum Tier tier);

namespace Name
{
static std::set<int> used_hero_index = {};
static std::set<int> used_monster_index = {};

const std::vector<std::string> hero_names = 
	{
		"Greg",
		"Sam",
		"George",
		"Jacob",
		"Jose",
		"Paul",
		"David",
		"James",
		"Gage",
		"Vance",
		"Bran",
		"Travis",
		"Richard",
		"Phillip",
		"Peter",
		"Michael",
		"Justin",
		"Bill",
		"Henry",
		"Alex",
		"John",
		"Bob",
		"Joe",
		"Gabriel",
		"Tim",
		"Matthew",
		"Cameron",
		"Connor",
		"Adam",
		"Donald",
		"Kieth",
		"William",
		"Eric",
		"Ronald",
		"Steven",
		"Nathan",
		"Devin",
		"Ben",
		"Rick",
		"Anakin",
		"Frodo",
		"Charles",
		"Noah",
		"Oliver",
		"Chris",
		"Liam",
		"Jack",
		"Theodore",
		"Owen",
		"Leo",
		"Luke",
		"Anthony",
		"Nick",
	};
const std::vector<std::string> monster_names =
	{
		"Raydon",
		"Tycho",
		"Saand",
		"Copper",
		"Sukun",
		"Werit",
		"Sephiran",
		"Talon",
		"Spike",
		"Zeidan",
		"Trik",
		"Echo",
		"Maggard",
		"Kragen",
		"Sem",
		"Zephyr",
		"Zul",
		"Riddles",
		"Mock",
		"Lik-Noots",
		"Thorne",
		"Raze",
		"Stabby",
		"Thick",
		"Lump",
		"Sore",
		"Punt",
		"Blip",
		"Boop",
		"Tipple",
		"Hoggle",
		"Strep",
		"Glop",
		"Mortem",
		"Clertz",
		"Mago",
		"Bakkins",
		"Lude",
		"Cader",
		"Crup",
		"Plub",
		"Ren",
		"Bim-Bop",
		"Shulk",
		"Anther",
		"Manther",
		"Danther",
		"Planther",
		"Tranther",
		"Wenth",
		"Benth",
		"Penth",
		"Silch",
		"Grug",
		"Mance",
		"Lutter",
		"Stutters",
		"Trop",
		"Singe",
		"Trump",
		"Vader",
		"Sauron",
	};
const std::vector<std::string> weapon_names =
	{
		"Sword",
		"Hatchet",
		"Axe",
		"Spear",
		"Bow",
		"Crossbow",
		"Mace",
		"Halberd",
		"Pike",
	};
const std::vector<std::string> apparel_names =
	{
		"Chainmail",
		"Leather",
		"Steel Plate",
		"Iron Plate",
		"Robes",
	};
};
};
#endif
