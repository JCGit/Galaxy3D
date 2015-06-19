#include "Component.h"

namespace Galaxy3D
{
	Component::Component():
		m_deleted(false)
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
		m_deleted = true;
	}
}