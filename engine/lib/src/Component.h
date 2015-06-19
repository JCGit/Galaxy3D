#ifndef __Component_h__
#define __Component_h__

#include "Object.h"

namespace Galaxy3D
{
	class Component : public Object
	{
	public:
		static void Destroy(std::weak_ptr<Component> &obj);
		virtual ~Component() {}

	protected:
		Component();
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void OnDestroy() {}

	private:
		bool m_deleted;

		void Delete();
	};
}

#endif