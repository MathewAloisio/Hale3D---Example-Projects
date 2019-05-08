/*----------------------------------/
/------------FileSystem-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_FILESYSTEM
#define HALE3D_FILESYSTEM
#include "Util.h"
#include "Compression.h"
#include "../Structs/Stream.h"

/* Standard include(s). */
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

struct archive;
namespace Hale3D {
	/* FStreamFlags. */
	enum class FStreamFlags : std::ios_base::openmode {
		None = 0,
		Binary = std::ios_base::binary,
		AtEnd = std::ios_base::ate,
		Write = std::ios_base::out,
		Read = std::ios_base::in,
		Append = std::ios_base::app,
		Truncate = std::ios_base::trunc
	};
	ENABLE_BITMASK_OPERATORS(FStreamFlags)

	/* FStreamStates. */
	enum class FStreamStates : std::ios_base::iostate {
		None = 0,
		Normal = std::ios_base::goodbit,
		Fatal = std::ios_base::failbit,
		Warning = std::ios_base::badbit,
		EndOfFile = std::ios_base::eofbit
	};
	ENABLE_BITMASK_OPERATORS(FStreamStates)

	/* FileStream. */
	class FileStream : public Stream { //lua
	public:
		/* Constructors & destructors. */
		FileStream(const std::string& pPath, FStreamFlags pFlags); //lua
		~FileStream(); //lua

		/* Members. */
		std::fstream m_Stream;
		size_t m_Size;
		bool m_CanRead;
		bool m_CanWrite;
		bool m_BinaryMode;
		FStreamFlags m_Flags;
		std::string m_FilePath;

		/* Methods. */
		FStreamStates GetState(); //lua
		bool EndOfFile(); //lua
		void Close(); //lua

		/* Position & size. */
		virtual void SetPosition(size_t pPosition = 0); //lua
		virtual size_t GetPosition(); //lua
		virtual size_t GetSize(); //lua

		/* FileSystem specific write & read pattern(s). */
		void WriteTime(); //lua
					  
		/* Custom read & write pattern(s). */
		virtual std::string ReadLine(size_t pReserveLength = 0); //lua
		virtual void WriteKeyValue(const std::string& pKey, const std::string& pValue); //lua
		virtual std::string GetKeyValue(const std::string& pKey, size_t pStartPos = 0); //lua

		/* Standard type(s). */
		virtual void WriteUInt8(uint8_t pValue);
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
		virtual  std::u32string ReadU32String(size_t pReserveLength = 0);
		virtual float ReadFloat(); //lua
		virtual double ReadDouble(); //lua

		/* Engine types. */
		virtual void WriteAABB(const AABB& pAABB); //lua
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
	};

	/* VirtualDrive. */
	class VirtualDrive { //lua
	public:
		VirtualDrive(const std::string& pPath, const std::string& pPassword = "");
		~VirtualDrive();

		size_t GetSize() const; //lua

		bool IsOpened() const; //lua
		bool Exists(const std::string& pPath) const; //lua
		bool IsDir(const std::string& pPath) const; //lua
		std::map<std::string, std::string> ReadKeyValues(const std::string& pPath);
		std::string GetKeyValueFromBuffer(const std::vector<char>& pBuffer, const std::string& pKey);
		std::vector<std::string> GetContents(const std::string& pPath) const;
		std::vector<char> ReadToBuffer(const std::string& pPath, bool pBinary = false, CompressionMode pCompressionMode = CompressionMode::None);
		size_t GetFileSize(const std::string& pPath) const; //lua

	private:
		bool _opened;
		archive* _archive;
	};

	/* FileSystem namespace. */
	namespace FileSystem {
		/* Methods. */
		bool Exists(const std::string& pPath); //lua
		bool IsDir(const std::string& pPath); //lua
		time_t GetModificationTime(const std::string& pPath); //lua
		uint32_t Checksum(const std::string& pPath); //lua
		size_t GetFileSize(const std::string& pPath); //lua
		std::map<std::string, std::string> ReadKeyValues(const std::string& pPath);
		std::vector<char> ReadToBuffer(const std::string& pPath, bool pBinary = false, CompressionMode pCompressionMode = CompressionMode::None);
		std::string GetKeyValueFromBuffer(const std::vector<char>& pBuffer, const std::string& pKey);
		std::string GetPath(const std::string& pPath); //lua
		std::string GetExtension(const std::string& pPath); //lua
		std::string GetFolderName(const std::string& pPath); //lua
		std::string StripBoth(const std::string& pPath); //lua
		std::string StripPath(const std::string& pPath); //lua
		std::string StripExtension(const std::string& pPath); //lua
		std::string GetDataPath(); //lua NOTE: GetDataPath() does NOT return a trailing '/'.
		std::string GetEngineDataPath(); //lua
		std::vector<std::string> GetContents(const std::string& pPath);

		std::string Rename(const std::string& pPath, const std::string& pName); //lua
		bool Move(const std::string& pFrom, const std::string& pTo); //lua
		bool CreateFile(const std::string& pPath, bool pOverwrite = true); //lua
		bool CreateDir(const std::string& pPath); //lua
		bool DeleteFile(const std::string& pPath); //lua
		bool DeleteDir(const std::string& pPath); //lua
		bool CopyFile(const std::string& pSrc, const std::string& pDst); //lua
		bool CopyDir(const std::string& pSrc, const std::string& pDst, bool pCopyRoot = true, bool pCopyFiles = true); //lua
		void CompressFile(const std::string& pInPath, const std::string& pOutPath = "", CompressionMode pCompressionMode = CompressionMode::ZSTD);
		void GenerateErrorLog(const std::string& pPath, const std::string& pError); //lua
	}
}

#endif
