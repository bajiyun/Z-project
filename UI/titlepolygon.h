#pragma once

#include "game_object.h"

class CTPolygon :public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

public:
	CTPolygon() {}
	~CTPolygon() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
};