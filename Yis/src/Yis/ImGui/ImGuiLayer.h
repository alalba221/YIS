#pragma once

#include "Yis/Layer.h"
#include "Yis/Events/ApplicationEvent.h"
#include "Yis/Events/KeyEvent.h"
#include "Yis/Events/MouseEvent.h"
namespace Yis {
    class YIS_API ImGuiLayer : public Layer
    {
    public:
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& e) override;
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);

        float m_Time = 0.0f;
    };
}
