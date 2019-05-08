/*----------------------------------/
/---------AnimationManager----------/
/-------Hale Game Engine 2017-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_ANIMATIONMANAGER
#define HALE3D_ANIMATIONMANAGER
#pragma once

/*Standard Include(s)*/
#include <vector>
#include <functional>

namespace Hale3D {
	class Entity;

	struct _AnimationObj {
		_AnimationObj() {};
		~_AnimationObj() {};

		struct {
			double start;
			double finish;
		} blend;

		std::string sequence;
		double length;
		float speed;
		bool mode;
		bool endOfSequenceReached = false;
		std::function<void(Entity*, const std::string&)> endHook;
	};


	class AnimationManager {
	public:
		AnimationManager(Entity* pEntity);
		~AnimationManager();

		virtual void SetAnimationSequence(const std::string& pSequence, const float pSpeed = 1.0f, const double pBlendTime = 500.0, const bool pMode = false, const std::function<void(Entity*, const std::string&)>& pEndHook = nullptr);
		virtual void Update();
		void ClearAnimations();

	private:
		Entity* entity;
		short frameOffset;
		std::vector<_AnimationObj> animations;
	};
}

#endif
