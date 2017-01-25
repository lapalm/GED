#include <string>
#include <iostream>
// Instead of importing the entire std namespace, we can be
// specific about which std library classes and objects are to be included:
using std::string;
using std::cout;
using std::endl;
using std::cin;


// Abstract base class: no implementation
class AbstractNPC {
public:
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
	void render() { npc->render(); } // delegate render to npc data member
	int getMana() { return npc->getMana(); };
	int getHealth() { return npc->getHealth(); };
};

// Elite, Captain and Shaman are all types of NPCDecorator
class Elite : public NPCDecorator {
public:
	Elite(AbstractNPC *n) : NPCDecorator(n) { }
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
	AbstractNPC *goblin1 = new Elite(new Shaman(new NPC("Goblin", 25, 25)));
	AbstractNPC *orc1 = new Elite(new Captain(new NPC("Orc", 10, 40)));
	AbstractNPC *orc2 = new Elite(new NPC("Orc", 10, 40));
	AbstractNPC *troll1 = new Shaman(new NPC("Troll",10, 100));
	AbstractNPC *bandit1 = new Elite(new NPC("Bandit", 10 ,30));
	AbstractNPC *brigand1 = new Captain(new NPC("Brigand", 20 ,50));
	goblin1->render(); cout << " Health: " << goblin1->getHealth() << " Mana: " << goblin1->getMana(); cout << endl;
	orc1->render(); cout << " Health: " << orc1->getHealth() << " Mana: " << orc1->getMana(); cout << endl;
	orc2->render(); cout << " Health: " << orc2->getHealth() << " Mana: " << orc2->getMana(); cout << endl;
	troll1->render(); cout << " Health: " << troll1->getHealth() << " Mana: " << troll1->getMana(); cout << endl;
	bandit1->render(); cout << " Health: " << bandit1->getHealth() << " Mana: " << bandit1->getMana(); cout << endl;
	brigand1->render(); cout << " Health: " << brigand1->getHealth() << " Mana: " << brigand1->getMana(); cout << endl;


	delete goblin1;
	delete orc1;
	delete orc2;
	delete troll1;
	delete bandit1;
	delete brigand1;

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
