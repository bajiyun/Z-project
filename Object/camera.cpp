//カメラオブジェクト
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "player.h"

void CCamera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -3.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 2.0f);

	m_CameraX = 0;
	m_CameraY = 0;
}

void CCamera::Uninit()
{
}
void CCamera::Update()
{
	if (CInput::GetKeyPress('L'))
	{
		m_CameraX += 0.1f;
	}
	if (CInput::GetKeyPress('J'))
	{
		m_CameraX -= 0.1f;
	}

	if (CInput::GetKeyPress('I'))
	{
		m_CameraY += 0.1f;
	}
	if (CInput::GetKeyPress('K'))
	{
		m_CameraY -= 0.1f;
	}
	CPlayer* player = CManager::GetScene()->GetGameObject<CPlayer>(1);
	m_Target = player->GetPosition() + D3DXVECTOR3(0.0f + m_CameraX, 3.0f + m_CameraY, 0.0f);//監視カメラのようにプレイヤーにフォロー
}
void CCamera::Draw()
{
	//ビユーマトリクス設定
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	CRenderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectMatrix);

	CRenderer::SetCameraPosition(m_Position);
}

bool CCamera::CheckView(D3DXVECTOR3 TargetPosition, float r)//視錐台カリング
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);//プロジェクション座標
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;

	v = TargetPosition - m_Position;

	v1 = wpos[0] - m_Position;
	v2 = wpos[2] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);

	float dis = D3DXVec3Dot(&n, &v);

	if (dis < 0.0f && fabs(dis) > r)
		return false;

	v1 = wpos[1] - m_Position;
	v2 = wpos[0] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);

	dis = D3DXVec3Dot(&n, &v);

	if (dis < 0.0f && fabs(dis) > r)
		return false;

	v1 = wpos[3] - m_Position;
	v2 = wpos[1] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);

	dis = D3DXVec3Dot(&n, &v);

	if (dis < 0.0f && fabs(dis) > r)
		return false;

	v1 = wpos[2] - m_Position;
	v2 = wpos[3] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	D3DXVec3Normalize(&n, &n);

	dis = D3DXVec3Dot(&n, &v);

	if (dis < 0.0f && fabs(dis) > r)
		return false;

	return true;
}