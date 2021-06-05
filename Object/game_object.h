//ゲームオブジェクト
#pragma once

class CGameObject
{
protected:
	bool m_Destroy = false;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

public:
	CGameObject() {}
	virtual ~CGameObject() {}
	virtual void Init() {};//仮想関数
	virtual void Uninit() = 0;//純粹仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;

	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }

	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._11;
		vx.y = world._12;
		vx.z = world._13;

		return vx * 0.5f;
	}

	D3DXVECTOR3 GetObbZ()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vz;
		vz.x = world._31;
		vz.y = world._32;
		vz.z = world._33;

		return vz * 0.5f;
	}

	D3DXVECTOR3 GetObbY()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vy;
		vy.x = world._21;
		vy.y = world._22;
		vy.z = world._23;

		return vy * 0.5f;
	}

	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }
	void SetDestroy() { m_Destroy = true; }

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Obb_Collision(D3DXVECTOR3 Position)//OBB衝突判定
	{
		D3DXVECTOR3 direction = Position - m_Position;

		D3DXVECTOR3 obbx, obbz, obby;
		float obbLenx, obbLenz, obbLeny;

		obbx = GetObbX();
		obbLenx = D3DXVec3Length(&obbx);
		obbx /= obbLenx;

		obbz = GetObbZ();
		obbLenz = D3DXVec3Length(&obbz);
		obbz /= obbLenz;

		obby = GetObbY();
		obbLeny = D3DXVec3Length(&obby);
		obby /= obbLeny;

		float lenX, lenZ, lenY;
		lenX = D3DXVec3Dot(&obbx, &direction);
		lenZ = D3DXVec3Dot(&obbz, &direction);
		lenY = D3DXVec3Dot(&obby, &direction);

		if (fabs(lenX) < obbLenx && fabs(lenZ) < obbLenz && fabs(lenY) < obbLeny)
		{
			return true;
		}
	}
};
