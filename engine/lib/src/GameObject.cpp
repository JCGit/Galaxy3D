#include "GameObject.h"
#include "Layer.h"
#include "World.h"

namespace Galaxy3D
{
	std::weak_ptr<GameObject> GameObject::Create(const std::string &name)
	{
		auto obj = std::shared_ptr<GameObject>(new GameObject(name));

		World::AddGameObject(obj);

		return obj;
	}

	void GameObject::Destroy(std::weak_ptr<GameObject> &obj)
	{
		if(!obj.expired())
		{
			obj.lock()->Delete();
			obj.reset();
		}
	}

	GameObject::GameObject(const std::string &name):
		m_active_in_hierarchy(true),
		m_active_self(true),
		m_layer(Layer::Default),
		m_deleted(false)
	{
		SetName(name);
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Delete()
	{
		m_deleted = true;
	}

	void GameObject::Update()
	{
		
	}

	void GameObject::LateUpdate()
	{
	
	}

	template <class T>
	std::weak_ptr<Component> GameObject::AddComponent()
	{
		auto t = std::make_shared<T>();
		std::shared_ptr<Component> com = std::dynamic_pointer_cast<Component>(t);

		return com;
	}
}