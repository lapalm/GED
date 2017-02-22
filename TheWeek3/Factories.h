#pragma 
#include <string>
#include "NPC.h"
using namespace std;
class RTSUnit: public NPCDecorator
{
public:
	RTSUnit(char *fn, char*theType, AbstractNPC* n) :NPCDecorator(n) {
		strcpy_s(name, fn);
	};
	virtual void Start() = 0;
	virtual void Stop() = 0;
	char *GetName(){
		return name;
	}
	virtual ~RTSUnit() {};
private:
	char name[20];
};
/*
class AbstractFactory {
public:
	AbstractFactory() {};
	virtual RTSUnit * CreateUnit
};
*/

class Factory
{
public:
	Factory() {};
	virtual ~Factory() {};
	virtual RTSUnit * CreateUnit(char*, char*, AbstractNPC*) = 0;
	virtual void NewUnit(char*name, char*theType, AbstractNPC* npc)=0;
	virtual void StartUnit()=0;
	virtual void ReportUnits()=0;

};

class MeleeUnit : public RTSUnit {
public:
	MeleeUnit(char *fn, char *theType, AbstractNPC* n) : RTSUnit(fn, theType, n){};
	void Start() {
		render();
		cout << "	MeleeUnit:Start()" << endl;
	}
	void Stop() {
		cout << "	MeleeUnit:Stop()" << endl;
	}
};

class RangeUnit : public RTSUnit{
public:
	RangeUnit(char *fn, char *theType, AbstractNPC* n) : RTSUnit(fn, theType, n) {};
	void Start() {
		render();
		cout << "	RangeUnit:Start()" << endl;
	}
	void Stop() {
		cout << "	RangeUnit:Stop()" << endl;
	}
};

class JarJar : public RTSUnit{
public:
	JarJar(char *fn, char *theType, AbstractNPC* n) : RTSUnit(fn, theType, n) {};
	void Start() {
		render();
		cout << "	JarJarTheUnit:Start()" << endl;
	}
	void Stop() {
		cout << "	JarJarTheUnit:Stop()" << endl;
	}
};


class FederationFactory: public Factory {
public:
	FederationFactory() {
		cout << "FederationFactory: ctor" << endl;
	}
	void NewUnit(char*name, char*theType, AbstractNPC* npc) {
		cout << "Factory: NewUnit()" << endl;
		/* Framework calls the "hole" reserved for client customization */
		_units = CreateUnit(name, theType, npc);
		_units->Start();
	}
	/* Client defines Framework's "hole" */
	RTSUnit *CreateUnit(char *fn, char *theType, AbstractNPC* npc) {
		cout << " FederationFactory: CreateUnit()" << endl;
		if (theType == "melee")
		{
			return new MeleeUnit(fn, theType, npc);
		} else if (theType == "range")
		{
			return new RangeUnit(fn, theType, npc);
		}
	}
	void StartUnit() {};
	void ReportUnits() {};
private:
	RTSUnit* _units;

};

class RepublicFactory : public Factory {
public:
	RepublicFactory() {
		cout << "RepublicFactory: ctor" << endl;
	}
	void NewUnit(char*name, char*theType, AbstractNPC* npc) {
		cout << "Factory: NewUnit()" << endl;
		/* Framework calls the "hole" reserved for client customization */
		_units = CreateUnit(name, theType, npc);
		_units->Start();
	}
	/* Client defines Framework's "hole" */
	RTSUnit *CreateUnit(char *fn, char *theType, AbstractNPC* npc) {
		cout << " RepublicFactory: CreateUnit()" << endl;
		if (theType == "melee")
		{
			return new MeleeUnit(fn, theType, npc);
		}
		else if (theType == "range")
		{
			return new RangeUnit(fn, theType, npc);

		}
		else if (theType == "jarjar")
		{
			return new JarJar(fn, theType, npc);
		}
	}
	void StartUnit() {};
	void ReportUnits() {};
private:
	RTSUnit* _units;

};
