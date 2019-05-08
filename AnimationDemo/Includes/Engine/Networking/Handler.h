/*----------------------------------/
/-------------Handler---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_HANDLER
#define HALE3D_NETWORK_HANDLER

#include "../Libraries/Util.h"

/* Standard include(s). */
#include <string>
#include <map>

/*Helper macros*/
#define DECLARE_NETWORK_HANDLER(MSG_NAME, MSG_HANDLE) \
    static Hale3D::Network::Handler::CompileMsgHndl CREATE_VAR_NAME(compilenethndl, __LINE__)(MSG_NAME, MSG_HANDLE);

namespace Hale3D {
	namespace Network {
		class Peer;
		class Host;
		class Message;
		class Reader;

		namespace Handler {
			/*Type Definitions*/
			typedef void(*CallbackFunc)(Host*, Peer*, Reader*);

			/*'CompileMsgHndl' | For static initialization.*/
			struct CompileMsgHndl {
				CompileMsgHndl(const std::string& pName, CallbackFunc pCallback);
			};

			/* Method(s). */
			std::map<uint16_t, CallbackFunc>& GetMessageHandlers();
			std::map<std::string, CallbackFunc>& GetMessageHandlerCache();

			/*Internal Methods*/
			void BuildHandler(const std::string& pName, uint16_t pID);
			void BuildHandlers();

			/* Method(s). */
			void Register(const std::string& pName, CallbackFunc pCallback);
			void Execute(Host* pHost, uint16_t pMessageID, Peer* pPeer, Reader* pReader);
		}
	}
}

#endif
