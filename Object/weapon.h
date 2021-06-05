#pragma once
#include "game_object.h"

class CWeapon :public CGameObject
{
private:

	static class CModel* m_Model;

	D3DXVECTOR3 m_Forward;


public:

	CWeapon() {}
	~CWeapon() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetForward(D3DXVECTOR3 position, D3DXVECTOR3 forward)
	{
		m_Position = position;
		m_Forward = forward;
	}
};