//ÉVÅ[Éìä«óù
#pragma once
#include <list>
#include <typeinfo>
#include <vector>
#include "main.h"
#include "input.h"
#include "game_object.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "campolygon.h"
#include "myimgui.h"
#include "light.h"

#define Layer_Num  3

class CScene
{
protected:
	std::list<CGameObject*> m_GameObject[Layer_Num];//listÇ™4Ç¬

public:
	CScene() {}
	virtual ~CScene() {}

	virtual void Init() = 0;

	virtual void Uninit()
	{
		for (int i = 0; i < Layer_Num; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < Layer_Num; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}
			m_GameObject[i].remove_if
			(
				[](CGameObject* object)
			{
				return object->Destroy();
			}
			);
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < Layer_Num; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	virtual void DepthDraw()
	{
		for (int i = 0; i < 2; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	virtual void PPDraw()
	{
		for (CGameObject* object : m_GameObject[3])
		{
			object->Draw();
		}
	}

	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects;
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}
};
