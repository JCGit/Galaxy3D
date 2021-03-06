#include "GameObject.h"
#include "Layer.h"
#include "World.h"

namespace Galaxy3D
{
	std::shared_ptr<GameObject> GameObject::Create(const std::string &name)
	{
		auto obj = std::shared_ptr<GameObject>(new GameObject(name));
		World::AddGameObject(obj);

		auto transform = std::shared_ptr<Transform>(new Transform());
		obj->m_transform = transform;
		obj->AddComponent(transform, true);

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
		if(!m_deleted)
		{
			m_deleted = true;
		}
	}

	void GameObject::Update()
	{
		m_components.insert(m_components.end(), m_components_new.begin(), m_components_new.end());
		m_components_new.clear();

		for(auto &i : m_components)
		{
			if(!i->m_deleted)
			{
				if(!i->m_started)
				{
					i->m_started = true;
					i->Start();
				}

				i->Update();
			}
		}
	}

	void GameObject::LateUpdate()
	{
		for(auto &i : m_components)
		{
			if(!i->m_deleted)
			{
				i->LateUpdate();
			}
		}

		//delete component
		auto it = m_components.begin();
		while(it != m_components.end())
		{
			if((*it)->m_deleted)
			{
				it = m_components.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void GameObject::AddComponent(const std::shared_ptr<Component> &com, bool immediately)
	{
		if(immediately)
		{
			m_components.push_back(com);
		}
		else
		{
			m_components_new.push_back(com);
		}

		auto obj = World::FindGameObject(this);
		com->m_gameobject = obj;
		com->m_transform = m_transform;
		com->SetName(GetName());
	}

	void GameObject::SetActive(bool active)
	{
		m_active_self = active;

		if(	(m_active_in_hierarchy != active) && 
			(m_transform.lock()->IsRoot() ||
			m_transform.lock()->GetParent().lock()->GetGameObject()->IsActiveInHierarchy()))
		{
			SetActiveInHierarchy(active);
		}
	}

	void GameObject::SetActiveInHierarchy(bool active)
	{
		if(m_active_in_hierarchy != active)
		{
			m_active_in_hierarchy = active;

			for(auto &i : m_components)
			{
				if(i->IsEnable())
				{
					if(m_active_in_hierarchy)
					{
						i->OnEnable();
					}
					else
					{
						i->OnDisable();
					}
				}
			}

			auto transform = m_transform.lock();
			int child_count = transform->GetChildCount();
			for(int i=0; i<child_count; i++)
			{
				auto child = transform->GetChild(i);
				if(child->GetGameObject()->IsActiveSelf())
				{
					child->GetGameObject()->SetActiveInHierarchy(active);
				}
			}
		}
	}
}