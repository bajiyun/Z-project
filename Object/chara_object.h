//キャラオブジェクト
#pragma once

#include "game_object.h"
#include "model.h"
#include "animation_model.h"
#include "d3dx9math.h"

class CCharacterObject :public CGameObject
{
protected:

	D3DXQUATERNION m_Quaternion;

public:
	CCharacterObject() {}
	virtual ~CCharacterObject() {}
	virtual void Init() {};//仮想関数
	virtual void Uninit() = 0;//純粹仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;

	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}

	D3DXVECTOR3 GetUp()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXVECTOR3 up;
		up.x = rot._21;
		up.y = rot._22;
		up.z = rot._23;

		return up;
	}
};