#pragma once

#include "game_object.h"

class CFire :public CGameObject
{
private:
	//D3DXVECTOR3 m_Position;
	//D3DXVECTOR3 m_Rotation;
	//D3DXVECTOR3 m_Scale;

	static ID3D11Buffer* m_VertexBuffer;
	static ID3D11ShaderResourceView* m_Texture;

	int m_Count;
public:
	CFire() {}
	~CFire() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};