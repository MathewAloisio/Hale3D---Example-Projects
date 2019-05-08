/*----------------------------------/
/-----------MasterServer------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_MASTERSERVER
#define HALE3D_NETWORK_MASTERSERVER

/*
Description:	The "MasterServer" class describes a host who's acting as a server list.
Realm:			Serverside.
*/

#include "Host.h"

namespace Hale3D {
	namespace Network {
		struct ServerInfo { //lua
			
		};
		
		class MasterServer : public Host { //lua
		public:
			MasterServer(); //lua
			~MasterServer(); //lua

			struct {
				uint16_t port;
				uint16_t maxConnections = 32;
				uint32_t dropDelay = 2000; // Drop peer delay in milliseconds. (Time allowed for graceful disconnection after dropping a peer.)
				uint32_t incomingBandwidth = 0; // Assume any amount when 0.
				uint32_t outgoingBandwidth = 0; // Assume any amount when 0.
				double updateDelay;
				std::string hostOverride;
			} config;

			struct {
				ENetAddress address;
				ENetHost* host;
			} components;

			void Start(uint16_t pPort = 0); //lua
			void Stop(); //lua

			virtual void Update();
			virtual bool IsMasterServer() const {
				return true;
			};

			virtual std::string GetType() const {
				return "MasterServer";
			}

			/*Threaded*/
			virtual void PollHost();

			/*Server management.*/
			std::map<uint32_t, ServerInfo> GetAllServers() const;
			ServerInfo GetServer(uint32_t pAddress) const;
			bool IsConnected(uint32_t pAddress) const; //lua

		private:
			struct {
				bool started = false;
				std::vector<ENetEvent> events;
			} states;

			std::map<uint32_t, ServerInfo> servers;

			/*Server management (private).*/
			
			/*Packet handling*/
			 void __ReadPacket(uint32_t pAddress, uint8_t* pData, size_t pSize);
		};
	}
}
#endif
