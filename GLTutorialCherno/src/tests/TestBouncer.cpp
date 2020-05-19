#include "TestBouncer.h"

#include "Debug.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {

	TestBouncer::TestBouncer()
		:
		m_ClearColor{ 0.2f,0.3f,0.5f,1.0f },
		m_Positions{
		/* positions | texture cords */
		250.0f,250.0f,0.0f,0.0f,
		750.0f,250.0f,1.0f,0.0f,

		750.0f, 750.0f,1.0f,1.0f,
		250.0f, 750.0f,0.0f,1.0f

	},
		m_Indices{
		0,1,2,
		2,3,0
	},
		m_vb(m_Positions, 4 * 4 * sizeof(float)),
		m_va(),
		m_ib(m_Indices, 6),
		m_layout(),
		m_shader("res/shaders/Bouncer.shader"),
		m_texture("res/textures/blue.png"),
		m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_MoveA(false),
		m_MoveB(false),
		// vars
		m_translationA(0.1, 0.2, 0),
		m_translationB(0.3, 0.15, 0),
		m_modelA(glm::translate(glm::mat4(1.0f),m_translationA)),
		m_modelB(glm::translate(glm::mat4(1.0f),m_translationB))


	{
		// Defining layout and adding buffer to VAO
		m_layout.AddFloat(2); /* Define the count */
		m_layout.AddFloat(2);

		m_va.AddBuffer(m_vb, m_layout);


		m_texture.Bind();
		m_shader.SetUniform1i("u_Texture", 0);

	}

	TestBouncer::~TestBouncer()
	{
		m_va.Unbind();
		m_shader.Unbind();

	}

	void TestBouncer::OnUpdate(float deltaTime)
	{
		if (m_modelA[3][0] > 220 || m_modelA[3][0] < -250)
				m_translationA.x = -m_translationA.x;
		if (m_modelA[3][1] > 50 || m_modelA[3][1] < -275)
				m_translationA.y = -m_translationA.y;
		
		if (m_modelB[3][0] > 220 || m_modelB[3][0] < -250)
			m_translationB.x = -m_translationB.x;
		if (m_modelB[3][1] > 50 || m_modelB[3][1] < -275)
					m_translationB.y = -m_translationB.y;
			
	}

	void TestBouncer::OnRender()
	{
		m_renderer.Clear();
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));


		{
			if (m_MoveA)
			{
				m_modelA = glm::translate(m_modelA, m_translationA);
			}

			glm::mat4 mvp = m_proj * m_view * m_modelA;
			m_shader.Bind();
			m_shader.SetUniform4f("u_Color", 0.1f, 0.2, 0.8f, 1.0f);
			m_shader.SetUniformMat4f("u_MVP", mvp);
			m_renderer.Draw(m_va, m_ib, m_shader);
		}

		{
			if (m_MoveB)
			{
				m_modelB = glm::translate(m_modelB, m_translationB);

			}

			glm::mat4 mvp = m_proj * m_view * m_modelB;
			m_shader.Bind();
			m_shader.SetUniformMat4f("u_MVP", mvp);
			m_shader.SetUniform4f("u_Color", 0.2f,0.3,0.5f,1.0f );
			m_renderer.Draw(m_va, m_ib, m_shader);
		}

	}

	void TestBouncer::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		ImGui::Checkbox("Move A", &m_MoveA);
		ImGui::SliderFloat3("Push A", &m_translationA.x, 0.0f, 3.0f);
		ImGui::Checkbox("Move B", &m_MoveB);
		ImGui::SliderFloat3("Push B", &m_translationB.x, 0.0f, 3.0f);
	}

}
