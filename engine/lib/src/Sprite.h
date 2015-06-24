#ifndef __Sprite_h__
#define __Sprite_h__

#include "Object.h"
#include "Texture2D.h"
#include "Rect.h"
#include "Vector2.h"
#include "Vector4.h"

namespace Galaxy3D
{
	class Sprite : Object
	{
	public:
		//rect:Location of the Sprite on the original Texture, specified in pixels.
		//pivot:Location of the Sprite's center point in the Rect on the original Texture, specified in pixels.
		//pixels_per_unit:The number of pixels in the sprite that correspond to one unit in world space. (Read Only)
		//border:the border sizes of the sprite.
		static std::shared_ptr<Sprite> Create(
			const std::weak_ptr<Texture2D> &texture,
			const Rect &rect,
			const Vector2 &pivot,
			float pixels_per_unit,
			const Vector4 &border);

	private:
		std::weak_ptr<Texture2D> m_texture;
		Rect m_rect;
		Vector2 m_pivot;
		float m_pixels_per_unit;
		Vector4 m_border;
		Vector2 m_vertices[4];
		Vector2 m_uv[4];
		unsigned short m_triangles[6];

		Sprite();
	};
}

#endif