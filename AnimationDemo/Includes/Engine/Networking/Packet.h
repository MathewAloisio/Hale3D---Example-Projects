/*----------------------------------/
/-------------Packet----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_PACKET
#define HALE3D_NETWORK_PACKET

#include "Network.h"

/* Standard include(s). */
#include <stdint.h>

/*Include ENet*/
#include <enet/enet.h>

namespace Hale3D {
	namespace Network {
		class Packet {
		public:
			Packet(size_t pSize, bool pReliable);
			~Packet();

			bool IsEmpty();
			bool HasSpace(size_t pSize);
			void Reset();
			void Write(uint8_t* pValue, size_t pSize);
			void Send(ENetPeer* pPeer, Channel pChannel);
			bool IsReliable() const;
			size_t GetSize() const;
			size_t GetPosition() const;
			
			uint8_t* m_Buffer;

		private:
			bool _reliable;
			size_t _size;
			size_t _position = 0;
		};
	}
}
#endif
