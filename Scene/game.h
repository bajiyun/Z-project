#pragma once

#include "scene.h"

class CGame :public CScene
{
private:
	int deadframe;
public:
	void Init();
	void Uninit();
	void Update();
};
