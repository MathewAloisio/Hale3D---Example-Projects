/*----------------------------------/
/-------------Camera----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_CAMERA
#define HALE3D_CAMERA

#include "../Core/Entity.h"
#include "../Structs/Vector2.h"
#include "../Structs/Matrix4.h"
#include "../Rendering/Frustum.h"

/* Standard include(s). */
#include <vector>

namespace Hale3D {
	class World;
	class Skybox;
	class Camera : public Entity { //lua
	public:
		DECLARE_ENTITY_CLASS(Camera) //lua

		/* Constructor(s) & destructor(s). */
		Camera();
		virtual ~Camera();

		/* Virtual method(s). */
		virtual void SetPosition(const Vector3& pPosition);
		virtual void SetAngles(const Vector3& pAngles);
		virtual void SetRotation(const Quaternion& pRotation);

		virtual bool IsCamera() {
			return true;
		}

		/* Overrideable event(s). */
		virtual void OnMadeCurrent() {};
		virtual void OnMadeNonCurrent() {};

		/* Skybox. */
		void SetSkybox(const std::string& pPath);
		Skybox* GetSkybox() const;

		/* Metohd(s). */
		void LookAt(const Vector3& pPosition); //lua
		void SetPerspective(float pFOV, float pAspect, float pZNear, float pZFar); //lua

		void SetViewDistance(float pDistance); //lua
		float GetViewDistance() const; //lua (zFar)

		void SetZNear(float pDistance); //lua
		float GetZNear() const; //lua

		Matrix4 GetMatrix() const; //lua
		const Matrix4& GetView() const; // lua
		const Matrix4& GetPerspective() const; //lua

		void SetFOV(float pFOV); //lua
		float GetFOV() const; //lua

		void SetAspectRatio(float pAspectRatio); //lua
		float GetAspectRatio() const; //lua

		float GetTangentFactorFOVY() const; //lua
		const Vector2& GetSphereFactor() const; //lua

		void RecalculatePVMatrix(); //lua
		void RebuildViewMatrix(); //lua
		void RebuildPerspectiveMatrix(); //lua

		void RenderVisibleEntities(); //lua
		void RecalculateVisibleEntities(const std::vector<Entity*>& pEntities);
		const std::vector<Entity*>& GetVisisbleEntities() const;

		// Radar approach frustum culling.
		bool CheckFrustumSphereRadar(const Vector3& pSphereCenter, float pSphereRadius, const Vector3& pUp, const Vector3& pRight, const Vector3& pForward) const; //lua

		/* Static methods. */
		static void SetCurrent(Camera* pCamera);
		static Camera* GetCurrent();

	protected:
		float _FOV;
		float _zNear;
		float _zFar;
		float _aspectRatio;
		float _tangentFactorFOVY;
		Skybox* _skybox;
		Frustum _frustum;
		Vector2 _sphereFactor;
		std::vector<Entity*> _visibleEntities;

		struct {
			Matrix4 perspective;
			Matrix4 view;
			Matrix4 perspectiveView;
		} _matrices;
	};
}

#endif
