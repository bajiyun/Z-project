//IMGUIを管理
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "scene.h"
#include "bullet.h"
#include "enemy.h"
#include "weapon.h"
#include "myimgui.h"

void  CMyimgui::Init()
{
}
void  CMyimgui::Uninit()
{
}
void  CMyimgui::Update()
{
}
void  CMyimgui::Draw()
{
	ImGui::Begin("Player");

	CScene* scene = CManager::GetScene();
	CPlayer* player = scene->GetGameObject<CPlayer>(1);
	D3DXVECTOR3 forward = player->GetForward();
	D3DXVECTOR3 playerPosition = player->GetPosition();
	D3DXVECTOR3 playerRotation = player->GetRotation();
	D3DXVECTOR3 playerScale = player->GetScale();
	int playerState = player->GetState();
	int Hp = player->GetHp();

	ImGui::Text("Position: x = %1.1f ,y = %1.1f z = %1.1f ", playerPosition.x, playerPosition.y, playerPosition.z);
	ImGui::Text("Rotation: x = %1.1f ,y = %1.1f z = %1.1f ", playerRotation.x, playerRotation.y, playerRotation.z);

	switch (playerState)//ステートマシン
	{
	case 0:
		ImGui::Text("State : Idle");
		break;
	case 1:
		ImGui::Text("State : Run");
		break;
	case 2:
		ImGui::Text("State : Back");
		break;
	case 3:
		ImGui::Text("State : LeftTurn");
		break;
	case 4:
		ImGui::Text("State : RightTurn");
		break;
	case 5:
		ImGui::Text("State : Aiming");
		break;
	case 6:
		ImGui::Text("State : Firing");
		break;
	case 7:
		ImGui::Text("State : Reloading");
		break;
	case 8:
		ImGui::Text("State : Dying");
		break;
	case 9:
		ImGui::Text("State : Hurt");
		break;
	}

	ImGui::Text("HP : %d ", Hp);

	ImGui::End();

	/*----------test-----------*/
	static float slider1 = 0.0f;
	ImGui::Begin("Test");
	/*----------group test----------*/
	ImGui::SetNextTreeNodeOpen(true, 2);
	if (ImGui::TreeNode("group 1"))
	{
		CWeapon* weapon = scene->GetGameObject<CWeapon>(1);

		static D3DXVECTOR3 w_pos = weapon->GetPosition();
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		ImGui::SliderFloat("weaponposx", &w_pos.x, -200.0f, 200.0f);
		ImGui::SliderFloat("weaponposy", &w_pos.y, -200.0f, 200.0f);
		ImGui::SliderFloat("weaponposz", &w_pos.z, -200.0f, 200.0f);

		ImGui::TreePop();
	}
	ImGui::End();
}