#pragma once

class CMyimgui :public CGameObject
{
private:

public:
	CMyimgui() {}
	~CMyimgui() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
};