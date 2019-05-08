/*----------------------------------/
/-------------Reader----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NETWORK_READER
#define HALE3D_NETWORK_READER
#include "../Structs/ExpandingBuffer.h"

namespace Hale3D {
	namespace Network {
		class Message;

		class Reader { //lua
		public:
			/* Constructor(s) & destructor(s). */
			Reader(Message* pMessage); //lua
			Reader(uint8_t* pValue, size_t pSize);
			Reader(const Reader& pOther); //lua

			/* Method(s). */
			bool ReadBool(); //lua
			uint8_t ReadUInt8(); //lua
			uint16_t ReadUInt16(); //lua
			uint32_t ReadUInt32(); //lua
			float ReadFloat(); //lua
			double ReadDouble(); //lua
			void ReadUInt8Array(uint8_t* pBuffer, size_t pSize);
			void SetPosition(size_t pPosition); //lua
			size_t GetPosition(); //lua

			std::string ReadString(); //lua
			std::string ReadString(size_t pLength);

			/*Hale3D Types*/
			Vector2 ReadVector2(); //lua
			Vector3 ReadVector3(); //lua
			Vector4 ReadVector4(); //lua
			Quaternion ReadQuaternion(); //lua

		protected:
			/* Member(s). */
			ExpandingBuffer _buffer;
		};
	}
}

#endif
