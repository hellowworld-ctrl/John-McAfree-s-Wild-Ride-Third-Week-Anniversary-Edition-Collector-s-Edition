#include <iostream>
#include <cstdlib>
#include <ctime>
#include "combat.h"
#include "generate.h"
#include "tier.h"
using namespace std;

#define RED "\033[31m"
#define RESET "\033[0m"

void end() {
	cout << "Bad input" << endl;
	exit(0);
}

template<typename T>
void print_stats(shared_ptr<Party<T>>& party, bool is_heroes) {
	if (is_heroes) cout << "[HERO STATS]" << endl;
	else cout << "[MONSTER STATS]" << endl;
	
	for (shared_ptr<Actor> actor : party->get_actors())
	{
		cout << actor->get_name() << " the " << actor->get_title() << endl;
		cout << "Power: " << actor->get_power() << endl;
		cout << "Health: " << actor->get_health() << "/" << actor->get_max_health() << endl;
		cout << "Speed: " << actor->get_speed() << endl;
		cout << endl;
	}
}

template<typename T>
void print_inventory(shared_ptr<Party<T>>& party, bool is_heroes) {
	if (is_heroes) cout << "[HERO INVENTORY]" << endl;
	else cout << "[MONSTER INVENTORY]" << endl;
	
	for (shared_ptr<Actor> actor : party->get_actors())
	{
		cout << actor->get_name() << " the " << actor->get_title() << endl;
		cout << "[" << actor->get_weapon()->get_damage() << "] " << "Weapon: " << actor->get_weapon()->get_title() << endl;
		cout << "[" << actor->get_apparel()->get_block() << "] " << "Apparel: " << actor->get_apparel()->get_title() << endl;
		cout << endl;
	}
}

void print_turn_order(shared_ptr<Combat>& combat) {
	cout << "[TURN ORDER]" << endl;

	for (int i = 0; i < static_cast<int>(combat->get_combatants().size()); i++)
	{
		shared_ptr<Actor> actor = combat->get_combatants().at(i);
		cout << "[" << i << "] " << actor->get_name() << " the " << actor->get_title();
		if (combat->get_index() == i) cout << " [CURRENT]" << endl;
		else cout << endl;
	}
	
	cout << endl;
}

int main()
{
	srand(time(0));
	int input;

	cout << "--------------------------------------------------" << endl;
	cout << "[GENERATION]" << endl;
	cout << "[0] Common" << endl;
	cout << "[1] Uncommon" << endl;
	cout << "[2] Rare" << endl;
	cout << "[3] Epic" << endl;
	cout << "[4] Legendary" << endl;

	cout << endl << "Select hero tier: " << endl;
	cin >> input;
	if (cin.fail()) { input = 0; cin.clear(); cin.ignore(); end(); }
	if (input > Stats::max_tier) input = Stats::max_tier;
	shared_ptr<Party<Hero>> heroes = Generate::generate_party<Hero>(static_cast<Tier>(input));
	
	cout << endl << "Select monster tier: " << endl;
	cin >> input;
	if (cin.fail()) { input = 0; cin.clear(); cin.ignore(); end(); }
	if (input > Stats::max_tier) input = Stats::max_tier;
	shared_ptr<Party<Monster>> monsters = Generate::generate_party<Monster>(static_cast<Tier>(input));

	shared_ptr<Combat> combat = make_shared<Combat>(heroes, monsters);
	pair<string, bool> result = make_pair("Temporary", true);
	bool is_started = false;

	do
	{
		cout << "--------------------------------------------------" << endl;
		cout << "[SELECT]" << endl;
		cout << "[0] Hero stats" << endl;
		cout << "[1] Monster stats" << endl;
		cout << "[2] Hero inventory" << endl;
		cout << "[3] Monster inventory" << endl;
		cout << "[4] Turn order" << endl;
		if (is_started) cout << "[5] Continue the fight!" << endl;
		else cout << "[5] Start the fight!" << endl;

		cin >> input;
		if (cin.fail()) { input = 0; cin.clear(); cin.ignore(); end(); }
		cout << endl;

		if (input <= 0)
		{
			print_stats(heroes, true);
		}
		else if (input == 1)
		{
			print_stats(monsters, false);
		}
		else if (input == 2)
		{
			print_inventory(heroes, true);
		}
		else if (input == 3)
		{
			print_inventory(monsters, false);
		}
		else if (input == 4)
		{
			print_turn_order(combat);	
		}
		else if (input >= 5)
		{
			cout << "[Q] Pause the fight" << endl << endl;
			is_started = true;

			do
			{
				string pause;
				getline(cin, pause);
				if (pause == "Q" || pause == "q") break;

				int size = combat->get_combatants().size();
				result = combat->do_combat();
				if (static_cast<int>(combat->get_combatants().size()) != size) cout << RED;
				cout << result.first << RESET << endl << endl;
			
			} while (result.second);
		}

	} while (result.second);

	return 0;
}
