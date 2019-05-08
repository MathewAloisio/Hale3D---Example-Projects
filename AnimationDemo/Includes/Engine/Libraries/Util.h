/*----------------------------------/
/--------------Util-----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_UTIL
#define HALE3D_UTIL

#include "../Structs/Color4.h"
#include "../Structs/Vector2.h"
#include "../Structs/Vector3.h"
#include "../Structs/Vector4.h"

/* Standard include(s). */
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <type_traits>

/* Definitions. */
#define _CREATE_VAR_NAME_HLP(X, Y) X##Y
#define CREATE_VAR_NAME(X, Y) _CREATE_VAR_NAME_HLP(X, Y)

// NOTE: Linear scoped enums mean the iterator starts at pFirst and counts in-order to pLast.
#define GENERATE_LINEAR_SCOPED_ENUM_ITERATOR(pEnum, pFirst, pLast)											\
	pEnum operator++(pEnum& pVar) { return pVar = (pEnum)(std::underlying_type<pEnum>::type(pVar) + 1); }	\
	pEnum operator*(pEnum pVar) { return pVar; }															\
	pEnum begin(pEnum pVar) { return pEnum::pFirst; }														\
	pEnum end(pEnum pVar) { pEnum l = pEnum::pLast; return l++; }											\

#define ENABLE_BITMASK_OPERATORS(pType)							\
	template<> struct Hale3D::EnableBitMaskOperators<pType> {	\
		static constexpr bool enable = true;					\
	};															\

namespace Hale3D {
	/* Algorithm utilities. */
	namespace Algorithm {
		template<typename ContainerType, typename PredicateType>
		void EraseIf(ContainerType& pContainer, const PredicateType& pPredicate) {
			for (auto it = pContainer.begin(); it != pContainer.end();) {
				if (pPredicate(*it)) {
					it = pContainer.erase(it);
				}
				else { ++it; }
			}
		}

		template<typename ContainerType, typename PredicateType, typename OnEraseType>
		void EraseIf(ContainerType& pContainer, const PredicateType& pPredicate, const OnEraseType& pOnErase) {
			for (auto it = pContainer.begin(); it != pContainer.end();) {
				if (pPredicate(*it)) {
					pOnErase(*it);
					it = pContainer.erase(it);
				}
				else { ++it; }
			}
		}

		/*template<typename Iterator, typename Predicate, typename Counter>
		Iterator FindIfNth(Iterator pFirst, Iterator pLast, Predicate pPredicate, Counter pN) {
			typedef typename std::iterator_traits<Iterator>::reference Tref;
			return std::find_if(pFirst, pLast, [&](Tref pValue) {
				return pPredicate(pValue) && !(--pN);
			});
		}*/
	}

	/* String utilities. */
	namespace String {
		/* String manipulation. */
		std::string TrimLeft(std::string pInput); //lua
		std::string TrimRight(std::string pInput); //lua
		std::string Trim(std::string pInput); //lua
		std::string Remove(std::string pInput, char pChar); //lua
		std::string Remove(std::string pInput, const std::initializer_list<char>& pExcluded);
		std::string RemoveTrailingSlash(const std::string& pInput); //lua
		std::string AppendTrailingSlash(const std::string& pInput); //lua
		std::vector<std::string> Split(const std::string& pString, char pSeperator);

		template<typename ... ARGS>
		std::string Format(const std::string& pInput, ARGS ... pArgs) {
			size_t size = std::snprintf(nullptr, 0, pInput.c_str(), pArgs ...) + 1;
			char* buffer = new char[size];
			std::snprintf(buffer, size, pInput.c_str(), pArgs ...);
			std::string out(buffer, size - 1); // Subtract 1 from size to exclude the termination character.

			delete buffer;

			return out;
		};

		/* Search algorithm(s). */
		bool Contains(const std::string& pString, const char pChar);
		bool Contains(const std::string& pString, const std::string& pSubstring);

