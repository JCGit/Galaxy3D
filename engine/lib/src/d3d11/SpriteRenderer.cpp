#include "SpriteRenderer.h"

namespace Galaxy3D
{
	SpriteRenderer::SpriteRenderer():
		m_color(1, 1, 1, 1)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Render()
	{
		auto mat = GetSharedMaterial();
		if(!mat)
		{
			mat = Material::Create("Sprite");
			SetSharedMaterial(mat);
		}
	}
}