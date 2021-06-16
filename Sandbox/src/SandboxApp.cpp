#include "Yis.h"
#include "imgui/imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

static void ImGuiShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
class EditorLayer : public Yis::Layer
{
public:
	EditorLayer()
        : m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f }, m_TriangleColor({ 0.8f, 0.2f, 0.3f, 1.0f }),
        m_Camera(glm::perspectiveFov(glm::radians(45.0f), 1280.0f, 720.0f, 0.1f, 10000.0f))
	{
	}

	virtual ~EditorLayer()
	{
	}

	virtual void OnAttach() override
	{
        m_Mesh.reset(new Yis::Mesh("assets/models/dinosaur/dinosaur5k.obj"));
        m_SimplePBRShader.reset(Yis::Shader::Create("assets/shaders/simplepbr.glsl"));
        m_HDRShader.reset(Yis::Shader::Create("assets/shaders/hdr.glsl"));

        m_FrameBuffer.reset(Yis::FrameBuffer::Create(1280, 720, Yis::FrameBufferFormat::RGBA8));
       


        // Create Quad
        static float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions        // texCoords
        -1.0f, -1.0f,0.0f,  0.0f, 0.0f,
         1.0f, -1.0f,0.0f,  1.0f, 0.0f,
         1.0f,  1.0f,0.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,0.0f,  0.0f, 1.0f
        };

        m_VB.reset(Yis::VertexBuffer::Create());
        m_VB->SetData(quadVertices, sizeof(quadVertices));

        uint32_t* indices = new uint32_t[6]{ 0, 1, 2, 2, 3, 0};
        m_IB.reset(Yis::IndexBuffer::Create());
        m_IB->SetData(indices, 6 * sizeof(unsigned int));

	}

	virtual void OnDetach() override
	{
	}
	
	virtual void OnUpdate() override
	{
        YS_APP_INFO("OnUpate");
        m_Camera.Update();
        glm::mat4 viewProjection = m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix();
        
         // all the command should be pushed into Renderer CommandQueue
        // first pass
        m_FrameBuffer->Bind();
       
        Yis::Renderer::Clear(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        Yis::UniformBufferDeclaration<sizeof(glm::mat4) +sizeof(glm::vec4) , 2> simplePbrShaderUB;
        simplePbrShaderUB.Push("u_Color", m_TriangleColor);
        simplePbrShaderUB.Push("u_ViewProjectionMatrix", viewProjection);
        m_SimplePBRShader->UploadUniformBuffer(simplePbrShaderUB);
        m_SimplePBRShader->Bind();
        m_Mesh->Render();
        m_FrameBuffer->Unbind();

        //// second pass
        Yis::Renderer::Clear(1.0,1.0,1.0,1.0);
        
       
        m_HDRShader->Bind();
        m_HDRShader->SetInt("u_Texture", 0);
      
        
        m_VB->Bind();
        m_IB->Bind();
        m_FrameBuffer->BindTexture();
        Yis::Renderer::DrawIndexed(m_IB->GetCount(),false);
	}

	virtual void OnImGuiRender() override
	{
		static bool show_demo_window = false;
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Begin("GameLayer");
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
        ImGui::ColorEdit4("Triangle Color", glm::value_ptr(m_TriangleColor));
		ImGui::End();
        /*ImGui::Begin("Viewport");
        auto viewportSize = ImGui::GetContentRegionAvail();
      
        ImGui::Image((void*)m_FrameBuffer->GetColorAttachmentRendererID(), viewportSize, { 0, 1 }, { 1, 0 });
        ImGui::End();*/

//#if ENABLE_DOCKSPACE
        static bool p_open = true;
        static bool opt_fullscreen = false;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        else
        {
            //ShowDockingDisabledMessage();
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();

                if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
                    p_open = false;
                ImGui::EndMenu();
            }
            ImGuiShowHelpMarker(
                "When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
                "- Drag from window title bar or their tab to dock/undock." "\n"
                "- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
                "- Hold SHIFT to disable docking." "\n"
                "This demo app has nothing to do with it!" "\n\n"
                "This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)." "\n\n"
                "ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame." "\n\n"
                "(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)"
            );

            ImGui::EndMenuBar();
        }

        ImGui::End();
//#endif
	}

	virtual void OnEvent(Yis::Event& event) override
	{
	}
private:
    std::unique_ptr<Yis::VertexBuffer> m_VB;
    std::unique_ptr<Yis::IndexBuffer> m_IB;
    std::unique_ptr<Yis::FrameBuffer> m_FrameBuffer;

    std::unique_ptr<Yis::Shader> m_SimplePBRShader;
    std::unique_ptr<Yis::Shader> m_HDRShader;
    Yis::Camera m_Camera;
    std::unique_ptr<Yis::Mesh> m_Mesh;
	float m_ClearColor[4];
    glm::vec4 m_TriangleColor;
};


//class ExampleLayer :public Yis::Layer 
//{
//public:	
//	ExampleLayer()
//		:Layer("Example")
//	{}
//
//	void OnUpdate() override
//	{
//		Yis::Renderer::Clear(0.1f, 0.3f, 0.8f, 1);
//		if (Yis::Input::IsKeyPressed(YS_KEY_TAB))
//		{
//			YS_APP_TRACE("Tab key is pressed (poll)!");
//			
//		}
//		
//	}
//	void OnEvent(Yis::Event& event)override
//	{
//		//YS_APP_INFO("{0}", event);
//		if (event.GetEventType() == Yis::EventType::KeyPressed)
//		{
//			Yis::KeyPressedEvent& e = (Yis::KeyPressedEvent&)event;
//			if (e.GetKeyCode() == YS_KEY_TAB)
//				YS_APP_TRACE("Tab key is pressed (event)!");
//			YS_APP_TRACE("{0}", (char)e.GetKeyCode());
//		}
//	}
//	void OnAttach() override
//	{}
//	void OnDetach()override
//	{}
//	virtual void OnImGuiRender() override
//	{
//		ImGui::Begin("Text");
//		ImGui::Text("Helli");
//		ImGui::End();
//	}
//
//};
class Sandbox :public Yis::Application 
{
public:
	Sandbox() 
	{
		PushLayer(new EditorLayer());
		
	};
	~Sandbox() {};
};

Yis::Application* Yis::CreateApplication() {
	return new Sandbox();
}
