#pragma once
#include "game_object.h"

class CBullet :public CGameObject
{
private:

	static class CModel* m_Model;

	D3DXVECTOR3 m_Forward;

public:

	CBullet() {}
	~CBullet() {}

	static void Load();
	static void Unload();

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