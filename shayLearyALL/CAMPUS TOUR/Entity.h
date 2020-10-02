//Entity class - Parent class of player and enemy, containing increments, setters and getters for health
//Version 1

class Entity
{
public:
	Entity();

	int getHealth();

	int getShields();

	void setHealth(int h);

	void setShields(int s);

	void incrementHealth();

	void incrementShields();

	void decreaseHealth();

	void decreaseShields();

protected:

	int health;
	int shields;
};

