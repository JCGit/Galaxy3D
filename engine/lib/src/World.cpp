#include "World.h"

namespace Galaxy3D
{
	std::unordered_map<GameObject *, std::shared_ptr<GameObject>> World::m_gameobjects;
	std::vector<std::shared_ptr<GameObject>> World::m_gameobjects_new;

	void World::AddGameObject(const std::shared_ptr<GameObject> &obj)
	{
		m_gameobjects_new.push_back(obj);
	}

	void World::AddNewGameObjects()
	{
		for(std::shared_ptr<GameObject> &obj : m_gameobjects_new)
		{
			m_gameobjects[obj.get()] = obj;
		}
		m_gameobjects_new.clear();
	}

	void World::Update()
	{
		AddNewGameObjects();

		//更新所有根obj,子obj的更新由父亲负责
		/*
		for(auto i : m_gameobjects)
		{
			i.second->Update();
		}

		for(auto i : m_gameobjects)
		{
			i.second->LateUpdate();
		}
		*/
	}
}