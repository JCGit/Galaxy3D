#include "Component.h"

namespace Galaxy3D
{
	Component::Component():
		m_deleted(false),
		m_started(false)
	{
	}

	void Component::Destroy(std::weak_ptr<Component> &obj)
	{
		if(!obj.expired())
		{
			obj.lock()->Delete();
			obj.reset();
		}
	}

	void Component::Delete()
	{
		if(!m_deleted)
		{
			m_deleted = true;
		}
	}
}