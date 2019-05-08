/*----------------------------------/
/----------PhysicsMaterial----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_PHYSICSMATERIAL
#define HALE3D_PHYSICSMATERIAL

/* Standard include(s). */
#include <string>

namespace Hale3D {
	// A set of physics coefficient combination behaviors that will ensure the coefficients always stay within arange of 0-1.
	enum class PhysicsCombine : uint8_t {
		Average,	// Adds two coefficients and uses the average.
		Minimum,	// Uses the smaller of two coefficients.
		Maximum,	// Uses the larger of two coefficients.
		Multiply	// Uses the result of multiplying the first coefficient by the second.
	};

	class PhysicsMaterial {
	public:
		/* Constructor(s) & destructor(s). */
		PhysicsMaterial();

		/* General. */
		void SetBounciness(float pBounciness); // Bounciness => Coefficient of Restitution.
		float GetBounciness();

		void SetBouncinessCombine(PhysicsCombine pPhysicsCombine); // Bounciness => Coefficient of Restitution.
		PhysicsCombine GetBouncinessCombine();
		
		void SetDynamicFriction(float pDynamicFrictionCoefficient);
		float GetDynamicFriction();

		void SetDynamicFrictionCombine(PhysicsCombine pPhysicsCombine);
		PhysicsCombine GetDynamicFrictionCombine();
		
		void SetStaticFriction(float pStaticFrictionCoefficient);
		float GetStaticFriction();

		void SetStaticFrictionCombine(PhysicsCombine pPhysicsCombine);
		PhysicsCombine GetStaticFrictionCombine();
		
		/* Save & load.*/
		bool Save(const std::string& pPath, bool pOverwrite = false);
		
		/* Static method(s). */
		static PhysicsMaterial Load(const std::string& pPath);

		/* Static constant member(s). */
		static constexpr uint32_t UniqueIdentifier = ('T' << 24) + ('A' << 16) + ('M' << 8) + 'P'; // Used to confirm that a file contains an engine-supported physics material.
		static constexpr uint16_t CurrentVersion = 1;
	
	private:
		float _bounciness; // 0 = No bounce / 1 = Bounces forever.
		PhysicsCombine _bouncinessCombine;

		float _dynamicFriction; // 0 = No dynamic friction / 1 = Full dynamic friction.
		PhysicsCombine _dynamicFrictionCombine;

		float _staticFriction; // 0 = No static friction / 1 = Full static friction.
		PhysicsCombine _staticFrictionCombine;
	};
}

#endif
