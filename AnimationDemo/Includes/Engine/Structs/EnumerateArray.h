/*----------------------------------/
/----------EnumerateArray-----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_ENUMERATEARRAY
#define HALE3D_ENUMERATEARRAY

#include "../Libraries/Util.h"

/* Standard include(s). */
#include <assert.h>
#include <cstdint>
#include <iterator>
#include <initializer_list>

namespace Hale3D {
	/*Enumerate array class.*/
	template <typename K, typename V, size_t SIZE>
	struct EnumerateArray {
	public:
		// Constructor(s)
		EnumerateArray() {}
		
		EnumerateArray(std::initializer_list<V> pList) {
			size_t i = 0;
			for (V value : pList) {
				_data[i++] = value;
			}
		}

		// [] access operator overload.
		V& operator[](K pKey) {
			return _data[Conversion::ToUnderlyingType(pKey)];
		}

		constexpr const V& operator[](K pKey) const {
			return _data[Conversion::ToUnderlyingType(pKey)];
		}

		V& operator[](size_t pIndex) {
			return _data[pIndex];
		}

		constexpr const V& operator[](size_t pIndex) const {
			return _data[pIndex];
		}

		// General.
		constexpr bool empty() const noexcept { return SIZE == 0; }
		constexpr size_t size() const noexcept { return SIZE; }

		// Data access.
		V* data() noexcept { return _data; }
		constexpr const V* data() const noexcept { return _data; }

		// Iteration.
		auto begin() noexcept { return std::begin(_data); }
		auto end() noexcept { return std::end(_data); }

		constexpr auto begin() const noexcept { return std::begin(_data); };
		constexpr auto end() const noexcept { return std::end(_data); }

		constexpr auto cbegin() const noexcept { return std::cbegin(_data); }
		constexpr auto cend() const noexcept { return std::cend(_data); }

	private:
		V _data[SIZE];
	};
}

#endif
