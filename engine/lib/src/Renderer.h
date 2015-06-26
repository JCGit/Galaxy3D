#ifndef __Renderer_h__
#define __Renderer_h__

#include "Component.h"
#include "Vector4.h"
#include <list>

namespace Galaxy3D
{
	class Renderer : public Component
	{
	public:
		virtual ~Renderer();
		bool SetVisible(bool visible) {m_visible = visible;}

	protected:
		bool m_cast_shadow;
		bool m_receive_shadow;
		bool m_visible;
		int m_lightmap_index;
		Vector4 m_lightmap_tiling_offset;
		int m_sorting_layer;
		int m_sorting_order;

		Renderer();

	private:
		static std::list<Renderer *> m_renderers;

		static bool Less(const Renderer *c1, const Renderer *c2);
	};
}

#endif