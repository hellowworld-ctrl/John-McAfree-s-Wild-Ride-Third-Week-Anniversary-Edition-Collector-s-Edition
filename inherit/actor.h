#ifndef ACTOR_H
#define ACTOR_H

#include <string>

class Actor {
public:
	Actor(std::string name, int max_health);
	
	// Rule of three
	Actor(const Actor &other) = delete;
	Actor& operator=(const Actor &other) = delete;
	~Actor() = default;

	// Getters
	virtual std::string get_name() const = 0;
	virtual int get_max_health() const = 0;
	virtual int get_current_health() const = 0;

	// Setters
	virtual void set_max_health(int max_health) = 0;
	virtual void set_current_health(int health) = 0;
private:
	std::string name;
	int max_health;
	int current_health;
};

#endif
