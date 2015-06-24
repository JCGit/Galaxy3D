#ifndef __Camera_h__
#define __Camera_h__

#include "../Component.h"
#include "../CameraClearFlags.h"
#include "../Color.h"
#include "../Matrix4x4.h"
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
		void SetCullingMask(int mask) {m_culling_mask = mask;}
		int GetCullingMask() const {return m_culling_mask;}
		void SetOrthographic(bool ortho) {m_orthographic = ortho;}
		void SetOrthographicSize(float ortho_size) {m_orthographic_size = ortho_size;}
		void SetFieldOfView(float fov) {m_field_of_view = fov;}
		void SetClipPlane(float near_clip, float far_clip) {m_near_clip_plane = near_clip; m_far_clip_plane = far_clip;}
		
	private:
		static std::list<Camera *> m_all_camera;
		CameraClearFlags::Enum m_clear_flags;
		Color m_clear_color;
		int m_depth;
		int m_culling_mask;
		bool m_orthographic;
		float m_orthographic_size;
		float m_field_of_view;
		float m_near_clip_plane;
		float m_far_clip_plane;

		static bool Camera::Less(const Camera *c1, const Camera *c2);
		static void UpdateTime();
		void Render();
	};
}

#endif