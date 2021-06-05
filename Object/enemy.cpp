//ゾンビオブジェクト
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "model.h"
#include "meshField.h"
#include "enemy.h"
#include "explosion.h"
#include "scene.h"

class CAnimationModel* CEnemy::m_Model;
class CAnimationModel* CEnemy::m_Model1;
class CAnimationModel* CEnemy::m_Model2;

void CEnemy::Load()
{
	m_Model = new CAnimationModel();
	m_Model1 = new CAnimationModel();
	m_Model2 = new CAnimationModel();

	m_Model->Load("asset\\model\\zombie\\Zombie1_Idle.fbx");
	m_Model->LoadAnimation("asset\\model\\zombie\\Zombie1_Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\zombie\\Zombie1_Walking.fbx", "Run");
	m_Model->LoadAnimation("asset\\model\\zombie\\Zombie1_Attack.fbx", "Attack");
	m_Model->LoadAnimation("asset\\model\\zombie\\Zombie1_Dying.fbx", "Dying");

	m_Model1->Load("asset\\model\\zombie\\Zombie2_Idle.fbx");
	m_Model1->LoadAnimation("asset\\model\\zombie\\Zombie2_Idle.fbx", "Idle");
	m_Model1->LoadAnimation("asset\\model\\zombie\\Zombie2_Walking.fbx", "Run");
	m_Model1->LoadAnimation("asset\\model\\zombie\\Zombie2_Attack.fbx", "Attack");
	m_Model1->LoadAnimation("asset\\model\\zombie\\Zombie2_Dying.fbx", "Dying");

	m_Model2->Load("asset\\model\\zombie\\Zombie3_Idle.fbx");
	m_Model2->LoadAnimation("asset\\model\\zombie\\Zombie3_Idle.fbx", "Idle");
	m_Model2->LoadAnimation("asset\\model\\zombie\\Zombie3_Walking.fbx", "Run");
	m_Model2->LoadAnimation("asset\\model\\zombie\\Zombie3_Attack.fbx", "Attack");
	m_Model2->LoadAnimation("asset\\model\\zombie\\Zombie3_Dying.fbx", "Dying");
}

void CEnemy::Unload()
{
	m_Model->Unload();
	delete m_Model;
	m_Model1->Unload();
	delete m_Model1;
	m_Model2->Unload();
	delete m_Model2;
}

void CEnemy::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 180.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);

	D3DXQuaternionIdentity(&m_Quaternion);

	CRenderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "pixelLightingVS.cso");
	CRenderer::CreatePixelShader(&m_PixelShader, "pixelLightingPS.cso");

	m_FrameControl = true;
	m_Alive = true;
	m_EnemyHp = 5;
}

