/* The entry point for applications. */
#include "App.h"
#include "Engine/Hale3D.h"

// Un-define windows DrawText.
#ifdef DrawText
#undef DrawText
#endif

namespace Hale3D {
	static std::vector<Animation*> animations;
	App::App(const std::string& pTitle) : window(1024, 768, pTitle), _quit(false), camera(nullptr) {
		if (GetCurrent() == nullptr) 
			SetCurrent(this);
		
		Start();
	}

	void App::Start() {
		Time::SetTargetFPS(6000); // NOTE: This feature currently doesn't work as intended, set it to a higher value than intended!
		Skybox::SetFallbackShader("cubemap"); // Tell the engine it can fallback on "cubemap" shader when a skybox is loaded with an invalid or unreadable shader path.
		Texture::SetFallbackTexture("Resources/Textures/error.tga"); // Tell the engine it can fallback on "error.tga" when Texture::Load2D fails.
		Material::SetFallbackMaterial("Resources/Materials/error.mat"); // Tell the engine it can fallback on "error.mat" when Material::Load fails.

		// Load a font.
		font = Font::Load("Resources/Fonts/introheadr-base.otf", 20);

		// Step 1) Load the animation we want to play.
		animations.push_back(Animation::Load("Resources/Animations/bob_lamp_update.anim"));

		// Step 2) Create a camera.
		camera = FlyCamera::Create();

		// Step 3) Create our entities.
		Vector3 basePosition(-45, -1.5, 15);
		for (uint16_t col = 0; col < 10; ++col) {
			for (uint16_t row = 0; row < 10; ++row) {
				Entity* entity = Entity::Create(); // NOTE: This is safe because the "World" always contains a list of entities, so we won't loose this pointer.
				entity->SetModel("Resources/Models/bob_lamp_update.mdl");
				entity->SetPosition(basePosition + Vector3(row * 6.5f, 0, col * 5.5f) + Vector3(Random::Float<float>(-0.5f, 0.5f), 0, 0));
				entity->SetAngles(Vector3(-90, 0, 0));
				double time = Random::Float<double>(0, animations[0]->GetDuration()); // Play the animation at a random time in the sequence on each joint of the model.
				for (auto& joint : entity->GetJoints()) {
					joint.PlayAnimation(animations[0], 0);
					joint.SetTime(time);
				}
				float randomScale = Random::Float<float>(0.25f, 1.f);
				entity->SetScale(Vector3(randomScale, randomScale, randomScale));
				entity->Spawn();
			}
		}
	}

	void App::Close() {
		_quit = true;
	}

	void App::OnExit() {
		// Delete the camera.
		if (camera != nullptr)
			camera->Remove();

		// Unload the animation(s).
		for (Animation* animation : animations) {
			animation->Remove();
		}
		animations.clear();
	}

	bool App::Update() {
		if (_quit || window.ShouldClose()) 
			return false;
		
		// Draw "how-to-close" instructions.
		Renderer::GetCurrent()->DrawText("To close this demo press the \"Enter\" key on your keyboard.", font, Vector2(4, 18), Color4(0, 0, 255, 255));

		// Check if we should close the application.
		if (window.IsKeyDown(Key::Enter))
			window.Close();
		
		// Handle cursor.
		if (window.IsKeyDown(Key::F1)) {
			switch (window.GetCursorMode()) {
			case CursorMode::Active:
				window.SetCursorMode(CursorMode::Hidden);
				break;
			case CursorMode::Hidden:
				window.SetCursorMode(CursorMode::Disabled);
				break;
			case CursorMode::Disabled:
				window.SetCursorMode(CursorMode::Active);
				break;
			}
		}
		
		Core::Update(); // Updates the engine.

		return true;
	}

	// Global state for App to make access easy anywhere in code.
	static App* currentApp = nullptr;
	void App::SetCurrent(App* pCurrent) {
		currentApp = pCurrent;
	}

	App* App::GetCurrent() {
		return currentApp;
	}

	// Console command: 'quit'.
	DECLARE_CONCOMMAND(
		"quit", 
		[](ARGS pArgs) {
			currentApp->Close();
		}, 
		"Close the application."
	)
	
	// Console command: 'clear_color'.
	DECLARE_CONCOMMAND(
		"clear_color",
		[](ARGS pArgs) {
			Renderer::GetCurrent()->SetClearColor(Color4(
				pArgs.size() > 0 ? std::stoi(pArgs[0]) : 0,
				pArgs.size() > 1 ? std::stoi(pArgs[1]) : 0,
				pArgs.size() > 2 ? std::stoi(pArgs[2]) : 0,
				pArgs.size() > 3 ? std::stoi(pArgs[3]) : 0
			));
		},
		"Set the renderers clear color."
	)

