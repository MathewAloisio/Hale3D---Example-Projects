/*----------------------------------/
/--------------Peer-----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_PEER
#define HALE3D_NETWORK_PEER

/*
Description:	The "Peer" class describes users connected to a server.
Realm:			Serverside.
*/

#include "Network.h"
#include "../Libraries/Util.h"

/* Standard include(s). */
#include <map>
#include <array>

/*Include ENet*/
#include <enet/enet.h>

namespace Hale3D {
	namespace Network {
		class Server;
		class ChannelBuffer;

		class Peer { //lua
		public:
			Peer(Server* pServer, ENetPeer* pPeer); //lua
			virtual ~Peer(); //lua

			/*Variables*/
			double m_DroppedTime;

			virtual void OnConnected() {};
			virtual void OnDisconnect(const std::string& pReason) {};

			void Send(Channel pChannel, uint8_t* pData, size_t pSize);
			void Ready();
			bool IsReady(); //lua
			bool IsDropped(); //lua
			void Drop(const std::string& pReason); //lua
			void Flush(); //WARNING: This method is called in a worker thread! DO NOT USE IT MANUALLY UNLESS YOU HAVE A REASON TO AND KNOW WHAT YOU'RE DOING!
			void DoDisconnect(const std::string& pReason);
			std::string GetDroppedReason() const; //lua

			/*Bandwidth*/
			uint32_t GetIncomingBandwidth() const; //lua
			uint32_t GetOutgoingBandwidth() const; //lua

			/*Packet*/
			uint32_t GetPacketsLost() const; //lua
			uint32_t GetPacketsSent() const; //lua
			uint32_t GetPacketLoss() const; //lua

			/*Identity*/
			uint32_t GetIP() const; //lua
			uint16_t GetPort() const; //lua

			/*Round trip*/
			uint32_t GetRTT() const; //lua
			uint32_t GetLastRTT() const; //lua
			uint32_t GetRTTVariance() const; //lua

			void SetUserID(uint16_t pID);
			uint16_t GetUserID() const; //lua

			ENetPeer* GetPeer();

		private:
			uint16_t _id;

			struct {
				bool m_Ready = false;
				bool m_Dropped = false;
				std::string m_DroppedReason;
			} _states;

			Server* _server;
			ENetPeer* _peer;
			std::array<ChannelBuffer*, Conversion::ToUnderlyingType(Channel::_END)> _channels;
		};
	}
}
#endif
