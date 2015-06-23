#ifndef __Component_h__
#define __Component_h__

#include "Object.h"

namespace Galaxy3D
{
	class Transform;

	class Component : public Object
	{
		friend class GameObject;

	public:
		static void Destroy(std::weak_ptr<Component> &obj);
		std::weak_ptr<GameObject> GetGameObject() const {return m_gameobject;}
		std::weak_ptr<Transform> GetTransform() const {return m_transform;}

	protected:
		std::weak_ptr<GameObject> m_gameobject;
		std::weak_ptr<Transform> m_transform;

		Component();
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}

	private:
		bool m_deleted;
		bool m_started;

		void Delete();
	};
}

#endif