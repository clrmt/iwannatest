#pragma once
#include "Sprite.h"
#include "Killer.h"

// �� ���� �Ҵ�
class SpriteManager {
public:

	bool allocated;

	static Sprite kid;
	static Sprite block;
	static Sprite killer[Killer::_killerType_total];

	SpriteManager();
	~SpriteManager();
	void allocate();
	void free();
};

