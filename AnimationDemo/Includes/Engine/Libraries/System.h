/*----------------------------------/
/--------------System---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_SYSTEM
#define HALE3D_SYSTEM
#include "FileSystem.h"
#include "../BuildConfig.h"

/* Standard include(s). */
#include <string>
#include <codecvt>
#include <iostream>

/*CALLBACK_ERROR_IF | Allows you to add callback while dispatching a System::Error of Warning type.*/
#define CALLBACK_ERROR_IF(Condition, Callback)														    \
	if (Condition) {																					\
		Callback																						\
		System::Error(#Condition, ErrorType::Warning, std::string(__FILE__), __LINE__);			\
	}

/*RETURN_ERROR_IF | Dispatches a System::Error(Condition, ErrType) when 'Condition' returns true, also returns ReturnValue if error occurs.*/
#define RETURN_ERROR_IF(Condition, ReturnValue)															\
	if (Condition) {																					\
		System::Error(#Condition, ErrorType::Warning, std::string(__FILE__), __LINE__);			\
		return ReturnValue;																				\
	}

/*RETURN_CUSTOM_ERROR_IF | Dispatches a System::Error(CustomError, ErrType) when 'Condition' returns true, also returns ReturnValue if error occurs.*/
#define RETURN_CUSTOM_ERROR_IF(Condition, CustomError, ReturnValue)										\
	if (Condition) {																					\
		System::Error(CustomError, ErrorType::Warning, std::string(__FILE__), __LINE__);		\
		return ReturnValue;																				\
	}

/*ERROR_IF | Dispatches a System::Error(Condition, ErrType) when 'Condition' returns true.*/
#define ERROR_IF(Condition, ErrType)																	\
	if (Condition) {																					\
		System::Error(#Condition, ErrType, std::string(__FILE__), __LINE__);							\
	}

/*ERROR | Dispatches a System::Error(ErrMsg, ErrType).*/
#define SYSTEM_ERROR(ErrMsg, ErrType)																	\
	System::Error(ErrMsg, ErrType, std::string(__FILE__), __LINE__);

namespace Hale3D {
	/* Error types. */
	enum class ErrorType {
		Warning,
		Error,
		Fatal
	};

	namespace System {
		/* Print method(s). */
		void Print(const char16_t pOut, const char16_t pEndChar = u'\n');
		void Print(const std::u16string& pUTF16String, const char16_t pEndChar = u'\n');

		template <typename T> void Print(const T pOut, const char pEndChar = '\n') {
			if (pEndChar != NULL) {
				std::cout << pOut << pEndChar;
			}
			else { std::cout << pOut; }
		}

		/* Error methods. */
		void Error(const std::string& pError, ErrorType pType, const std::string& pFile, int pLine);
		std::string ErrorToString(ErrorType pType);

		/* Startup parameters (command line options). */
		void AddParameter(const std::string& pParam, const std::string& pValue);
		bool HasParameter(const std::string& pParam); //lua
		std::string GetParameter(const std::string& pParam); //lua
	}
}

#endif
