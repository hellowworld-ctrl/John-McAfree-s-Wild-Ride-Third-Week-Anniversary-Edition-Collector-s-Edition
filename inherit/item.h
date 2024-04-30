#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
	Item(std::string name);
	// Rule of three
	Item(const Item &other) = delete;
	Item& operator=(const Item &other) = delete;
	~Item() = default;

	// Getters
	virtual std::string get_name() const = 0;
private:
	std::string name;
};

#endif
