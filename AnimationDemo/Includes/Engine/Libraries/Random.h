/*----------------------------------/
/--------------Random---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_RANDOM
#define HALE3D_RANDOM

/* Standard include(s). */
#include <random>

namespace Hale3D {
	namespace Random {
		static std::random_device _device;
		static std::mt19937_64 _generator64 { _device() };

		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		T Number(const T pMin, const T pMax) {
			std::uniform_int_distribution<T> distribution(pMin, pMax);
			return distribution(_generator64);
		}

		template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
		T Float(const T pMin, const T pMax) {
			std::uniform_real_distribution<T> distribution(pMin, pMax);
			return distribution(_generator64);
		}
	}
}

#endif
