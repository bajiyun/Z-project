//ÉQÅ[ÉÄÉVÅ[Éì
#include "main.h"
#include "manager.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "model.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "fire.h"
#include "enemy.h"
#include "weapon.h"
#include "tree.h"
#include "campolygon.h"
#include "ui_number.h"
#include "ui_ammo.h"
#include "redrec.h"
#include "dead.h"
#include "myimgui.h"
#include "camera.h"
#include "field.h"
#include "meshField.h"
#include "light.h"

int ammo;

void CGame::Init()
{
	CBullet::Load();
	CExplosion::Load();
	CEnemy::Load();
	CDead::Load();
	CFire::Load();

	AddGameObject<CCamera>(0);
	AddGameObject<CMeshField>(1);
	AddGameObject<CPlayer>(1);
	AddGameObject<CEnemy>(1)->SetPositionType(D3DXVECTOR3(0.0f, 0.5f, 7.0f), 0);
	AddGameObject<CEnemy>(1)->SetPositionType(D3DXVECTOR3(-3.0f, 0.0f, 7.0f), 1);
	AddGameObject<CEnemy>(1)->SetPositionType(D3DXVECTOR3(3.0f, 1.0f, 7.0f), 2);
	AddGameObject<CWeapon>(1);
	AddGameObject<CTree>(1)->SetPosition(D3DXVECTOR3(12, 0, 23));
	AddGameObject<CTree>(1)->SetPosition(D3DXVECTOR3(14, 0, -12));
	AddGameObject<CTree>(1)->SetPosition(D3DXVECTOR3(38, 0, 26));
	AddGameObject<CTree>(1)->SetPosition(D3DXVECTOR3(1, 0, 10));
	AddGameObject<CTree>(1)->SetPosition(D3DXVECTOR3(-9, 0, 4));
	AddGameObject<CTree>(1)->SetPosition(D3DXVECTOR3(8, 0, 5));
	AddGameObject<CTree>(1)->SetPosition(D3DXVECTOR3(-12, 0, 10));

	AddGameObject<CUiAmmo>(2);
	AddGameObject<CPolygon>(2);
	AddGameObject<CRedRec>(2);
	//AddGameObject<CMyimgui>(2);
}

void CGame::Uninit()
{
	CScene::Uninit();
	CBullet::Unload();
	CExplosion::Unload();
	CEnemy::Unload();
	CDead::Unload();
}

void CGame::Update()
{
	CScene::Update();

	CPlayer* player = CManager::GetScene()->GetGameObject<CPlayer>(1);
	int p_Hp = player->GetHp();

	if (p_Hp <= 0)
	{
		deadframe++;

		if (deadframe >= 170)
		{
			CDead* dead = CManager::GetScene()->GetGameObject<CDead>(2);

			AddGameObject<CDead>(2);

			if (CInput::GetKeyTrigger('R'))
				CManager::SetScene<CGame>();
		}
	}

	CScene* scene = CManager::GetScene();
	std::vector<CEnemy*> enemyList = scene->GetGameObjects<CEnemy>(1);
	if (enemyList.empty())
	{
		AddGameObject<CEnemy>(1)->SetPositionType(D3DXVECTOR3(-3.0f, 0.5f, 23.0f), 0);
		AddGameObject<CEnemy>(1)->SetPositionType(D3DXVECTOR3(-3.0f, 0.0f, 20.0f), 1);
		AddGameObject<CEnemy>(1)->SetPositionType(D3DXVECTOR3(-3.0f, 1.0f, 18.0f), 2);
	}
}