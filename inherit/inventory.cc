#include <iostream>
#include <algorithm>
#include <ostream>
#include "inventory.h"
using namespace std;

Inventory::Inventory() : items() {}
Inventory::Inventory(const Inventory &other) {
    currency = other.currency;
    for (const auto& item : other.items) {
        items.push_back(item);
    }
}
Inventory& Inventory::operator=(const Inventory &other) {
	if (this != &other) 
	{
		// Old
        items.clear();
		
		// New
		currency = other.currency;
        for (const auto& item : other.items) 
		{
            items.push_back(item);
        }
    }

    return *this;
}
Inventory Inventory::operator+(const Inventory &other) const
{
    Inventory result;

	// Current
    for (const auto& item : this->items) {
        result.add_item(item);
    }

	// Other
    for (const auto& item : other.items) {
        result.add_item(item);
    }

    result.currency = this->currency + other.currency;

    return result;
}
void Inventory::add_item(shared_ptr<Item> item) {
	items.push_back(item);
	sort(items.begin(), items.end());
}
void Inventory::remove_item(shared_ptr<Item> item) {
	for (int i = items.size() - 1; i >= 0; i--)
	{
		if (item == items.at(i)) 
		{
			items.erase(items.begin() + i);
			break;
		}
	}
}

