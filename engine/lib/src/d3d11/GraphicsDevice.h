#ifndef __GraphicsDevice_h__
#define __GraphicsDevice_h__

#include <d3d11.h>

namespace Galaxy3D
{
	class GraphicsDevice
	{
	public:
		static GraphicsDevice *GetInstance();
		GraphicsDevice();
		~GraphicsDevice();
		void Init(void *param);

	private:
		ID3D11Device *m_d3d_device;
		IDXGISwapChain *m_swap_chain;
		ID3D11DeviceContext *m_immediate_context;
		ID3D11RenderTargetView *m_render_target_view;
		ID3D11Texture2D *m_depth_stencil_texture;
		ID3D11DepthStencilView *m_depth_stencil_view;
	};
}

#endif