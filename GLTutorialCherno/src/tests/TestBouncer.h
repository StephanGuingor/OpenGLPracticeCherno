#pragma once

#include "tests/Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <Texture.h>



namespace test
{
	class TestBouncer : public Test
	{
	public:
		TestBouncer();
		~TestBouncer();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;

		bool m_MoveA;
		bool m_MoveB;

		float m_ClearColor[4];
		float m_Positions[16];
		unsigned int m_Indices[6];


		VertexArray m_va;
		VertexBuffer m_vb;
		IndexBuffer m_ib;
		VertexBufferLayout m_layout;
		Shader m_shader;
		Texture m_texture;
		Renderer m_renderer;

		// MVP members
		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::mat4 m_modelA;
		glm::mat4 m_modelB;


	};
}

