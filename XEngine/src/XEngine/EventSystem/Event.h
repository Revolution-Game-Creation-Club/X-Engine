// Base event class, with event type and category enums, as well as an event dispatcher class
#pragma once
#include "Xpch.h"
#include "../Core/XCore.h"
namespace XEngine
{
	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
	class XENGINE_API Event 
	{
	public:
		// To Be Defined in derived classes
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		// Prototype in Header File
		inline bool IsInCategory(EventCategory category)
			{ return GetCategoryFlags() & category; }
		virtual std::string ToString() const
			{ return GetName(); }
		bool handled = false;
	};
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : eventDispatcherEvent(event)
			{ /* Called everytime a event occurs */ }
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (eventDispatcherEvent.GetEventType() == T::GetStaticType())
			{
				eventDispatcherEvent.handled = func(*(T*)&eventDispatcherEvent);
				return true;
			}
			return false;
		}
	private:
		Event& eventDispatcherEvent;
	};
	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } virtual EventType GetEventType() const override { return GetStaticType(); } virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }