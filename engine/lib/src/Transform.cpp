#include "Transform.h"

namespace Galaxy3D
{
	Transform::Transform()
	{
	}

	void Transform::RemoveChild(std::weak_ptr<Transform> &child)
	{
		for(auto i=m_children.begin(); i!=m_children.end(); i++)
		{
			if(i->lock() == child.lock())
			{
				m_children.erase(i);
				break;
			}
		}
	}

	void Transform::AddChild(std::weak_ptr<Transform> &child)
	{
		m_children.push_back(child);
	}

	void Transform::SetBeRoot()
	{
		if(!m_parent.expired())
		{
			m_parent.lock()->RemoveChild(m_transform);
			m_parent.reset();
		}
	}

	void Transform::SetParent(const std::weak_ptr<Transform> &parent)
	{
		SetBeRoot();

		m_parent = parent;
		if(!m_parent.expired())
		{
			m_parent.lock()->AddChild(m_transform);
		}
	}
}