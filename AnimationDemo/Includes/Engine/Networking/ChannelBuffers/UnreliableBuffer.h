#ifndef HALE3D_NETWORK_CHANNELBUFFER_UNRELIABLE
#define HALE3D_NETWORK_CHANNELBUFFER_UNRELIABLE

#include "../ChannelBuffer.h"

namespace Hale3D {
	namespace Network {
		class UnreliableBuffer : public ChannelBuffer {
		public:
			UnreliableBuffer(ENetPeer* pPeer, Channel pChannel, size_t pSize);
			~UnreliableBuffer();

			/*Operator Overload(s)*/
			UnreliableBuffer& operator=(const UnreliableBuffer& pOther) {
				if (this == &pOther) return *this;
				delete _packet;
				_packet = pOther._packet;
				return *this;
			}

			virtual void Send(uint8_t* data, size_t pSize) override;
			virtual void Flush() override;

		private:
			size_t _size;
			ENetPeer* _peer;
			Packet* _packet;
		};
	}
}

#endif
