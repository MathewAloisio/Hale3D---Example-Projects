/*----------------------------------/
/-------------Server----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_SERVER
#define HALE3D_NETWORK_SERVER

/*
Description:	The "Server" class describes a host who's acting as a server.
Realm:			Serverside.
*/

#include "Host.h"
#include "Peer.h"

namespace Hale3D {
	namespace Network {
		class Message;
		class Packet;
		class ServerInterface;

		class Server : public Host { //lua
		public:
			Server(); //lua
			virtual ~Server(); //lua

			struct {
				uint16_t m_Port;
				uint16_t m_Tickrate = 60;
				uint16_t m_MaxPlayers = 32;
				uint32_t m_DropDelay = 2000; // Drop peer delay in milliseconds. (Time allowed for graceful disconnection after dropping a peer.)
				uint32_t m_IncomingBandwidth = 0; // Assume any amount when 0.
				uint32_t m_OutgoingBandwidth = 0; // Assume any amount when 0.
				std::string m_HostOverride;
			} m_Config;

			struct {
				ENetAddress m_Address;
				ENetHost* m_Host;
			} m_Components;

			void Start(uint16_t pPort = 0); //lua
			void Stop(); //lua
			bool IsStarted() const; //lua
			uint16_t GetMaxPlayers(); //lua

			virtual void Update();
			virtual bool IsServer() const {
				return true;
			};

			virtual std::string GetType() const {
				return "Server";
			}

			/*Threaded*/
			virtual void PollHost();

			/*Management*/
			ServerInterface* GetInterface();

			/*Peer management.*/
			std::map<uint16_t, Peer*> GetAllPeers() const;
			Peer* GetPeer(uint16_t pID); //lua
			bool IsConnected(uint16_t pID) const; //lua

			void AddPeer(Peer* pPeer); // Adds a 'Peer' object to the 'states.peers' map. Returns the peers's assigned ID.
			void DropPeer(Peer* pPeer, const std::string& pReason);
			void RemovePeer(Peer* pPeer, bool pForceDrop = false);
			void DestroyPeers();
			void SetDropDelay(uint32_t pDropDelay); //lua

			/*Message*/
			void Send(Message* pMessage, Peer* pPeer, Channel pChannel = Channel::Reliable); //lua
			void Broadcast(Message* pMessage, Channel pChannel = Channel::Reliable); //lua
			void SendMessageMap(Peer* pPeer);

		private:
			struct {
				bool m_Started = false;
				std::vector<ENetEvent> m_Events;
				std::map<unsigned short, Peer*> m_Peers;
			} _states;

			void __ReadPacket(Peer* pPeer, uint8_t* pData, size_t pSize);
		};
	}
}
#endif
