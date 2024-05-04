#ifndef INVENTORY_H
#define INVENTORY_H

#include <memory>
#include <vector>
#include "../inherit/item.h"

class Inventory
{
public:
	Inventory();
	// Rule of three
	Inventory(const Inventory &other);
	Inventory& operator=(const Inventory &other);
	~Inventory() = default;

	Inventory operator+(const Inventory &other) const;
	
	// Functions
	void add_item(std::shared_ptr<Item> item);
	void remove_item(std::shared_ptr<Item> item);

	// Getters
	const std::vector<std::shared_ptr<Item>>& get_items() const { return items; }
	int get_currency() const { return currency; }

	// Setters
	void set_currency();
private:
	std::vector<std::shared_ptr<Item>> items;
	int currency;
};

#endif
