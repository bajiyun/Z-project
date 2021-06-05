#pragma once

#include "game_object.h"
#include "chara_object.h"

class CEnemy :public CCharacterObject
{
private:

	static class CAnimationModel* m_Model;
	static class CAnimationModel* m_Model1;
	static class CAnimationModel* m_Model2;//ŽOŽí—Þ‚Ìƒ]ƒ“ƒr‘Î‰ž‚·‚éˆ×

	int m_State;
	int m_Type = 0;

	int m_Frame;
	int m_RunFrame;
	int m_AttackFrame;
	int m_DryingFrame;

	int m_EnemyHp;

	bool m_FrameControl;
	bool m_Alive;

public:

	CEnemy() {}
	~CEnemy() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	int GetRunFrame() { return m_RunFrame; }
	int GetAttackFrame() { return m_AttackFrame; }
	bool GetFrameControl() { return m_FrameControl; }
	void GetAttack() { m_EnemyHp--; }
	bool GetLive() { return m_Alive; }

	void SetPositionType(D3DXVECTOR3 Position, int i)
	{
		m_Position = Position; m_Type = i;
	}
	void SetType(int i) { m_Type = i; }
};