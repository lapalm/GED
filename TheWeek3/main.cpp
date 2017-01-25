#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
// Instead of importing the entire std namespace, we can be
// specific about which std library classes and objects are to be included:
using std::string;
using std::cout;
using std::endl;
using std::cin;


// Abstract base class: no implementation
class AbstractNPC {
public:
	virtual ~AbstractNPC() {};
	virtual void render() = 0;
	virtual int getMana() = 0;
	virtual int getHealth() = 0;
};

// NPC implements AbstractNPC - all methods defined inline
class NPC : public AbstractNPC {
protected:
	int health, mana;
private:
	string name;
public:
	NPC(string basename, int mana, int health) { name.assign(basename); this->mana = mana; this->health = health;} // assign is a string function
	NPC(char * basename, int mana, int health) { name.assign(basename); this->mana = mana; this->health = health; } // to set string contents
	virtual ~NPC() { cout << "Deleting NPC Object: "+ name << endl; };
	void render() { cout << name; };
	int getMana();
	int getHealth();
};

// NPCDecorator implements AbstractNPC
class NPCDecorator : public AbstractNPC {
private:
	AbstractNPC * npc; 
	int health, mana;
public:
	NPCDecorator(AbstractNPC *n) { npc = n; }
	virtual ~NPCDecorator() { delete npc; };
	void render() { npc->render(); } // delegate render to npc data member
	int getMana() { return npc->getMana(); };
	int getHealth() { return npc->getHealth(); };
};

// Elite, Captain and Shaman are all types of NPCDecorator
class Elite : public NPCDecorator {
public:
	Elite(AbstractNPC *n) : NPCDecorator(n) { }
	virtual ~Elite() { cout << "Deleting Elite Decorator" << endl; };
	void render() {
		cout << "Elite "; // render special features
		NPCDecorator::render(); // delegate to base class
	}
	
	int getMana() {
		return NPCDecorator::getMana() + 20;
	}

	int getHealth() {
		return NPCDecorator::getHealth() + 20;
	}
};

class Captain : public NPCDecorator {
public:
	Captain(AbstractNPC *n) : NPCDecorator(n) { }
	virtual ~Captain() { cout << "Deleting Captain Decorator" << endl; };
	void render() {
		cout << "Captain "; // render special features
		NPCDecorator::render(); // delegate to base class
	}

	int getMana() {
		return NPCDecorator::getMana() + 0;
	}

	int getHealth() {
		return NPCDecorator::getHealth() + 40;
	}
};

class Shaman : public NPCDecorator {
public:
	Shaman(AbstractNPC *n) : NPCDecorator(n) { }
	virtual ~Shaman() { cout << "Deleting Shaman Decorator" << endl; };
	void render() {
		NPCDecorator::render(); // delegate to base class
		cout << " Shaman "; // render special features *after* base
	}
	int getMana() {
		return NPCDecorator::getMana() + 60;
	}

	int getHealth() {
		return NPCDecorator::getHealth() + 0;
	}
};

// Program entry point
int main(int argc, char **argv)
{
	srand(time(NULL));
	AbstractNPC *monsterArray[10];
	int r;
	for (int i = 0; i < 10; i++) {
		r = rand() % 6;
		NPC *base;
		switch (r) {
		case 0:
			base = new NPC("Ork", 10, 40);
			break;
		case 1:
			base = new NPC("Goblim", 25, 25);
			break;
		case 2:
			base = new NPC("Troll", 10, 100);
			break;
		case 3:
			base = new NPC("Bandit", 10, 30);
			break;
		case 4:
			base = new NPC("Brigand", 20, 50);
			break;
		case 5:
			base = new NPC("Master of All things Breaker of none ", 1500000, 15000000);
			break;
		default:
			base = new NPC("Its a you", 0, 1);
			break;
		}

		r = rand() % 3;
		AbstractNPC *firstClass;
		switch(r) {
		case 0:
			firstClass = new Elite(base);
			break;
		case 1:
			firstClass = new Shaman(base);
			break;
		case 2:
			firstClass = new Captain(base);
			break;
		}
		r = rand() % 2;
		if (r == 1) {
			AbstractNPC *secondClass;
			switch (r) {
			case 0:
				secondClass = new Elite(firstClass);
				break;
			case 1:
				secondClass = new Shaman(firstClass);
				break;
			case 2:
				secondClass = new Captain(firstClass);
				break;
			}

			monsterArray[i] = secondClass;
		}
		else {
			monsterArray[i] = firstClass;
		}
		
	}
	for (int i = 0; i < 10; i++) {
		monsterArray[i]->render();
		cout << " Health: "<< monsterArray[i]->getHealth();
		cout << " Mana: " << monsterArray[i]->getMana();
		cout << endl;
	}

	for (int i = 0; i < 10; i++) {
		cout << endl;
		delete monsterArray[i];
	}

	cin.get();
	return 0;
}

int NPC::getMana()
{
	return this->mana;
}

int NPC::getHealth()
{
	return this->health;
}
