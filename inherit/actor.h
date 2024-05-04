#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <utility>
#include <memory>
#include "inventory.h"

// Fighter: Twice the power
// Defender: Twice the block
// Healer: Passive regeneration
enum Special
{
	Fighter = 0,
	Defender = 1,
	Healer = 2,
};

// Invariants:
// 1. max_special must equal enum Special maximum value

class Actor 
{
public:
	static const int max_special = 2;

	Actor(enum Special special, std::string name, int power, int max_health, int speed);
	// Rule of three
	Actor(const Actor &other) = delete;
	Actor& operator=(const Actor &other) = delete;
	~Actor() = default;
	
	// Functions
	std::pair<std::string, bool> attack(std::shared_ptr<Actor> target);

	// Getters
	virtual std::string get_special_name() const = 0;
	virtual std::string get_title() const = 0;
	virtual std::string get_name() const = 0;
	enum Tier get_tier() const;
	const std::shared_ptr<Weapon> get_weapon();
	const std::shared_ptr<Apparel> get_apparel();

	int get_power() const { return power; }
	int get_health() const { return health; }
	int get_max_health() const { return max_health; }
	int get_speed() const { return speed; }
	enum Special get_special() const { return special; }

	// Setters
	void set_health(int health);
	void set_max_health(int max_health);
	void set_weapon(std::shared_ptr<Weapon>& weapon);
	void set_apparel(std::shared_ptr<Apparel>& apparel);
protected:
	enum Special special;
	std::string name;
	int power;
	int max_health;
	int health;
	int speed;

	std::shared_ptr<Weapon> weapon;
	std::shared_ptr<Apparel> apparel;
};

class Hero : public Actor
{
public:
	Hero(enum Special special, std::string name, int power, int max_health, int speed);

	// Getters
	std::string get_special_name() const override;
	std::string get_title() const override;

	std::string get_name() const override { return name; }
private:
};

class Monster : public Actor
{
public:
	Monster(enum Special special, std::string name, int power, int max_health, int speed);

	// Getters
	std::string get_special_name() const override;
	std::string get_title() const override;

	std::string get_name() const override { return name; }
private:
};

#endif
