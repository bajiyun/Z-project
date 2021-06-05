#pragma once

#include "game_object.h"

class CPolygon :public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

public:
	CPolygon() {}
	~CPolygon() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
};