void CEnemy::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void CEnemy::Update()
{
	m_Frame++;

	CPlayer* player = CManager::GetScene()->GetGameObject<CPlayer>(1);
	D3DXVECTOR3 p_Pos = player->GetPosition();
	D3DXVECTOR3 p_Rot = player->GetForward();
	D3DXVECTOR3 direction = p_Pos - m_Position;
	D3DXVECTOR3 n_Direction;

	D3DXVec3Normalize(&n_Direction, &direction);
	float l_direction = D3DXVec3Length(&direction);

	D3DXVECTOR3 A_Direction = (m_Position - GetForward() * 0.8f) - p_Pos;
	float length = D3DXVec3Length(&A_Direction);

	if (m_EnemyHp <= 0)
	{
		m_Alive = false;
	}

	if (m_Type == 0)
	{
		if (m_Alive)
		{
			if (l_direction >= 1.8f && m_FrameControl)
			{
				m_Frame = 0;
				m_AttackFrame = 0;
				m_RunFrame++;
				m_Model->Update("Run", m_RunFrame);

				float angle = atan2(n_Direction.x, n_Direction.z);

				m_Position += n_Direction * 0.01f;
				m_Rotation.y = angle + 9.5f;
			}
			if (l_direction <= 1.8f || !m_FrameControl)//攻撃アニメーションちゃんとループさせる
			{
				m_Frame = 0;
				m_RunFrame = 0;
				m_AttackFrame++;
				m_Model->Update("Attack", m_AttackFrame);

				if (m_AttackFrame >= 200)
					m_AttackFrame = 10;

				if (m_AttackFrame == 110)
				{
					CScene* scene = CManager::GetScene();

					if (length < 1.5f)
					{
						scene->AddGameObject<CExplosion>(1)->SetPosition(p_Pos + D3DXVECTOR3(0.0f, 1.9f, 0.0f));
						player->LostHp();
					}
				}

				if (20 <= m_AttackFrame <= 169)
					m_FrameControl = false;
				if (m_AttackFrame > 170)
					m_FrameControl = true;
			}
		}
		if (!m_Alive)
		{
			m_Frame = 0;
			m_AttackFrame = 0;
			m_RunFrame = 0;
			m_DryingFrame++;
			m_Model->Update("Dying", m_DryingFrame);
			if (m_DryingFrame >= 150)
			{
				SetDestroy();
			}
		}
	}

	if (m_Type == 1)
	{
		if (m_Alive)
		{
			if (l_direction >= 1.8f && m_FrameControl)
			{
				m_Frame = 0;
				m_AttackFrame = 0;
				m_RunFrame++;
				m_Model1->Update("Run", m_RunFrame);

				float angle = atan2(n_Direction.x, n_Direction.z);

				m_Position += n_Direction * 0.01f;
				m_Rotation.y = angle + 9.5f;
			}
			if (l_direction <= 1.8f || !m_FrameControl)
			{
				m_Frame = 0;
				m_RunFrame = 0;
				m_AttackFrame++;
				m_Model1->Update("Attack", m_AttackFrame);

				if (m_AttackFrame >= 200)
					m_AttackFrame = 10;

				if (m_AttackFrame == 110)
				{
					CScene* scene = CManager::GetScene();

					if (length < 1.5f)
					{
						scene->AddGameObject<CExplosion>(1)->SetPosition(p_Pos + D3DXVECTOR3(0.0f, 1.9f, 0.0f));
						player->LostHp();
					}
				}

				if (20 <= m_AttackFrame <= 169)
					m_FrameControl = false;
				if (m_AttackFrame > 170)
					m_FrameControl = true;
			}
		}
		if (!m_Alive)
		{
			m_Frame = 0;
			m_AttackFrame = 0;
			m_RunFrame = 0;
			m_DryingFrame++;
			m_Model1->Update("Dying", m_DryingFrame);
			if (m_DryingFrame >= 150)
			{
				SetDestroy();
			}
		}
	}

	if (m_Type == 2)
	{
		if (m_Alive)
		{
			if (l_direction >= 1.8f && m_FrameControl)
			{
				m_Frame = 0;
				m_AttackFrame = 0;
				m_RunFrame++;
				m_Model2->Update("Run", m_RunFrame);

				float angle = atan2(n_Direction.x, n_Direction.z);

				m_Position += n_Direction * 0.01f;
				m_Rotation.y = angle + 9.5f;
			}
			if (l_direction <= 1.8f || !m_FrameControl)
			{
				m_Frame = 0;
				m_RunFrame = 0;
				m_AttackFrame++;
				m_Model2->Update("Attack", m_AttackFrame);

				if (m_AttackFrame >= 200)
					m_AttackFrame = 10;

				if (m_AttackFrame == 110)
				{
					CScene* scene = CManager::GetScene();

					if (length < 1.5f)
					{
						int p_hp = player->GetHp();
						if (p_hp >= 0)
						{
							scene->AddGameObject<CExplosion>(1)->SetPosition(p_Pos + D3DXVECTOR3(0.0f, 1.9f, 0.0f));
							player->LostHp();
						}
					}
				}

				if (20 <= m_AttackFrame <= 169)
					m_FrameControl = false;
				if (m_AttackFrame > 170)
					m_FrameControl = true;
			}
		}
		if (!m_Alive)
		{
			m_Frame = 0;
			m_AttackFrame = 0;
			m_RunFrame = 0;
			m_DryingFrame++;
			m_Model2->Update("Dying", m_DryingFrame);
			if (m_DryingFrame >= 150)
			{
				SetDestroy();
			}
		}
	}

	//meshfield との衝突判定
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);
}

void CEnemy::Draw()
{
	//入力レイアウト設定
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//シェーダー設定
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	CScene* scene = CManager::GetScene();
	CCamera* camera = scene->GetGameObject<CCamera>(0);

	float r = sqrtf(m_Scale.x * m_Scale.x + m_Scale.y * m_Scale.y + m_Scale.z * m_Scale.z);
	//if (!camera->CheckView(m_Position))
	//	return;

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	CRenderer::SetWorldMatrix(&world);

	if (m_Type == 0)
	{
		m_Model->Draw();
	}
	if (m_Type == 1)
	{
		m_Model1->Draw();
	}
	if (m_Type == 2)
	{
		m_Model2->Draw();
	}
}