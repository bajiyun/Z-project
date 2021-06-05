#pragma once

#include "game_object.h"

class CMeshField :public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;

	ID3D11ShaderResourceView* m_Texture = NULL;
	ID3D11ShaderResourceView*   m_TextureNormal = NULL;
	ID3D11ShaderResourceView*   m_TextureDisplacement = NULL;

	VERTEX_3D m_Vertex[21][21];

public:
	CMeshField() {}
	~CMeshField() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	float GetHeight(D3DXVECTOR3 Position);
};