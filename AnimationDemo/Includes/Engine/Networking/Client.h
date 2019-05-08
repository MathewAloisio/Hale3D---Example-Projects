/*----------------------------------/
/-------------Client----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_CLIENT
#define HALE3D_NETWORK_CLIENT

/*
Description:	The "Client" class describes a host who can create and manage a connection with a server.
Realm:			Clientside.
*/

#include "Host.h"
#include "../Libraries/Util.h"

namespace Hale3D {
	namespace Network {
		class Message;
		class Peer;
		class Packet;
		class ChannelBuffer;
		class ClientInterface;

		class Client : public Host { //lua
		public:
			Client(); //lua
			virtual ~Client(); //lua

			struct {
				uint32_t m_IncomingBandwidth;
				uint32_t m_OutgoingBandwidth;
			} m_Config;

			struct {
				ENetAddress m_Address;
				ENetHost* m_Host;
				::ENetPeer* m_Peer;
			} m_Components;

			/*Management*/
			ClientInterface* GetInterface();

			void Connect(const std::string& pHost, uint16_t pPort); //lua
			void Disconnect(); //lua
			void OnDropped(const std::string& pReason);
			void OnConnected();
			void OnDisconnected();
			bool IsConnected() const; //lua

			virtual void Update();
			virtual bool IsClient() const {
				return true;
			}

			virtual std::string GetType() const {
				return "Client";
			}

			/*Threaded*/
			virtual void PollHost();

			/*Message*/
			void SendToServer(Message* pMessage, Channel pChannel = Channel::Reliable); //lua

		private:
			struct {
				bool m_Connected = false;
				ENetAddress m_Address;
				std::vector<ENetEvent> m_Events;
				std::array<ChannelBuffer*, Conversion::ToUnderlyingType(Channel::_END)> m_Channels;
			} _states;

			void __Flush();
			void __ReadPacket(uint8_t* pData, size_t pSize);
		};
	}
}
#endif
