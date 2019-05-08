/*----------------------------------/
/----------ExpandingBuffer----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/

/* Originally designed with Networking in mind,					*
 * but later it was decided to make this a generic growable		*
 * buffer class.												*/

#ifndef HALE3D_EXPANDINGBUFFER
#define HALE3D_EXPANDINGBUFFER

#include "Stream.h"

/* Standard include(s). */
#include <string>
#include <initializer_list>

namespace Hale3D {
	class ExpandingBuffer : public Stream { //lua
	public:
		/* Constructor(s) & destructor(s). */
		ExpandingBuffer(size_t pInitialSize = ExpandingBuffer::BUFFER_DEFAULT_INITIAL_SIZE); //lua
		ExpandingBuffer(const std::string& pPath); //lua
		ExpandingBuffer(const ExpandingBuffer& pOther); //lua
		ExpandingBuffer(ExpandingBuffer&& pMovable);
		ExpandingBuffer(uint8_t* pBuffer, size_t pSize);
		virtual ~ExpandingBuffer();

		ExpandingBuffer& operator=(const ExpandingBuffer& pOther);
		ExpandingBuffer& operator=(ExpandingBuffer&& pMovable);

		/* Methods. */
		void UpdateMessageHeader(); //lua
		uint8_t* GetData();
		size_t GetAllocationSize() const; //lua

		/* Position & size. */
		virtual void SetPosition(size_t pPosition = 0); //lua
		virtual size_t GetPosition(); //lua
		virtual size_t GetSize(); //lua

		/* Custom read & write pattern(s). */
		virtual std::string ReadLine(size_t pReserveLength = 0); //lua
		virtual void WriteKeyValue(const std::string& pKey, const std::string& pValue); //lua
		virtual std::string GetKeyValue(const std::string& pKey, size_t pStartPos = 0); //lua

		/* Standard type(s). */
		virtual void WriteUInt8(uint8_t pValue); //lua
		virtual void WriteUInt8List(const std::initializer_list<uint8_t>& pValues);
		virtual void WriteBool(bool pValue); //lua
		virtual void WriteUInt16(uint16_t pValue);
		virtual void WriteUInt32(uint32_t pValue); //lua
		virtual void WriteUInt64(uint64_t pValue);
		virtual void WriteChar16(char16_t pValue);
		virtual void WriteChar32(char32_t pValue);
		virtual void WriteString(const std::string& pValue); //lua
		virtual void WriteU16String(const std::u16string& pValue);
		virtual void WriteU32String(const std::u32string& pValue);
		virtual void WriteFloat(float pValue); //lua
		virtual void WriteDouble(double pValue); //lua
		virtual void WriteUInt8Array(const uint8_t* pBuffer, size_t pSize);
		virtual void ReadUInt8Array(uint8_t* pBuffer, size_t pSize);
		virtual bool ReadBool(); //lua
		virtual uint8_t ReadUInt8();
		virtual uint16_t ReadUInt16();
		virtual uint32_t ReadUInt32(); //lua
		virtual uint64_t ReadUInt64();
		virtual char16_t ReadChar16();
		virtual char32_t ReadChar32();
		virtual std::string ReadString(size_t pReserveLength = 0); //lua
		virtual std::u16string ReadU16String(size_t pReserveLength = 0);
		virtual std::u32string ReadU32String(size_t pReserveLength = 0);
		virtual float ReadFloat(); //lua
		virtual double ReadDouble(); //luaa

		/* Engine types. */
		virtual void WriteAABB(const AABB& pAABB); //lu
		virtual void WriteColor4(const Color4& pValue); //lua
		virtual void WriteVector2(const Vector2& pValue); //lua
		virtual void WriteVector3(const Vector3& pValue); //lua
		virtual void WriteVector4(const Vector4& pValue); //lua
		virtual void WriteQuaternion(const Quaternion& pValue); //lua
		virtual AABB ReadAABB(); //lua
		virtual Color4 ReadColor4(); //lua
		virtual Vector2 ReadVector2(); //lua
		virtual Vector3 ReadVector3(); //lua
		virtual Vector4 ReadVector4(); //lua
		virtual Quaternion ReadQuaternion(); //lua

		/* Static member(s). */
		static const size_t BUFFER_DEFAULT_INITIAL_SIZE; //lua
		static const float BUFFER_GROWTH_FACTOR; //lua
		static const size_t BUFFER_SIZE_WARNING; //lua

	protected:
		/* Methods. */
		void CheckForSpace(size_t pSize);

		/* Members. */
		uint8_t* _buffer;
		size_t _position;
		size_t _allocatedSize;
		size_t _size;
	};
}
#endif
