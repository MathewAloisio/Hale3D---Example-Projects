/*----------------------------------/
/--------------Host-----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_HOST
#define HALE3D_NETWORK_HOST

/*
Description:	The "Host" class describes a base for which the server and the client are derived from.
Realm:			Purely virtual, (Cannot be instantiated on it's own.)
*/

#include "Network.h"

/*Include ENet*/
#include <enet/enet.h>

/* Standard include(s). */
#include <map>
#include <array>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

namespace Hale3D {
	namespace Network {
		class Interface;

		class Host { //lua
		public:
			Host();
			virtual ~Host() = default;

			virtual void Update() {}
			virtual void OnDisconnected() {}
			virtual bool IsMasterServer() const; //lua
			virtual bool IsServer() const; //lua
			virtual bool IsClient() const; //lua

			virtual std::string GetType() const; //lua

			/*Threaded*/
			virtual void PollHost() {};

			/*Management*/
			void SetInterface(Interface* pInterface);

		protected:
			/*Threading*/
			struct {
				bool m_Closing = false;
				std::thread m_Worker;
				std::mutex m_Mute;
				std::condition_variable m_Condition;
			} _thread;

			void __DestroyWorker();

			/*Management*/
			Interface* _interface = nullptr;
		};
	};
}
#endif
