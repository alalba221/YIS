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
        virtual void OnImGuiRender() override;
        void Begin();
        void End();


        virtual void OnUpdate() override {};
        virtual void OnEvent(Event& e) override {};
        

        float m_Time = 0.0f;
    };
}
