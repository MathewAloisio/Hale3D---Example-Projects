/*----------------------------------/
/--------------Stream---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_STREAM
#define HALE3D_STREAM

#include "AABB.h"
#include "Color4.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Quaternion.h"

/* A template for all Stream types in the engine, all types that implement Get/Write methods for standard and engine data types. */
namespace Hale3D {
	class Stream { //lua
	public:
		/* Position & size. */
		virtual void SetPosition(size_t pPosition = 0) = 0; //lua
		virtual size_t GetPosition() = 0; //lua
		virtual size_t GetSize() = 0; //lua

		/* Custom read & write pattern(s). */
		virtual std::string ReadLine(size_t pReserveLength = 0) = 0; //lua
		virtual void WriteKeyValue(const std::string& pKey, const std::string& pValue) = 0; //lua
		virtual std::string GetKeyValue(const std::string& pKey, size_t pStartPos = 0) = 0; //lua

		/* Standard type(s). */
		virtual void WriteUInt8(uint8_t pValue) = 0; //lua
		virtual void WriteUInt8List(const std::initializer_list<uint8_t>& pValues) = 0;
		virtual void WriteBool(bool pValue) = 0; //lua
		virtual void WriteUInt16(uint16_t pValue) = 0;
		virtual void WriteUInt32(uint32_t pValue) = 0; //lua
		virtual void WriteUInt64(uint64_t pValue) = 0;
		virtual void WriteChar16(char16_t pValue) = 0;
		virtual void WriteChar32(char32_t pValue) = 0;
		virtual void WriteString(const std::string& pValue) = 0; //lua
		virtual void WriteU16String(const std::u16string& pValue) = 0;
		virtual void WriteU32String(const std::u32string& pValue) = 0;
		virtual void WriteFloat(float pValue) = 0; //lua
		virtual void WriteDouble(double pValue) = 0; //lua
		virtual void WriteUInt8Array(const uint8_t* pBuffer, size_t pSize) = 0;
		virtual void ReadUInt8Array(uint8_t* pBuffer, size_t pSize) = 0;
		virtual bool ReadBool() = 0; //lua
		virtual uint8_t ReadUInt8() = 0;
		virtual uint16_t ReadUInt16() = 0;
		virtual uint32_t ReadUInt32() = 0; //lua
		virtual uint64_t ReadUInt64() = 0;
		virtual char16_t ReadChar16() = 0;
		virtual char32_t ReadChar32() = 0;
		virtual std::string ReadString(size_t pReserveLength = 0) = 0; //lua
		virtual std::u16string ReadU16String(size_t pReserveLength = 0) = 0;
		virtual std::u32string ReadU32String(size_t pReserveLength = 0) = 0;
		virtual float ReadFloat() = 0; //lua
		virtual double ReadDouble() = 0; //lua

		/* Engine types. */
		virtual void WriteAABB(const AABB& pAABB) = 0; //lua
		virtual void WriteColor4(const Color4& pValue) = 0; //lua
		virtual void WriteVector2(const Vector2& pValue) = 0; //lua
		virtual void WriteVector3(const Vector3& pValue) = 0; //lua
		virtual void WriteVector4(const Vector4& pValue) = 0; //lua
		virtual void WriteQuaternion(const Quaternion& pValue) = 0; //lua
		virtual AABB ReadAABB() = 0; //lua
		virtual Color4 ReadColor4() = 0; //lua
		virtual Vector2 ReadVector2() = 0; //lua
		virtual Vector3 ReadVector3() = 0; //lua
		virtual Vector4 ReadVector4() = 0; //lua
		virtual Quaternion ReadQuaternion() = 0; //lua

		/* Static constant member(s). */
		static const std::initializer_list<char> REMOVED_ESCAPE_SEQUENCES;
	};
}

#endif