		/* Case sensitivity. */
		std::string Lower(const std::string& pValue);
		std::string Upper(const std::string& pValue);

		// Substring extraction.
		std::string ExtractMiddle(const std::string& pValue, const char pLeftChar, const char pRightChar, const size_t pOffset = 0); //lua
		std::string ExtractMiddle(const std::string& pValue, const std::string& pLeft, const std::string& pRight, const size_t pOffset = 0); //lua

		// Numeric type checking.
		bool IsDigits(const std::string& pString, bool pLeadingDigits = false); //lua
		bool IsFloat(const std::string& pString); //lua

		// Hex to decimal conversions.
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		T HexToNumber(const std::string& pHex) {
			std::stringstream stream;
			stream << pHex;
			long long out;
			stream >> std::hex >> out;

			return static_cast<T>(out);
		}
	}

	/* Type conversion utilities. */
	namespace Conversion {
		/* String conversion(s). */
		std::string FloatToString(const float pFloat);

		/* Memory size conversions. */
		std::string ByteCountToString(uint32_t pValue, uint32_t pDecimalPlaces = 0, const std::string& pSeperator = " "); //lua

		/* Conversion templates. */
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		T StringToNumber(const std::string& pString) {
			T value = 0;
			const char* cString = pString.c_str();
			while (*cString) {
				value = value * 10 + (*cString++ - '0');
			}

			return value;
		}

		template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
		T StringToFloat(const std::string& pString) {
			return static_cast<T>(std::stod(pString));
		}

		Color4 StringToColor4(const std::string& pString);
		Vector3 StringToVector3(const std::string& pString);

		/* Enumerate conversion(s). */
		template<typename T>
		constexpr auto ToUnderlyingType(T pObj) {
			return static_cast<std::underlying_type<T>::type>(pObj);
		}
	}

	/* Enable-able bitmask operators. */
	template <typename T> 
	struct EnableBitMaskOperators {
		static constexpr bool enable = false;
	};

	template<typename T>
	typename std::enable_if<EnableBitMaskOperators<T>::enable, T>::type operator|(T pLeft, T pRight) {
		return static_cast<T>(Conversion::ToUnderlyingType(pLeft) | Conversion::ToUnderlyingType(pRight));
	}

	template<typename T>
	typename std::enable_if<EnableBitMaskOperators<T>::enable, T>::type operator&(T pLeft, T pRight) {
		return static_cast<T>(Conversion::ToUnderlyingType(pLeft) & Conversion::ToUnderlyingType(pRight));
	}

	template<typename T>
	typename std::enable_if<EnableBitMaskOperators<T>::enable, T>::type operator^(T pLeft, T pRight) {
		return static_cast<T>(Conversion::ToUnderlyingType(pLeft) ^ Conversion::ToUnderlyingType(pRight));
	}

	template<typename T>
	typename std::enable_if<EnableBitMaskOperators<T>::enable, T>::type operator~(T pRight) {
		return static_cast<T>(~Conversion::ToUnderlyingType(pRight));
	}

	template<typename T>
	typename std::enable_if<EnableBitMaskOperators<T>::enable, T>::type& operator|=(T& pLeft, T& pRight) {
		pLeft = static_cast<T>(Conversion::ToUnderlyingType(pLeft) | Conversion::ToUnderlyingType(pRight));
		return pLeft;
	}

	template<typename T>
	typename std::enable_if<EnableBitMaskOperators<T>::enable, T>::type& operator&=(T& pLeft, const T& pRight) {
		pLeft = static_cast<T>(Conversion::ToUnderlyingType(pLeft) & Conversion::ToUnderlyingType(pRight));
		return pLeft;
	}

	template<typename T>
	typename std::enable_if<EnableBitMaskOperators<T>::enable, T>::type& operator^=(T& pLeft, T& pRight) {
		pLeft = static_cast<T>(Conversion::ToUnderlyingType(pLeft) ^ Conversion::ToUnderlyingType(pRight));
		return pLeft;
	}
}

#endif