	// Console command: 'entity_setpos'.
	DECLARE_CONCOMMAND(
		"entity_setpos",
		[](ARGS pArgs) {
			if (pArgs.empty()) return;
			World* world = World::GetCurrent();
			size_t entityID = Conversion::StringToNumber<int>(pArgs[0]);
			if (world->GetEntities().size() < entityID || entityID <= 0) {
				System::Print("Entity not found!");
				return;
			}
			Entity* entity = world->GetEntities()[entityID - 1];
			Vector3 newPosition;
			if (pArgs.size() > 1) newPosition.x = std::stof(pArgs[1]);
			if (pArgs.size() > 2) newPosition.y = std::stof(pArgs[2]);
			if (pArgs.size() > 3) newPosition.z = std::stof(pArgs[3]);
			entity->SetPosition(newPosition);
			System::Print("Updated " + entity->GetClass() + "'s position!");
		},
		"Set an entities positon."
	)

	// Console command: 'entity_setrot'.
	DECLARE_CONCOMMAND(
		"entity_setang",
			[](ARGS pArgs) {
			if (pArgs.empty()) return;
			World* world = World::GetCurrent();
			size_t entityID = Conversion::StringToNumber<int>(pArgs[0]);
			if (world->GetEntities().size() < entityID || entityID <= 0) {
				System::Print("Entity not found!");
				return;
			}
			Entity* entity = world->GetEntities()[entityID - 1];
			Vector3 newRotation;
			if (pArgs.size() > 1) newRotation.x = std::stof(pArgs[1]);
			if (pArgs.size() > 2) newRotation.y = std::stof(pArgs[2]);
			if (pArgs.size() > 3) newRotation.z = std::stof(pArgs[3]);
			entity->SetAngles(newRotation);
			System::Print("Updated " + entity->GetClass() + "'s rotation! [" + entity->GetRotation().GetAngles().ToString() + "]");
		},
		"Set an entities euler angles."
	)

	// Console command: 'entity_setscale'.
	DECLARE_CONCOMMAND(
		"entity_setscale",
			[](ARGS pArgs) {
			if (pArgs.empty()) return;
			World* world = World::GetCurrent();
			size_t entityID = Conversion::StringToNumber<int>(pArgs[0]);
			if (world->GetEntities().size() < entityID || entityID < 0) {
				System::Print("Entity not found!");
				return;
			}
			Entity* entity = world->GetEntities()[entityID - 1];
			Vector3 newScale(1.f, 1.f, 1.f);
			if (pArgs.size() > 1) newScale.x = std::stof(pArgs[1]);
			if (pArgs.size() > 2) newScale.y = std::stof(pArgs[2]);
			if (pArgs.size() > 3) newScale.z = std::stof(pArgs[3]);
			entity->SetScale(newScale);
			System::Print("Updated " + entity->GetClass() + "'s scale!");
		},
		"Set an entities scale."
	)

	// Console command: 'entity_setcolor'.
	DECLARE_CONCOMMAND(
		"entity_setcolor",
		[](ARGS pArgs) {
			if (pArgs.empty()) return;
			World* world = World::GetCurrent();
			size_t entityID = Conversion::StringToNumber<int>(pArgs[0]);
			if (world->GetEntities().size() < entityID || entityID < 0) {
				System::Print("Entity not found!");
				return;
			}
			Entity* entity = world->GetEntities()[entityID - 1];
			Color4 newColor;
			if (pArgs.size() > 1) newColor.r = Conversion::StringToNumber<uint32_t>(pArgs[1]);
			if (pArgs.size() > 2) newColor.g = Conversion::StringToNumber<uint32_t>(pArgs[2]);
			if (pArgs.size() > 3) newColor.b = Conversion::StringToNumber<uint32_t>(pArgs[3]);
			if (pArgs.size() > 4) newColor.a = Conversion::StringToNumber<uint32_t>(pArgs[4]);
			entity->SetColor(newColor);
			System::Print("Updated " + entity->GetClass() + "'s color!");
		},
		"Set an entities color."
	)

	// Console command: 'fov'.
	DECLARE_CONCOMMAND(
		"fov",
			[](ARGS pArgs) {
			if (pArgs.empty()) return;
			float fov = Conversion::StringToFloat<float>(pArgs[0]);
			Camera* camera = Camera::GetCurrent();
			camera->SetFOV(fov);
			System::Print("FOV updated!");
		},
		"Set the camera's fov."
	)
}
