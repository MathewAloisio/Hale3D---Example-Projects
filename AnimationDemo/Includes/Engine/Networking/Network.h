/*----------------------------------/
/------------Network---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_NETWORK
#define HALE3D_NETWORK_NETWORK

/* Standard include(s). */
#include <stdint.h>

namespace Hale3D { 
	namespace Network {
		class Host;

		/*Hard-Coded Limitations*/
		static constexpr size_t MESSAGE_NAME_LIMIT = 25;

		/*Network Chanels*/
		enum class Channel : uint8_t { //lua
			Reliable,
			Unreliable,
			Unsequenced,
			_END
		};

		/*Host Tracking.*/
		void SetHost(Host* pHost); //lua
		Host* GetHost(); //lua
	}
}

#endif
