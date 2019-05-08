#ifndef ANIMATIONDEMO_APP
#define ANIMATIONDEMO_APP
#pragma once
#include "Engine/Core/World.h"
#include "Engine/2D/World2D.h"
#include "Engine/Rendering/Window.h"

#include <string>

namespace Hale3D {
	class Font;
	class Camera;
	class App {
	public:
		/* Constructor(s) & destructor(s). */
		App(const std::string& pTitle);
		
		/* Member(s). */
		Font* font;
		Camera* camera;
		Window window;
		World world;
		World2D world2D;
		
		/* Method(s). */
		void Start();
		void Close();
		void OnExit();
		bool Update();
		
		/* Static method(s). */
		static void SetCurrent(App* pCurrent);
		static App* GetCurrent();

	private:
		bool _quit;
	};
}

#endif