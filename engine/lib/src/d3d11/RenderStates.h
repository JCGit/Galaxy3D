#ifndef __RenderStates_h__
#define __RenderStates_h__

#include "GraphicsDevice.h"
#include <string>

namespace Galaxy3D
{
	class RenderStates
	{
	public:
		struct Key
		{
			enum Enum
			{
				Cull,
				ZWrite,
				ZTest,
				Offset,
				Blend,
				BlendOp,
				ColorMask,
				Fog,
				Stencil,
			};
		};

		static const int KeyCount = 9;
		static const std::string Keys[KeyCount];

		static const int CullNameCount = 3;
		static const std::string CullNames[CullNameCount];

		static const int ZWriteNameCount = 2;
		static const std::string ZWriteNames[ZWriteNameCount];

		static const int ZTestNameCount = 7;
		static const std::string ZTestNames[ZTestNameCount];

		static const int BlendNameCount = 11;
		static const std::string BlendNames[BlendNameCount];

		static const int BlendOpNameCount = 5;
		static const std::string BlendOpNames[BlendOpNameCount];

		ID3D11RasterizerState *resterizer_state;
		ID3D11DepthStencilState *depth_stencil_state;
		ID3D11BlendState *blend_state;

		RenderStates();
		void Parse(const std::string &s);
		void Create();
		void Release();

	private:
		std::string m_values[KeyCount];
	};
}

#endif