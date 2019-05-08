/*----------------------------------/
/---------Channel Buffer------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_CHANNELBUFFER
#define HALE3D_NETWORK_CHANNELBUFFER

#include "Packet.h"
#include "Network.h"

/* Standard include(s). */
#include <queue>

namespace Hale3D {
	namespace Network {
		const short maxFreePackets = 64; // The maximum amount of packets that can be in the freePacket queue.

		class ChannelBuffer { // A base ChannelBuffer class specific channel buffers inherit from.
		public:
			virtual void Send(uint8_t* pData, size_t pSize) = 0;
			virtual void Flush() = 0;

			bool IsReliable() const;

		protected:
			bool _reliable;
			Channel _channel;
			static std::queue<Packet*> _freeReliablePackets; // A queue of available reliable packets shared amongst all reliable channel buffers.
		};
	}
}
#endif
