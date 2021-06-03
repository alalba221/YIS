#pragma once

#include "Yis/Core/Layer.h"
//#include "Events/ApplicationEvent.h"
//#include "Events/KeyEvent.h"
//#include "Events/MouseEvent.h"
namespace Yis {
    class YIS_API ImGuiLayer : public Layer
    {
    public:
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;
        void Begin();
        void End();


        virtual void OnUpdate() override {
        
        };
        virtual void OnEvent(Event& e) override {};
        

        float m_Time = 0.0f;
    };
}
