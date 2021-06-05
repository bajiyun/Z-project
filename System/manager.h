#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "scene.h"

class CManager
{
private:
	static class CScene* m_Scene;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static class CScene* GetScene() { return m_Scene; }

	template<typename T>
	static void SetScene()
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
			//CResource::UnloadAll();
		}

		T* scene = new T();
		m_Scene = scene;
		scene->Init();
	}
};
