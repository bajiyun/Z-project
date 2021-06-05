#pragma once

#include "game_object.h"

class CRedRec :public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;
	bool key;
	int frame;
public:
	CRedRec() {}
	~CRedRec() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
};