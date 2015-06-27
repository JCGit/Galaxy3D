#ifndef __Material_h__
#define __Material_h__

#include "Object.h"
#include "ShaderPropertyType.h"
#include "Shader.h"
#include "Color.h"
#include "Matrix4x4.h"
#include "Texture.h"
#include <unordered_map>

namespace Galaxy3D
{
	class Material : public Object
	{
	public:
		static std::shared_ptr<Material> Create(const std::shared_ptr<Shader> &shader);
		void SetShader(const std::shared_ptr<Shader> &shader);
		const std::shared_ptr<Shader> &GetShader() {return m_shader;}
		void SetRenderQueue(int queue);
		int GetRenderQueue() const {return m_render_queue;}
		void SetVector(const std::string &name, const Vector4 &vector);
		void SetColor(const std::string &name, const Color &color);
		void SetMatrix(const std::string &name, const Matrix4x4 &matrix);
		void SetMatrixArray(const std::string &name, const std::vector<Matrix4x4> &matrices);
		void SetTexture(const std::string &name, const std::shared_ptr<Texture> &texture);
		void SetMainTexture(const std::shared_ptr<Texture> &texture);
		std::shared_ptr<Texture> GetMainTexture();
		std::shared_ptr<Texture> GetTexture(const std::string &name);
		void Copy(const Material &mat);
		void Apply(int pass);

	private:
		std::shared_ptr<Shader> m_shader;
		std::unordered_map<std::string, Color> m_colors;
		std::unordered_map<std::string, Matrix4x4> m_matrices;
		std::unordered_map<std::string, std::vector<Matrix4x4>> m_matrix_arrays;
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
		std::unordered_map<std::string, Vector4> m_vectors;
		
		int m_render_queue;

		Material();
		Material(const Material &mat) {}
	};
}

#endif