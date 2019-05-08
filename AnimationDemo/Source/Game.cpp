#include "Game.h"
#include "App.h"
#include "Engine/Core.h"
#include "Engine/Libraries/LuaHook.h"
#include "Engine/Libraries/FileSystem.h"
#include "Engine/Libraries/Interpreter.h"

// Renderer Include
#include "Renderers/OpenGLRenderer.h" // This can be switched out by downloading and compiling one of the renderer implementations for Hale3D.

// NOTE: Only edit this file if you know what you're doing. Consider editing App.h & App.cpp instead!
// NOTE: Game.cpp is the entry-point for your game, it initializes the engine and your customizable 'App' class.
int main(int argc, const char* argv[]) {
	// Tell the engine which renderer to use.
	Hale3D::Renderer::SetCurrent(new Hale3D::OpenGLRenderer());

	// Start the engine.
	Hale3D::Core::Start(argc, argv); // Initializes the engine, the engine must be started before an 'App' is created.
	
	// Launch main Lua script.
	if (Hale3D::FileSystem::Exists(SCRIPT_PATH)) {
		Hale3D::Interpreter::GLOBAL.ExecuteFile(SCRIPT_PATH);
	}
	
	// Call engine started LuaHook.
	Hale3D::LuaHook::Run("Engine::OnStarted");
	
	// Create the app entry point and use its update function for the games main loop.
	Hale3D::App app(APP_TITLE);
	while (app.Update()) {} // Code under the Update loop will ONLY be executed when the game's shutting down.
	app.OnExit();
	
	// Tell the engine it may free its allocated resources.
	Hale3D::Core::Stop();
}