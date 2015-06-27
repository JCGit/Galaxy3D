#include "Material.h"

static const std::string MAIN_TEXTURE_NAME = "_MainTex";

namespace Galaxy3D
{
	std::shared_ptr<Material> Material::Create(const std::shared_ptr<Shader> &shader)
	{
		std::shared_ptr<Material> mat(new Material());
		mat->SetShader(shader);

		return mat;
	}

	Material::Material():
		m_render_queue(-1)
	{
	}

	void Material::SetShader(const std::shared_ptr<Shader> &shader)
	{
		m_shader = shader;
		SetName(m_shader->GetName());
	}

	void Material::SetRenderQueue(int queue)
	{
		m_render_queue = queue;
	}

	void Material::SetVector(const std::string &name, const Vector4 &vector)
	{
		m_vectors[name] = vector;
	}

	void Material::SetColor(const std::string &name, const Color &color)
	{
		m_colors[name] = color;
	}

	void Material::SetMatrix(const std::string &name, const Matrix4x4 &matrix)
	{
		m_matrices[name] = matrix;
	}

	void Material::SetMatrixArray(const std::string &name, const std::vector<Matrix4x4> &matrices)
	{
		m_matrix_arrays[name] = matrices;
	}

	void Material::SetTexture(const std::string &name, const std::shared_ptr<Texture> &texture)
	{
		m_textures[name] = texture;
	}

	void Material::SetMainTexture(const std::shared_ptr<Texture> &texture)
	{
		m_textures[MAIN_TEXTURE_NAME] = texture;
	}

	std::shared_ptr<Texture> Material::GetMainTexture()
	{
		return GetTexture(MAIN_TEXTURE_NAME);
	}

	std::shared_ptr<Texture> Material::GetTexture(const std::string &name)
	{
		std::shared_ptr<Texture> tex;

		auto find = m_textures.find(name);
		if(find != m_textures.end())
		{
			tex = find->second;
		}

		return tex;
	}

	void Material::Copy(const Material &mat)
	{
		*this = mat;
	}

	void Material::Apply(int pass)
	{
		
	}
}