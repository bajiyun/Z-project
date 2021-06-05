#pragma once
#include "game_object.h"

class CTree :public CGameObject
{
private:

	static class CModel* m_Model;

public:
	CTree() {}
	~CTree() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};