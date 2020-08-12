#include "Xpch.h"
#include <GLM/glm.hpp>
#include "XEngine/Scene/Scene.h"
#include "XEngine/Scene/Entity.h"
#include "XEngine/Scene/Components.h"
#include "XEngine/Renderer/RendererAPI/Renderer2D.h"
namespace XEngine
{
	Scene::Scene()
	{
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
	}
	Scene::~Scene() {}
	Entity Scene::CreateEntity(const std::string tagName)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = tagName.empty() ? "Entity" : tagName;
		return entity;
	}
	void Scene::OnUpdate(Timestep timestep)
	{
		// Render 2D
		Camera* primaryCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
			if (camera.Primary)
			{
				primaryCamera = &camera.Camera;
				cameraTransform = &transform.Transform;
				break;
			}
		}
		if (primaryCamera)
		{
			Renderer2D::BeginScene(primaryCamera->GetProjection(), *cameraTransform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				if (sprite.Texture == nullptr)
					Renderer2D::DrawQuad(transform, sprite.Color);
				else
					Renderer2D::DrawQuad(transform, sprite.Texture);
			}
			Renderer2D::EndScene();
		}
	}
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}
}