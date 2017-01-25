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
};

// NPC implements AbstractNPC - all methods defined inline
class NPC : public AbstractNPC {
private:
	string name;
public:
	NPC(string basename) { name.assign(basename); } // assign is a string function
	NPC(char * basename) { name.assign(basename); } // to set string contents
	void render() { cout << name; }
};

// NPCDecorator implements AbstractNPC
class NPCDecorator : public AbstractNPC {
private:
	AbstractNPC * npc;
public:
	NPCDecorator(AbstractNPC *n) { npc = n; }
	void render() { npc->render(); } // delegate render to npc data member
};

// Elite, Captain and Shaman are all types of NPCDecorator
class Elite : public NPCDecorator {
public:
	Elite(AbstractNPC *n) : NPCDecorator(n) { }
	void render() {
		cout << "Elite "; // render special features
		NPCDecorator::render(); // delegate to base class
	}
};

class Captain : public NPCDecorator {
public:
	Captain(AbstractNPC *n) : NPCDecorator(n) { }
	void render() {
		cout << "Captain "; // render special features
		NPCDecorator::render(); // delegate to base class
	}
};

class Shaman : public NPCDecorator {
public:
	Shaman(AbstractNPC *n) : NPCDecorator(n) { }
	void render() {
		NPCDecorator::render(); // delegate to base class
		cout << " Shaman "; // render special features *after* base
	}
};

// Program entry point
int main(int argc, char **argv)
{
	AbstractNPC *goblin1 = new Elite(new Shaman(new NPC("Goblin")));
	AbstractNPC *orc1 = new Elite(new Captain(new NPC("Orc")));
	AbstractNPC *troll1 = new Shaman(new NPC("Troll"));
	AbstractNPC *bandit1 = new Elite(new NPC("Bandit"));
	AbstractNPC *brigand1 = new Captain(new NPC("Brigand"));
	goblin1->render(); cout << endl;
	orc1->render(); cout << endl;
	troll1->render(); cout << endl;
	bandit1->render(); cout << endl;
	brigand1->render(); cout << endl;


	delete goblin1;
	delete orc1;
	delete troll1;
	delete bandit1;
	delete brigand1;

	cin.get();
	return 0;
}




