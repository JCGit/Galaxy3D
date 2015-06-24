#ifndef __Transform_h__
#define __Transform_h__

#include "Component.h"
#include <vector>

namespace Galaxy3D
{
	class Transform : public Component
	{
		friend class GameObject;

	public:
		std::weak_ptr<Transform> GetParent() const {return m_parent;}
		void SetParent(const std::weak_ptr<Transform> &parent);
		bool IsRoot() const {return m_parent.expired();}
		int GetChildCount() const {return m_children.size();}
		std::shared_ptr<Transform> GetChild(int index) const;

	private:
		std::weak_ptr<Transform> m_parent;
		std::vector<std::weak_ptr<Transform>> m_children;

		Transform();
		void SetBeRoot();
		void RemoveChild(std::weak_ptr<Transform> &child);
		void AddChild(std::weak_ptr<Transform> &child);
	};
}

#endif