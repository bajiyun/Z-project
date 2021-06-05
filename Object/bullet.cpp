//弾丸オブジェクト
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "model.h"
#include "bullet.h"
#include "scene.h"
#include "enemy.h"
#include "explosion.h"

class CModel* CBullet::m_Model;

void CBullet::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\cube.obj");
}

void CBullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CBullet::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.002f, 0.002f, 0.002f);
	m_Forward = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CRenderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexShader.cso");
	CRenderer::CreatePixelShader(&m_PixelShader, "pixelShader.cso");
}

void CBullet::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void CBullet::Update()
{
	m_Position += m_Forward * 0.3f;//弾丸速度

	CScene* scene = CManager::GetScene();
	if (m_Position.x > 100.0f || m_Position.z > 100.0f || m_Position.x < -100.0f || m_Position.z < -100.0f)//画面外に行った弾丸を消す
	{
		scene->AddGameObject<CExplosion>(1)->SetPosition(m_Position);
		SetDestroy();
	}

	std::vector<CEnemy*> enemyList = scene->GetGameObjects<CEnemy>(1);

	for (CEnemy* enemy : enemyList)
	{
		//OBB判定用
		/*
		if (enemy->Obb_Collision(m_Position))
		{
			scene->AddGameObject<CExplosion>(1)->SetPosition(m_Position);
			enemy->SetDestroy();
			SetDestroy();
			return;
		}
		*/

		D3DXVECTOR3 enemyPosition = enemy->GetPosition();

		D3DXVECTOR3 direction = m_Position - D3DXVECTOR3(enemyPosition.x, enemyPosition.y + 1.5f, enemyPosition.z);
		bool live = enemy->GetLive();

		//円形判定
		float length = D3DXVec3Length(&direction);
		if (length < 1.0f && live)
		{
			scene->AddGameObject<CExplosion>(1)->SetPosition(D3DXVECTOR3(m_Position.x, m_Position.y + 0.5f, m_Position.z));
			enemy->GetAttack();
			SetDestroy();
			return;
		}
	}

	//OBB判定用
/*　
	std::vector<CEnemy*> enemyList = scene->GetGameObjects<CEnemy>(1);

	for (CEnemy* enemy : enemyList)
	{
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();
		D3DXVECTOR3 direction = m_Position - enemyPosition;

		//float length = D3DXVec3Length(&direction);
		//if (length < 2.0f)
		//{
		//	//scene->AddGameObject<CExplosion>(1)->SetPosition(m_Position);
		//	//enemy->SetDestroy();
		//	SetDestroy();
		//	return;
		//}

		D3DXVECTOR3 obbx, obbz,obby;
		float obbLenx, obbLenz,obbLeny;

		obbx = enemy->GetObbX();
		obbLenx = D3DXVec3Length(&obbx);
		obbx /= obbLenx;

		obbz = enemy->GetObbZ();
		obbLenz = D3DXVec3Length(&obbz);
		obbz /= obbLenz;

		obby = enemy->GetObbY();
		obbLeny = D3DXVec3Length(&obby);
		obby /= obbLeny;

		float lenX, lenZ,lenY;
		lenX = D3DXVec3Dot(&obbx, &direction);
		lenZ = D3DXVec3Dot(&obbz, &direction);
		lenY = D3DXVec3Dot(&obby, &direction);

		if (fabs(lenX) < obbLenx && fabs(lenZ) < obbLenz && fabs(lenY) < obbLeny)
		{
			//enemy->SetDestroy();
			SetDestroy();
			return;
		}
	}
	*/
}

void CBullet::Draw()
{
	//入力レイアウト設定
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//シェーダー設定
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}