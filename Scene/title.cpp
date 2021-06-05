//タイトルシーン
#include "main.h"
#include "manager.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "model.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "titlepolygon.h"
#include "titlemoji.h"
#include "titleenter.h"
#include "myimgui.h"
#include "camera.h"
#include "field.h"
#include "light.h"

void CTitle::Init()
{
	AddGameObject<CTPolygon>(2);
	AddGameObject<CTMoji>(2);
	AddGameObject<CTEnter>(2);
}

void CTitle::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CGame>();
	}
}