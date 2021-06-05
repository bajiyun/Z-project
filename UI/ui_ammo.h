#pragma once
#include "game_object.h"

class CUiAmmo :public CGameObject
{
private:

	static class CUiNumber* number1;
	static class CUiNumber* number2;
	static class CUiNumber* number3;
	int ammo;
	int hp;

public:
	CUiAmmo() {}
	~CUiAmmo() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};