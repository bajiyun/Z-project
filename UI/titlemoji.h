#pragma once

#include "game_object.h"

class CTMoji :public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	float alf;
public:
	CTMoji() {}
	~CTMoji() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void alfplus() { alf += 0.1f; }
	float getalf() { return alf; }
};