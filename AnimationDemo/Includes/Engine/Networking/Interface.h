/*----------------------------------/
/------------Interface--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_INTERFACE
#define HALE3D_NETWORK_INTERFACE

/*
Description:	The "Interface" class describes a base for which the programmer can inherit from and add/change network events.
Realm:			Pure virtual. (Cannot be instantiated on it's own.)
*/

#include "Network.h"
#include "Server.h"
#include "Client.h"

/* Standard include(s). */
#include <string>

namespace Hale3D {
	namespace Network {
		class Interface {
		public:
			Interface() = default;
			virtual ~Interface() = default;
		};

		class ClientInterface : public Interface {
		public:
			ClientInterface(Client* pClient);
			virtual ~ClientInterface();

			virtual void OnConnected() {}
			virtual void OnDisconnect() {}
			virtual void OnDropped(const std::string& pReason) {}

		protected:
			Client* client;
		};

		class ServerInterface : public Interface {
		public:
			ServerInterface(Server* pServer);
			virtual ~ServerInterface();

			virtual void OnPeerConnected(Peer* pPeer) {}
			virtual void OnPeerDisconnected(Peer* pPeer, bool pDropped) {}
			virtual void OnStarted() {}
			virtual void OnStopped() {}

		protected:
			Server* server;
		};
	}
}
#endif
