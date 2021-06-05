#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "ui_number.h"
#include "camera.h"
#include "player.h"
#include "ui_ammo.h"

class CUiNumber* CUiAmmo::number1;
class CUiNumber* CUiAmmo::number2;
class CUiNumber* CUiAmmo::number3;

void CUiAmmo::Init()
{
	number1 = new CUiNumber();
	number1->Init();
	number2 = new CUiNumber();
	number2->Init();
	number3 = new CUiNumber();
	number3->Init();
}

void CUiAmmo::Uninit()
{
	number1->Uninit();
	number2->Uninit();
	number3->Uninit();
}

void CUiAmmo::Update()
{
	CPlayer* player = CManager::GetScene()->GetGameObject<CPlayer>(1);
	ammo = player->GetAmmo();

	hp = player->GetHp();
}

void CUiAmmo::Draw()
{
	number1->Draw(D3DXVECTOR2(875, 480), ammo / 10 % 10);
	number2->Draw(D3DXVECTOR2(900, 480), ammo % 10);
	number3->Draw(D3DXVECTOR2(120, 480), hp);
}