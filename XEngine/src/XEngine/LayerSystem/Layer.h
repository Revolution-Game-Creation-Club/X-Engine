// Layer class header file
#pragma once
#include "XEngine/Core/XCore.h"
#include "XEngine/EventSystem/Event.h"
#include "XEngine/Core/Time.h"
namespace XEngine
{
	class XENGINE_API Layer
	{
	public:
		// Defined in Source File
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnImGuiRender() = 0;
		// Prototype in Header File
		virtual void OnAttach() 
			{ XCORE_INFO("{0} attached", GetName()); }
		virtual void OnDetach() 
			{ XCORE_INFO("{0} detached", GetName()); }
		virtual void OnUpdate(Timestep timestep) { }
		virtual void OnEvent(Event& event) 
			{ /* XCORE_TRACE("{0}", event.GetName()); */}
		inline const std::string& GetName() const
			{ return layerDebugName; }
	protected:
		std::string layerDebugName;
	};
}