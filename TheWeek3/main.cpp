
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Factories.h"
#include "NPC.h"
// Instead of importing the entire std namespace, we can be
// specific about which std library classes and objects are to be included:
using namespace std;



// Program entry point
int main(int argc, char **argv)
{
	/* Client's customization of the Framework : determine to call which function*/
	Factory* factories[2];
	factories[0] = new FederationFactory;
	factories[1] = new RepublicFactory;


	NPCDecorator* doggo = new Elite(new NPC("Doggo", 1, 10));
	NPCDecorator* joggo = new Shaman(new NPC("Joggo", 1, 10));
	NPCDecorator* SITH_LORD = new Shaman(new Elite(new NPC("Sith Lord", 1, 10)));
	factories[0]->NewUnit("Federation Melee", "melee", doggo);
	factories[0]->NewUnit("Federation Range", "range", joggo);
	factories[1]->NewUnit("JarJar", "jarjar",SITH_LORD);

	cin.get();
	delete doggo;
	delete joggo;
	/*NO ONE CAN DELETE SITH LORD. ITS ALWAYS IN MEMEPORYRYRSKJA*/
	delete SITH_LORD;
	delete factories[0];
	delete factories[1];
	cin.get();
	return 0;
}
