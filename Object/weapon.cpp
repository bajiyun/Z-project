//ライフルオブジェクト
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "model.h"
#include "bullet.h"
#include "player.h"
#include "scene.h"
#include "enemy.h"
#include "explosion.h"
#include "weapon.h"

class CModel* CWeapon::m_Model;

void CWeapon::Init()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\weapon.obj");
	m_Position = D3DXVECTOR3(-95.0f, 140.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	CRenderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "pixelLightingVS.cso");
	CRenderer::CreatePixelShader(&m_PixelShader, "pixelLightingPS.cso");

}

void CWeapon::Uninit()
{
	m_Model->Unload();
	delete m_Model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void CWeapon::Update()
{
	CPlayer* player = CManager::GetScene()->GetGameObject<CPlayer>(1);

	int state = player->GetState();

	if (state == 0 || state == 1)//プレイヤーが待機状況に合わせて位置を変更
	{
		m_Position.z = 5.0f;
		m_Rotation.y = 0.4f;
	}
	else
	{
		m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

void CWeapon::Draw()
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

	CPlayer* player = CManager::GetScene()->GetGameObject<CPlayer>(1);
	D3DMATRIX matrix = player->GetPlayerHandBone();

	world = scale * rot * trans * matrix;

	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}