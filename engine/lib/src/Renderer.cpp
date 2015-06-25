#include "Renderer.h"

namespace Galaxy3D
{
	std::list<Renderer *> Renderer::m_all_renderers;

	Renderer::Renderer():
		m_cast_shadow(false),
		m_receive_shadow(false),
		m_visible(true),
		m_lightmap_index(-1),
		m_lightmap_tiling_offset(),
		m_sorting_layer(0),
		m_sorting_order(0)
	{
		m_all_renderers.push_back(this);
		m_all_renderers.sort(Less);
	}

	Renderer::~Renderer()
	{
		m_all_renderers.remove(this);
	}

	bool Renderer::Less(const Renderer *c1, const Renderer *c2)
	{
		return false;
	}
}