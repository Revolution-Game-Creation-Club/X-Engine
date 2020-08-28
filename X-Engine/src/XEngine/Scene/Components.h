#pragma once
#include <glm/glm.hpp>
#include "XEngine/Core/XCore.h"
#include "XEngine/Renderer/Texture.h"
#include "XEngine/Scene/SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "XEngine/Scene/ScriptableEntity.h"
namespace XEngine
{
	struct TagComponent
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : Tag(tag) {}
	};
	struct TransformComponent
	{
		//glm::mat4 Transform;
		glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
		float Rotation = 0;
		glm::vec2 Size{ 1.0f, 1.0f };
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3 position, const glm::vec2 size, const float rotation) : Position(position), Size(size), Rotation(rotation) {}
		glm::mat4 CalculateMatrix()
		{
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) * glm::rotate(glm::mat4(1.0f), Rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
			return transform;
		}
	};
	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture;
		float TillingFactor = 1.0f;
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) : Color(color) {}
	};
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;
		ScriptableEntity*(*InstantiateScript)();
		void(*DestroyScript)(NativeScriptComponent*);
		template<typename T>
		void Bind()
		{
			InstantiateScript = []()
				{ return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc)
			{
				delete nsc->Instance;
				nsc->Instance = nullptr;
			};
		}
	};
}