#ifndef __GameObject_h__
#define __GameObject_h__

#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include <vector>
#include <memory>

namespace Galaxy3D
{
	class GameObject : public Object
	{
		friend class World;

	public:
		static std::weak_ptr<GameObject> Create(const std::string &name);
		static void Destroy(std::weak_ptr<GameObject> &obj);
		virtual ~GameObject();
		template<class T> inline std::weak_ptr<Component> AddComponent();
		std::weak_ptr<Transform> GetTransform() const {return m_transform;}
		bool IsActiveInHierarchy() const {return m_active_in_hierarchy;}
		bool IsActiveSelf()const {return m_active_self;}
		void SetActive(bool active);

	protected:

	private:
		std::list<std::shared_ptr<Component>> m_components;
		std::list<std::shared_ptr<Component>> m_components_new;
		bool m_active_in_hierarchy;
		bool m_active_self;
		int m_layer;
		bool m_deleted;
		std::weak_ptr<Transform> m_transform;

		GameObject(const std::string &name);
		void Delete();
		void Update();
		void LateUpdate();
		void AddComponent(const std::shared_ptr<Component> &com);
		void SetActiveInHierarchy(bool active);
	};

	template<class T> inline std::weak_ptr<Component> GameObject::AddComponent()
	{
		if(m_deleted)
		{
			return std::weak_ptr<Component>();
		}

		auto t = std::make_shared<T>();
		std::shared_ptr<Component> com = std::dynamic_pointer_cast<Component>(t);

		AddComponent(com);

		return com;
	}
}

#endif