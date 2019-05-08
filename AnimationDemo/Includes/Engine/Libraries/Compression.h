/*----------------------------------/
/-----------Compression-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_COMPRESSION
#define HALE3D_COMPRESSION

/* Standard include(s). */
#include <vector>

/* Include zstandard compression. */
#include <zstd/zstd.h>

namespace Hale3D {
	enum class CompressionMode : uint8_t { //lua
		None,
		ZSTD
	};

	namespace Compression {
		void SetLevel(int pLevel);
		int GetLevel();

		std::vector<char> Compress(CompressionMode pCompressionMode, const std::vector<char>& pData);
		std::vector<char> Decompress(CompressionMode pCompressionMode, const std::vector<char>& pCompressedData);
		std::vector<char> Decompress(CompressionMode pCompressionMode, const std::vector<char>& pCompressedData, size_t pDecompressedSize);
	}
}

#endif
