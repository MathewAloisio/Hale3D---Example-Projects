#ifndef HALE3D_NETWORK_CHANNELBUFFER_RELIABLE
#define HALE3D_NETWORK_CHANNELBUFFER_RELIABLE

#include "../ChannelBuffer.h"

namespace Hale3D {
	namespace Network {
		class ReliableBuffer : public ChannelBuffer {
		public:
			ReliableBuffer(ENetPeer* pPeer, Channel pChannel, size_t pSize);
			~ReliableBuffer();

			ReliableBuffer& operator=(const ReliableBuffer& pOther) {
				if (this == &pOther) return *this;

				FreePacket(_packet);
				_packet = pOther._packet;

				return *this;
			}

			virtual void Send(uint8_t* data, size_t pSize) override;
			virtual void Flush() override;

			Packet* NextPacket();
			void PushPacket();
			void FreePacket(Packet* pPacket);

		private:
#ifdef DEBUG
			static const unsigned short _packetCountWarning = 12;
#endif

			size_t _size;
			ENetPeer* _peer;
			Packet* _packet; // The packet that we're currently writing to the buffer.
			std::queue<Packet*> _packets; // The packets in this specific ChannelBuffer.
		};
	}
}

#endif
