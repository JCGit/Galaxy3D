#include "SpriteRenderer.h"
#include "VertexType.h"
#include "Camera.h"
#include "Transform.h"

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

		auto context = GraphicsDevice::GetInstance()->GetDeviceContext();

		auto shader = mat->GetShader();
		auto pass = shader->GetPass(0);

		context->IASetInputLayout(pass->vs->input_layout);

		UINT stride = pass->vs->vertex_stride;
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);
		context->IASetIndexBuffer(m_index_buffer, DXGI_FORMAT_R16_UINT, 0);
		
		auto camera = Camera::GetCurrent();
		
		Matrix4x4 wvp = camera->GetViewProjectionMatrix() * GetTransform()->GetLocalToWorldMatrix();

		mat->SetMatrix("WorldViewProjection", wvp);
		mat->SetMainTexture(m_sprite->GetTexture());
		mat->ReadyPass(0);
		
		context->RSSetState(pass->rs->resterizer_state);
		context->OMSetDepthStencilState(pass->rs->depth_stencil_state, 1);
		context->OMSetBlendState(pass->rs->blend_state, 0, 0xffffffff);

		mat->ApplyPass(0);

		context->DrawIndexed(6, 0, 0);

		ID3D11ShaderResourceView *empty[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		context->PSSetShaderResources(0, 8, empty);
	}

	void SpriteRenderer::CreateVertexBuffer()
	{
		int vertex_size = sizeof(VertexMesh);
		Vector2 *vertices = m_sprite->GetVertices();
		Vector2 *uv = m_sprite->GetUV();
		int buffer_size = vertex_size * 4;
		char *buffer = (char *) malloc(buffer_size);
		char *p = buffer;

		for(int i=0; i<4; i++)
		{
			Vector3 pos = vertices[i];
			memcpy(p, &pos, sizeof(Vector3));
			p += sizeof(Vector3);

			Vector3 n;
			memcpy(p, &n, sizeof(Vector3));
			p += sizeof(Vector3);

			Vector4 t;
			memcpy(p, &t, sizeof(Vector4));
			p += sizeof(Vector4);

			Color c = m_color;
			memcpy(p, &c, sizeof(Color));
			p += sizeof(Color);

			Vector2 v1 = uv[i];
			memcpy(p, &v1, sizeof(Vector2));
			p += sizeof(Vector2);

			Vector2 v2;
			memcpy(p, &v2, sizeof(Vector2));
			p += sizeof(Vector2);
		}

		bool dynamic = true;

		auto device = GraphicsDevice::GetInstance()->GetDevice();

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.ByteWidth = buffer_size;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = buffer;
		HRESULT hr = device->CreateBuffer(&bd, &data, &m_vertex_buffer);
		
		free(buffer);
	}

	void SpriteRenderer::CreateIndexBuffer()
	{
		unsigned short *uv = m_sprite->GetIndices();
		int buffer_size = sizeof(unsigned short) * 6;
		char *buffer = (char *) malloc(buffer_size);
		char *p = buffer;

		memcpy(p, uv, buffer_size);

		auto device = GraphicsDevice::GetInstance()->GetDevice();

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_IMMUTABLE;
		bd.CPUAccessFlags = 0;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.ByteWidth = buffer_size;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = buffer;
		HRESULT hr = device->CreateBuffer(&bd, &data, &m_index_buffer);

		free(buffer);
	}
}