#pragma once

#include "game_object.h"

class CDead :public CGameObject
{
private:
	static ID3D11Buffer* m_VertexBuffer;
	static ID3D11ShaderResourceView* m_Texture;

public:
	CDead() {}
	~CDead() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};