#include "SpriteRenderer.h"

namespace Galaxy3D
{
	SpriteRenderer::SpriteRenderer():
		m_color(1, 1, 1, 1),
		m_vertex_buffer(nullptr),
		m_index_buffer(nullptr)
	{
		m_sorting_layer = 0;
		m_sorting_order = 0;

		Sort();
	}

	SpriteRenderer::~SpriteRenderer()
	{
		SAFE_RELEASE(m_vertex_buffer);
		SAFE_RELEASE(m_index_buffer);
	}

	void SpriteRenderer::Render()
	{
		if(!m_sprite)
		{
			return;
		}

		auto mat = GetSharedMaterial();
		if(!mat)
		{
			mat = Material::Create("Sprite");
			SetSharedMaterial(mat);
		}

		if(m_vertex_buffer == nullptr)
		{
			CreateVertexBuffer();
		}

		if(m_index_buffer == nullptr)
		{
			CreateIndexBuffer();
		}
	}

	void SpriteRenderer::CreateVertexBuffer()
	{
		
	}

	void SpriteRenderer::CreateIndexBuffer()
	{
		
	}
}