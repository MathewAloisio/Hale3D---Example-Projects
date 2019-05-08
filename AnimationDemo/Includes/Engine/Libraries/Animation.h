/*----------------------------------/
/------------Animation--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_ANIMATION
#define HALE3D_ANIMATION

#include "../Core/Object.h"
#include "../Structs/AABB.h"
#include "../Structs/Vertex.h"
#include "../Structs/Quaternion.h"
#include "../Structs/EnumerateArray.h"
#include "../Structs/ReferenceTable.h"

/* Standard include(s). */
#include <string>
#include <cstdint>

namespace Hale3D {
	class ExpandingBuffer;
	struct BaseFrameJoint {
		Vector3 m_Position;
		Quaternion m_Orientation;
	};

	struct JointInfo {
		int32_t m_Parent;
		uint32_t m_Flags;
		uint32_t m_StartIndex;
		std::string m_Name;
	};

	/*Both*/
	struct Joint {
		int32_t m_Parent;
		Vector3 m_Position;
		Quaternion m_Orientation;
		std::string m_Name;
	};
	typedef std::vector<Joint> Skeleton;
	/*---*/

	class Animation;
	enum class AnimationPlayMode : uint8_t { //lua
		Forward,
		Backward,
		Alternating
	};

	enum class AnimationCallback : uint8_t { //lua
		Play,
		Pause,
		Finish,
		Repeat
	};

	class AnimatedJoint {
	public:
		AnimatedJoint(std::string pName);

		void PlayAnimation(Animation* pAnimation, uint32_t pRepeatCount = 1, AnimationPlayMode pPlayMode = AnimationPlayMode::Forward);
		void SetAnimation(Animation* pAnimation);
		Animation* GetAnimation();
		const Animation* GetAnimation() const;

		void Update(double pDelta);

		void SetTime(double pTime);
		double GetTime() const;

		void SetCallback(AnimationCallback pCallbackKey, std::function<void()> pCallbackFunc);
		const std::function<void()> GetCallback(AnimationCallback pCallbackKey) const;

		void Play();
		void Pause();
		bool IsPlaying() const;

		uint32_t GetLastFrame() const;
		uint32_t GetNextFrame() const;

		const std::string& GetName() const;

		void SetRepeatCount(uint32_t pRepeatCount);
		uint32_t GetRepeatCount() const;

		uint32_t GetTimesRepeated() const;

		void SetPlayMode(AnimationPlayMode pPlayMode);
		AnimationPlayMode GetPlayMode() const;

		bool operator==(const AnimatedJoint& pInstance) {
			return (_animation == nullptr && pInstance._animation == nullptr) ||
				(_frame.next == pInstance._frame.next && _frame.last == pInstance._frame.last && _animation == pInstance._animation); //TODO: Possibly have to compare paths if un-cached animations become a thing.
		}

		bool operator!=(const AnimatedJoint& pInstance) {
			return !(*this == pInstance);
		}

	private:
		// General.
		bool _playing;
		double _time; // Time animation has been playing for.
		uint32_t _timesRepeated;
		uint32_t _repeatCount; //The # of times the animation should repeat. (NOTE: 0 for infinite.)
		struct {
			uint32_t last;
			uint32_t next;
		} _frame;
		std::string _name;
		AnimationPlayMode _playMode;
		AnimationPlayMode _altPlayMode; // To keep track of the sub-play mode when _playMode is set to alternating.
		Animation* _animation;

		// Callbacks.
		EnumerateArray<AnimationCallback, std::function<void()>, 4> _callbacks;
	};

	class AnimatedSkeleton : public std::vector<AnimatedJoint> {
	public:
		AnimatedSkeleton() = default;
		AnimatedSkeleton(const Skeleton& pSkeleton);
	};

	/* Animation. */
	class Animation : public Object {
	public:
		//bool Save(const std::string& pPath, bool pOverwrite = false) const;
		bool IsValid() const;
		bool IsVersion(uint32_t pVersion) const;
		bool IsSkeletonSupported(const Skeleton& pSkeleton) const;
		std::string GetPath() const;

		void SetFrameRate(uint32_t pFrameRate);
		uint32_t GetFrameRate() const;

		uint32_t GetID() const;
		uint32_t GetVersion() const;
		uint32_t GetFrameCount() const;
		uint32_t GetJointCount() const;

		double GetFrameDuration() const;
		double GetDuration() const;

		virtual void Remove();

		std::vector<AABB> m_BoundingBoxes;
		std::vector<Skeleton> m_SkeletonFrames;

		/* Static method(s). */
		static Animation* Load(const std::string& pPath);
		static void InterpolateJoint(const Joint& pJointA, const Joint& pJointB, float pBlend, Joint& pJointOut);
		static void InterpolateSkeletons(const Skeleton& pSkelA, const Skeleton& pSkelB, float pBlend, Skeleton& pSkelOut);

		/* Static constant member(s). */
		static constexpr uint32_t UniqueIdentifier = ('A' << 24) + ('D' << 16) + ('3' << 8) + 'H'; // Used to confirm that a file contains an engine-supported animation.
		static const uint32_t CurrentVersion;

	private:
		std::string _path;

		uint32_t _id; // Should equal UniqueIdentifier after the model is loaded.
		uint32_t _version;

		uint32_t _frameRate;
		uint32_t _frameCount;
		uint32_t _jointCount;

		double _frameDuration;
		double _duration;

		/* Reference counting. */
		static ReferenceTable<Animation*> _animationReference;

		/*Static Private Methods*/
		static void __ReadData(Animation& pAnimation, ExpandingBuffer& pBuffer);
	};
}

#endif
