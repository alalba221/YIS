#pragma once

#include "Core.h"
#include "Events/Event.h"
namespace Yis 
{
	class YIS_API Layer
	{
	public:
		Layer(const std::string& name = "Layer") :
			m_DebugName(name)
		{
		}
		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;


		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}