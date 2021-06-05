#pragma once

#include "game_object.h"

class CField :public CGameObject
{
private:

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;
	ID3D11ShaderResourceView*   m_TextureNormal = NULL;
	ID3D11ShaderResourceView*   m_TextureDisplacement = NULL;

public:
	CField() {}
	~CField() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};