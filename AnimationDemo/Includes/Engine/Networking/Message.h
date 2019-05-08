/*----------------------------------/
/-------------Message---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_MESSAGE
#define HALE3D_NETWORK_MESSAGE

/*
Description:	The "Message" class describes a class used to write information about objects that will be streamed across the network.
Realm:			Shared.
*/

#include "../Libraries/Util.h"
#include "../Structs/ExpandingBuffer.h"

/* Standard include(s). */
#include <map>
#include <string>
#include <unordered_map>

namespace Hale3D {
	namespace Network {
		struct _CompileMsg {
			_CompileMsg(const std::string& pName);
		};

		class Message { //lua
		public:
			/* Constructor(s) & destructor(s). */
			Message(const std::string& pName, size_t pSize = 64); //lua
			~Message(); //lua

			size_t GetSize(); //lua
			uint8_t* GetData();
			void WriteFloat(float pValue); //lua
			void WriteDouble(double pValue); //lua
			void WriteBool(bool pValue); //lua
			void WriteUInt8(uint8_t pValue); //lua
			void WriteUInt16(uint16_t pValue); //lua
			void WriteUInt32(uint32_t pValue); //lua
			void WriteString(const char* pValue); //lua
			void WriteString(const std::string& pValue);
			void WriteUInt8Array(uint8_t* pExpandingBuffer, size_t pSize);
			void UpdateHeader(); //lua

			/*Hale3D Types*/
			void WriteVector2(const Vector2& pValue); //lua
			void WriteVector3(const Vector3& pValue); //lua
			void WriteVector4(const Vector4& pValue); //lua
			void WriteQuaternion(const Quaternion& pValue); //lua

			/*Static Members*/
			static std::map<std::string, uint16_t>* messages;
			static std::unordered_map<uint16_t, std::string>* messagesReverse;

			/* Static method(s). */
			static std::map<std::string, uint16_t>* GetAll();
			static std::unordered_map<uint16_t, std::string>* GetReverse();
			static int32_t Find(const std::string& pName);
			static std::string FindByID(uint16_t pID);
			static bool Exists(uint16_t pID);
			static void Initialize();
			static void Register(const std::string& pName, bool pStreamToPeers = false); //lua
			static void Insert(const std::string& pName, uint16_t pIndex);
			static void ClearAll();

		protected:
			ExpandingBuffer _buffer;
		};
	}
}

#define DECLARE_NETWORK_MESSAGE(MessageName) \
	static Hale3D::Network::_CompileMsg CREATE_VAR_NAME(_CompileMsg, __LINE__)(MessageName);

#endif
