#pragma once
#include "Entity.h"
#include "Killer.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")

class Killer : public Entity {

public:
	const static int _killerType_null = 0;
	const static int _killerType_apple = 1;
	const static int _killerType_spikeUp = 2;
	const static int _killerType_spikeDown = 3;
	const static int _killerType_spikeLeft = 4;
	const static int _killerType_spikeRight = 5;

	const static int _killerType_total = 6;

};
