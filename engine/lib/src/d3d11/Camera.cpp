#include "Camera.h"
#include "../GameObject.h"
#include "GraphicsDevice.h"
#include "../GTTime.h"
#include "../Debug.h"

namespace Galaxy3D
{
	std::list<Camera *> Camera::m_all_camera;

	Camera::Camera():
		m_clear_flags(CameraClearFlags::SolidColor),
		m_clear_color(0, 0, 1, 1),
		m_depth(0)
	{
		m_all_camera.push_back(this);
		m_all_camera.sort(Less);
	}

	Camera::~Camera()
	{
		m_all_camera.remove(this);
	}

	bool Camera::Less(const Camera *c1, const Camera *c2)
	{
		return c1->m_depth < c2->m_depth;
	}

	void Camera::SetDepth(int depth)
	{
		m_depth = depth;
		m_all_camera.sort(Less);
	}

	void Camera::UpdateTime()
	{
		if(GTTime::m_time_record < 0)
		{
			GTTime::m_time_record = GTTime::GetRealTimeSinceStartup();
			GTTime::m_frame_record = GTTime::GetFrameCount();
		}

		float now = GTTime::GetRealTimeSinceStartup();
		int frame = GTTime::GetFrameCount();
		if(now - GTTime::m_time_record > 1)
		{
			GTTime::m_fps = frame - GTTime::m_frame_record;
			GTTime::m_time_record = now;
			GTTime::m_frame_record = frame;

			Debug::Log("fps:%d render:%f update:%f", GTTime::m_fps, GTTime::m_render_time * 1000, GTTime::m_update_time * 1000);
		}

		GTTime::m_frame_count++;
	}

	void Camera::RenderAll()
	{
		float time = GTTime::GetRealTimeSinceStartup();

		UpdateTime();

		for(auto i : m_all_camera)
		{
			auto obj = i->GetGameObject();
			if(obj->IsActiveInHierarchy() && i->IsEnable())
			{
				i->Render();
			}
		}

		GraphicsDevice::GetInstance()->GetSwapChain()->Present(0, 0);

		GTTime::m_render_time = GTTime::GetRealTimeSinceStartup() - time;
	}

	void Camera::Render()
	{
		auto context = GraphicsDevice::GetInstance()->GetDeviceContext();
		auto render_buffer= GraphicsDevice::GetInstance()->GetRenderTargetView();
		auto depth_buffer = GraphicsDevice::GetInstance()->GetDepthStencilView();

		context->ClearRenderTargetView(render_buffer, (const float *) &m_clear_color);
		context->ClearDepthStencilView(depth_buffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}