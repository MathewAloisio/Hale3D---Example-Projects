/*----------------------------------/
/-------------Entity----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_ENTITY
#define HALE3D_ENTITY

/* Hale3D includes. */
#include "Object.h"
#include "../BuildConfig.h"
#include "../Structs/Color4.h"
#include "../Structs/Vertex.h"
#include "../Structs/Matrix4.h"
#include "../Structs/Transform.h"
#include "../Libraries/Model.h"
#include "../Libraries/Material.h"
#include "../Libraries/EntManager.h"
#include "../Physics/PhysicsCollider.h"

/* Standard includes. */
#include <queue>
#include <string>
#include <vector>

namespace Hale3D {
	class World;
	class Camera;

	class Entity : public Object { //lua
	public:
		DECLARE_ENTITY_CLASS(Entity) //lua

		/* Constructor(s) & destructor(s). */
		Entity();
		virtual ~Entity();
	
		/* Update methods. */
		virtual void Update() {};
		virtual void FixedUpdate() {};

		/* Is<Type> methods. */
		virtual bool IsCamera(); //lua
		virtual bool IsVehicle(); //lua
		virtual bool IsPlayer(); //lua
		virtual bool IsWeapon(); //lua
		virtual bool IsDoor(); //lua

		/* Virtual methods. */
		virtual void OnSpawned() {};
		virtual void OnDespawned() {};
		virtual void OnInitialized() {};
		virtual void OnDeinitialized() {};
		virtual void OnPreDraw(Camera* pCamera) {};
		virtual void OnPostDraw(Camera* pCamera) {};
		virtual bool ShouldDraw(Camera* pCamera) { return true; };

		virtual void SetPosition(const Vector3& pPosition); //lua
		virtual void SetAngles(const Vector3& pAngles); //lua
		virtual void SetRotation(const Quaternion& pRotation); //lua
		virtual void SetScale(const Vector3& pScale); //lua

		/* Methods. */
		void Spawn(); //lua
		void Despawn(); //lua
		void Initialize(); //lua
		void Deinitialize(); //lua
		void __AddChild(Entity* pChild); // Interal use only!
		void __RemoveChild(Entity* pChild); // Internal use only!
		void __RemoveChild(size_t pIndex); // Internal use only!
		void SetParent(Entity* pParent = nullptr); //lua
		void SetNoDraw(const bool pNoDraw); //lua
		void SetMaterial(size_t pIndex = -1, const std::string& pPath = ""); //lua
		void SetMaterialOverride(const std::string& pPath = ""); //lua
		void SetModel(const std::string& pPath = ""); //lua
		void SetColor(const Color4& pColor); //lua

		void PreDraw(Camera* pCamera); // NOTE: This MUST NOT be called by the engine, it MUST be called by the external renderer implementation. (See "Renderer Standard.md")
		void PostDraw(Camera* pCamera); // NOTE: This MUST NOT be called by the engine, it MUST be called by the external renderer implementation. (See "Renderer Standard.md")

		bool IsInitialized(); //lua
		bool GetNoDraw(); //lua
		bool IsCulled(Camera* pCamera); //lua
		bool IsCulledByAllCameras(); //lua
		bool IsSpawned(); //lua
		bool HasVisibleMaterial(); //lua
		Model* GetModel() const; //lua
		Material* GetMaterial(size_t pIndex); //lua
		Material* GetMaterialOverride(); //lua
		const MaterialArray& GetMaterials() const; //lua

		void SetClass(const std::string& pClassName); //lua
		std::string GetClass() const; //lua

		Entity* GetParent(); //lua
		std::vector<Entity*>& GetChildren(); //TODO: Make ToLua++ support std::vectors and std::lists.

		Vector3 GetPosition() const; //lua
		Vector3 GetScale() const; //lua
		Vector3 GetAngles() const; //lua
		Color4 GetColor() const; //lua
		Quaternion GetRotation() const; //lua
		Matrix4 GetTransformMatrix() const; //lua

		void PlayAnimation(Animation* pAnimation, uint32_t pRepeatCount = 1, AnimationPlayMode pPlayMode = AnimationPlayMode::Forward);
		void ClearAnimations(); //lua

		AnimatedJoint* GetJoint(size_t pIndex);
		AnimatedJoint* FindJoint(const std::string& pName);
		AnimatedSkeleton& GetJoints();

		// Physics method(s).
		void SetPhysicsShape(PhysicsShape pShape); // Sets a physics shape by generating or using a cached one from the PhysicsShape type enumeration.									| Side effect(s): Sets this entity's PhysicsCollider, deletes currently pointed-to PhysicsCollider if set by a function other than "SetPhysicsCollider(PhysicsCollider* pCollider)". The engine will manage the generated collision shape.
		void SetPhysicsShape(const std::string& pPath); // Sets a physics shape by loading a physics shape file, automatically sets the entity's PhysicsShape to PhysicsShape::Custom.	| Side effect(s): Sets this entity's PhysicsCollider, deletes currently pointed-to PhysicsCollider if set by a function other than "SetPhysicsCollider(PhysicsCollider* pCollider)". The engine will manage the generated collision shape.
		void SetPhysicsCollider(PhysicsCollider* pCollider); // Directly sets this entity to use a PhysicsCollider at a given address.													| Side effect(s): Sets this entity's PhysicsCollider without taking responsibility for the creation or deletion of pCollider. The engine WILL NOT take responsibility for the ceation or deletion of this system.
		PhysicsShape GetPhysicsShape() const;

		const PhysicsCollider* GetPhysicsCollider() const; // Returns a read-only pointer of this entity's current PhysicsCollider, or nullptr if there is none.

		/* Lua communication. */
		void RunLuaFunction(const std::string& pFuncName, int pArgCount = 0, const std::function<void()>& pArgsFn = nullptr);
		bool CallLuaFunction(const std::string& pFuncName, bool pDefaultReturn = true, int pArgCount = 0, const std::function<void()>& pArgsFn = nullptr);

		/* Model & mesh buffers. */
		ModelBuffer& GetModelBuffer();
		// Mesh buffers to be drawn.
		const std::vector<MeshBuffer>& GetMeshBuffers() const;

	protected:
		// General
		bool _nodraw;
		bool _spawned;
		bool _initialized;
		bool _managingPhysicsCollider;
		World* _world;
		Entity* _parent;
		Color4 _color;
		Transform _transform;
		std::string _className;
		std::vector<Entity*> _children;

		// Materials
		Material* _materialOverride;
		MaterialArray _materials; // These materials, by default, correspond to the material of the mesh with a matching index.

		// Models, Meshes and animation.
		Model* _model;
		ModelBuffer _modelBuffer;
		AnimatedSkeleton _animatedSkeleton;

		// Physics.
		PhysicsShape _physicsShape;
		PhysicsCollider* _physicsCollider;
	};
}

#endif
