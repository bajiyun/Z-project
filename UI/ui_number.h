#pragma once

#include "game_object.h"

class CUiNumber :public CGameObject
{
private:
	//D3DXVECTOR3 m_Position;
	//D3DXVECTOR3 m_Rotation;
	//D3DXVECTOR3 m_Scale;

	static ID3D11Buffer* m_VertexBuffer;
	static ID3D11ShaderResourceView* m_Texture;

	int m_Count;
	D3DXVECTOR2 number_Position;
public:
	CUiNumber() {}
	~CUiNumber() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Draw(D3DXVECTOR2 Position, int number);
	void SetPositionAndNumber(D3DXVECTOR2 Position, int number) { number_Position = Position; m_Count = number; }
	void SetPosition(D3DXVECTOR2 Position) { number_Position = Position; }
	void SetNumber(int number) { m_Count = number; }
};