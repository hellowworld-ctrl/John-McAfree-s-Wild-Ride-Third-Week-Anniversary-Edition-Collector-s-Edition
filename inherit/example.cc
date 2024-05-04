#include <iostream>
#include <cstdlib>
#include <ctime>
#include "combat.h"
#include "generate.h"
#include "tier.h"
using namespace std;

// Party is a collection of actors.
// Tier is the skill of an actor. Common -> Uncommon -> Rare -> Epic -> Legendary
// Generating parties, actors, or items requires their tier to be passed as an argument.

int main() {

	// ------------ HOW TO AUTOMATICALLY GENERATE PARTY OF SAME-TIERED ACTORS: 
	// Automatically generate a Legendary party of two heroes.
	shared_ptr<Party<Hero>> autoHeroes = Generate::generate_party<Hero>(Tier::Legendary, 2);
	// Automatically generate an Epic party of two monsters.
	shared_ptr<Party<Monster>> autoMonsters = Generate::generate_party<Monster>(Tier::Epic, 2);

	// ------------ HOW TO MANUALLY GENERATE PARTY OF DIFFERENT-TIERED ACTORS:
	// Create an empty party of heroes.
	shared_ptr<Party<Hero>> manualHeroes = make_shared<Party<Hero>>();
	// Manually generate two heroes, then add them to manualHeroes party.
	manualHeroes->try_add_actor(Generate::generate_hero(Tier::Rare));
	manualHeroes->try_add_actor(Generate::generate_hero(Tier::Uncommon));
	// Create an empty party of monsters.
	shared_ptr<Party<Monster>> manualMonsters = make_shared<Party<Monster>>();
	// Manually generate two monsters, then add them to manualMonsters party.
	manualMonsters->try_add_actor(Generate::generate_monster(Tier::Uncommon));
	manualMonsters->try_add_actor(Generate::generate_monster(Tier::Common));

	// ------------ HOW TO GENERATE ITEMS:
	// Generate an example party of heroes.
	shared_ptr<Party<Hero>> exampleParty = Generate::generate_party<Hero>(Tier::Legendary, 2);	
	// Generate weapon and apparel.
	shared_ptr<Weapon> weapon = Generate::generate_weapon(Tier::Legendary);
	shared_ptr<Apparel> apparel = Generate::generate_apparel(Tier::Common);
	// Add items to example party inventory.
	exampleParty->get_inventory()->add_item(weapon);
	exampleParty->get_inventory()->add_item(apparel);
	// Automatically equip best items available in inventory.
	exampleParty->equip();

	// ------------ HOW TO MOVE PARTIES AROUND THE MAP:
	// Pass the desired (x, y) coordinate as a parameter.
	exampleParty->set_point(2, 2);

	// ------------ HOW TO COMBAT:
	// Create combat object with an existing hero and monster party as parameters.
	shared_ptr<Combat> combat = make_shared<Combat>(autoHeroes, autoMonsters);
	// Prepare to capture the result of the next combat.
	pair<string, bool> result;
	// Let the next combatant attack a random target.
	result = combat->do_combat();
	// The first result will describe the combat as a string.
	cout << result.first << endl;
	// The second result indicates if combat is ongoing as a bool.
	cout << "Are both parties fighting: " << boolalpha << result.second << endl;
	// To end combat, continue to call do_combat() until result.second is false.

	return 0;
}
