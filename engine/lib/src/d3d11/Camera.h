#ifndef __Camera_h__
#define __Camera_h__

#include "../Component.h"
#include "../CameraClearFlags.h"
#include "../Color.h"
#include <list>

namespace Galaxy3D
{
	class Camera : public Component
	{
	public:
		static void RenderAll();
		Camera();
		virtual ~Camera();
		void SetClearFlags(CameraClearFlags::Enum flag) {m_clear_flags = flag;}
		void SetClearColor(const Color &color) {m_clear_color = color;}
		void SetDepth(int depth);

	private:
		static std::list<Camera *> m_all_camera;
		CameraClearFlags::Enum m_clear_flags;
		Color m_clear_color;
		int m_depth;

		static bool Camera::Less(const Camera *c1, const Camera *c2);
		static void UpdateTime();
		void Render();
	};
}

#endif