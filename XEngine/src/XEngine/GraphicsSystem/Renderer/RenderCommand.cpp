// Render Command Source File
#include "Xpch.h"
#include "XEngine/GraphicsSystem/Renderer/RenderCommand.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLRendererAPI.h"
namespace XEngine
	{ Scope<RendererAPI> RenderCommand::renderCommandAPI = CreateScope<OpenGLRendererAPI>(); }