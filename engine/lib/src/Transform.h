#ifndef __Transform_h__
#define __Transform_h__

#include "Component.h"
#include <list>

namespace Galaxy3D
{
	class Transform : public Component
	{
		friend class GameObject;

	public:
		std::weak_ptr<Transform> GetParent() const {return m_parent;}
		void SetParent(const std::weak_ptr<Transform> &parent);
		bool IsRoot() const {return m_parent.expired();}

	protected:

	private:
		std::weak_ptr<Transform> m_parent;
		std::list<std::weak_ptr<Transform>> m_children;

		Transform();
		void SetBeRoot();
		void RemoveChild(std::weak_ptr<Transform> &child);
		void AddChild(std::weak_ptr<Transform> &child);
	};
}

#endif