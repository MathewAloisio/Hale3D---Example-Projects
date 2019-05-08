/*----------------------------------/
/--------------Endian---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef DEFINES_ENDIAN
#define DEFINES_ENDIAN

#include <stdint.h>

//Try our best to determine endianness, but if we can't it's okay we'll do it at runtime.
#if defined(_WIN32)
	#define SYSTEM_LITTLE_ENDIAN
#endif
#if !defined(SYSTEM_LITTLE_ENDIAN)
	#if defined(__BYTE_ORDER)
		#if __BYTE_ORDER == __BIG_ENDIAN
			#define SYSTEM_BIG_ENDIAN
		#elif __BYTE_ORDER == LITTLE_ENDIAN
			#define SYSTEM_LITTLE_ENDIAN
		#endif
	#elif defined(__BYTE_ORDER__)
		#if __BYTE_ORDER__ == __ORDER_LITTLE__ 
			#define SYSTEM_LITTLE_ENDIAN 1
		#elif __BYTE_ORDER__ == __ORDER_BIG__
			#define SYSTEM_BIG_ENDIAN
		#endif
	#endif
#endif
#if !defined(SYSTEM_BIG_ENDIAN) && !defined(SYSTEM_LITTLE_ENDIAN)
	#if (defined(__BIG__) || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIPSEB) || defined(__MIPSEB) || defined(__MIPSEB__))
		#define SYSTEM_BIG_ENDIAN
	#elif (defined(_LITTLE__) || defined(__ARMEL__) || defined(__THUMBEL__) || defined(__AARCH64EL__) || defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__))
		#define SYSTEM_LITTLE_ENDIAN
	#endif
#endif

//Endian swapping macros/functions not based on our endianness.
#define FLOAT_SWAP(fOut, fIn) (*((unsigned int*)fOut) = *((unsigned int*)fIn))

/*NOTE: This DOES NOT add the methods to a 'Endian' namespace, or alike, so the usage for all cases is the same within the engine.*/
namespace Hale3D {
	inline void SHORT_SWAP(int16_t value, int16_t out) {
		out = (value << 8) | ((value >> 8) & 0xFF);
	}
	inline void USHORT_SWAP(uint16_t value, uint16_t out) {
		out = (value << 8) | (value >> 8);
	}
	inline void INT_SWAP(int32_t value, int32_t out) {
		value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00F);
		out = (value << 16) | ((value >> 16) & 0xFFFF);
	}
	inline void UINT_SWAP(uint32_t value, uint32_t out) {
		value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF);
		out = (value << 16) | (value >> 16);
	}
	inline void LONG_SWAP(int64_t value, int64_t out) {
		value = ((value << 8) & 0xFF00FF00FF00FF00ULL) | ((value >> 8) & 0x00FF00FF00FF00FFULL);
		value = ((value << 16) & 0xFFFF0000FFFF0000ULL) | ((value >> 16) & 0x0000FFFF0000FFFFULL);
		out = (value << 32) | ((value >> 32) & 0xFFFFFFFFULL);
	}
	inline void ULONG_SWAP(uint64_t value, uint64_t out) {
		value = ((value << 8) & 0xFF00FF00FF00FF00ULL) | ((value >> 8) & 0x00FF00FF00FF00FFULL);
		value = ((value << 16) & 0xFFFF0000FFFF0000ULL) | ((value >> 16) & 0x0000FFFF0000FFFFULL);
		out = (value << 32) | (value >> 32);
	}

	/*Create our endian swapping macros/functions based on our endianess.*/
#if defined(SYSTEM_LITTLE_ENDIAN) /*System is Little Endian.*/
	#define FLOAT_BIG(fOut, fIn) FLOAT_SWAP(fOut, fIn)
	#define FLOAT_LITTLE(fOut, fIn) (*fOut = *fIn) //Already little, we're on a little endian machine.
	#define SHORT_BIG(sIn, sOut) SHORT_SWAP(sIn, sOut)
	#define SHORT_LITTLE(sIn, sOut) (*sIn = *sOut)
	#define USHORT_BIG(sIn, sOut) USHORT_SWAP(sIn, sOut)
	#define USHORT_LITTLE(sIn, sOut) (*sIn = *sOut)
	#define INT_BIG(iIn, iOut) INT_SWAP(iIn, iOut)
	#define INT_LITTLE(iIn, iOut) (*iIn = *iOut)
	#define UINT_BIG(iIn, iOut) UINT_SWAP(iIn, iOut)
	#define UINT_LITTLE(iIn, iOut) (*iIn = *iOut)
	#define LONG_BIG(lIn, lOut) LONG_SWAP(lIn, lOut)
	#define LONG_LITTLE(lIn, lOut) (*lIn = *lOut)
	#define ULONG_BIG(lIn, lOut) ULONG_SWAP(lIn, lOut)
	#define ULONG_LITTLE(lIn, lOut) (*lIn = *lOut)
#elif defined(SYSTEM_BIG_ENDIAN) //System is big endian.
	#define FLOAT_BIG(fOut, fIn) (*fOut = *fIn) //Already big endian, we're on a big endian machine.
	#define FLOAT_LITTLE(fOut, fIn) FLOAT_SWAP(fOut, fIn)
	#define SHORT_BIG(sIn, sOut) (*sIn = *sOut)
	#define SHORT_LITTLE(sIn, sOut) SHORT_SWAP(sIn, sOut)
	#define USHORT_BIG(sIn, sOut) (*sIn = *sOut)
	#define USHORT_LITTLE(sIn, sOut) USHORT_SWAP(sIn, sOut)
	#define INT_BIG(iIn, iOut) (*iIn = *iOut)
	#define INT_LITTLE(iIn, iOut) INT_SWAP(iIn, iOut)
	#define UINT_BIG(iIn, iOut) (*iIn = *iOut)
	#define UINT_LITTLE(iIn, iOut) UINT_SWAP(iIn, iOut)
	#define LONG_BIG(lIn, lOut) (*lIn = *lOut)
	#define LONG_LITTLE(lIn, lOut) LONG_SWAP(lIn, lOut)
	#define ULONG_BIG(lIn, lOut) (*lIn = *lOut)
	#define ULONG_LITTLE(lIn, lOut) ULONG_SWAP(lIn, lOut)
#else //Determine endianness at runtime.
	#define LITTLE_ENDIAN 0
	#define BIG_ENDIAN 1
	static int get_endianness() {
		const int i = 1;
		if ((*(char*)&i) == 0) {
			return BIG_ENDIAN;
		}
		else { return LITTLE_ENDIAN; }
	}
	static inline float _floatSwap(const float fIn) {
		float out;
		((uint8_t*)&out)[0] = ((uint8_t*)&fIn)[3];
		((uint8_t*)&out)[1] = ((uint8_t*)&fIn)[2];
		((uint8_t*)&out)[2] = ((uint8_t*)&fIn)[1];
		((uint8_t*)&out)[3] = ((uint8_t*)&fIn)[0];
		return out;
	}

	static int endianness = -1;
	inline void FLOAT_BIG(float& fOut, const float& fIn) {
		if (endianness == -1) endianness = get_endianness();
		if (endianness == LITTLE_ENDIAN) fOut = _floatSwap(fIn);
	}
	inline void FLOAT_LITTLE(float& fOut, const float& fIn) {
		if (endianness == -1) endianness = get_endianness();
		if (endianness == BIG_ENDIAN) fOut = _floatSwap(fIn);
	}
#endif
}
#endif
