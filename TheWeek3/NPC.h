#pragma once
#include <iostream>
#include <string>
using namespace std;
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
	NPC(string basename, int mana, int health) { name.assign(basename); this->mana = mana; this->health = health; } // assign is a string function
	NPC(char * basename, int mana, int health) { name.assign(basename); this->mana = mana; this->health = health; } // to set string contents
	virtual ~NPC() { cout << "Deleting NPC Object: " + name << endl; };
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


int NPC::getMana()
{
	return this->mana;
}

int NPC::getHealth()
{
	return this->health;
}