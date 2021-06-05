#pragma once

#include "game_object.h"
class CCamera :public CGameObject
{
private:

	D3DXVECTOR3 m_Target;

	D3DXMATRIX m_ViewMatrix;

	D3DXMATRIX m_ProjectMatrix;

	float m_CameraX;
	float m_CameraY;

public:
	CCamera() {}
	~CCamera() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool CheckView(D3DXVECTOR3 TargetPosition);

	bool CheckView(D3DXVECTOR3 TargetPosition, float r);

	D3DXMATRIX GetViewMatrix()
	{
		return m_ViewMatrix;
	}
};