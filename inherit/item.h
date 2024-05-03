#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "tier.h"

class Item
{
public:
	Item(std::string name);
	// Rule of three
	Item(const Item &other) = delete;
	Item& operator=(const Item &other) = delete;
	~Item() = default;

	bool operator>(const Item &other) const;

	virtual std::string get_title() const = 0;
	virtual int get_value() const = 0;
protected:
	std::string name;
	
	virtual enum Tier get_tier() const = 0;
	virtual std::string get_name() const = 0;
};

class Weapon : public Item
{
public:
	Weapon(std::string name, int damage);

	std::string get_title() const override { return Stats::get_tier_name(get_tier()) + " " + get_name(); }
	int get_value() const override { return damage; }
	int get_damage() const { return damage; }
private:
	int damage;
	
	enum Tier get_tier() const override;
	std::string get_name() const override { return name; }
};

class Potion : public Item
{
public:
	Potion(std::string name, int magic);

	std::string get_title() const override { return Stats::get_tier_name(get_tier()) + " " + get_name(); }
	int get_value() const override { return magic; }
	int get_magic() const { return magic; }
private:
	int magic;
	
	enum Tier get_tier() const override;
	std::string get_name() const override { return name; }
};

class Apparel : public Item
{
public:
	Apparel(std::string name, int block);

	std::string get_title() const override { return Stats::get_tier_name(get_tier()) + " " + get_name(); }
	int get_value() const override { return block; }
	int get_block() const { return block; }
private:
	int block;
	
	enum Tier get_tier() const override;
	std::string get_name() const override { return name; }
};

#endif
