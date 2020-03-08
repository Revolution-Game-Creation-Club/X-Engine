#include "Xpch.h"
#include <stdio.h>
#include "Application.h"
#include "../XEngine/Log.h"
#include <GLAD/glad.h>
namespace XEngine
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	// Constructor: Print Application Created
	Application* Application::s_Instance = nullptr;
	Application::Application() 
	{  
		X_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create()); 
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	// Destructor: Print Application Deleted
	Application::~Application() { printf("Application Deleted\n"); }
	void Application::PushLayer(Layer* layer) 
	{ 
		m_LayerStack.PushLayer(layer); 
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) 
	{ 
		m_LayerStack.PushOverlay(layer); 
		layer->OnAttach();
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		X_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	// Function: Keeps application alive and running
	void Application::Run() 
	{
		// Keeps the application running
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate(); 
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}