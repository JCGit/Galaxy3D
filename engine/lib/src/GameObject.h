#ifndef __GameObject_h__
#define __GameObject_h__

#include "Object.h"
#include "Component.h"
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
		template <class T>
		std::weak_ptr<Component> AddComponent()
		{
			auto t = std::make_shared<T>();
			std::shared_ptr<Component> com = std::dynamic_pointer_cast<Component>(t);

			AddComponent(com);

			return com;
		}

	protected:

	private:
		std::vector<std::shared_ptr<Component>> m_components;
		bool m_active_in_hierarchy;
		bool m_active_self;
		int m_layer;
		bool m_deleted;

		GameObject(const std::string &name);
		void Delete();
		void Update();
		void LateUpdate();
		void AddComponent(const std::shared_ptr<Component> &com);
	};
}

#endif