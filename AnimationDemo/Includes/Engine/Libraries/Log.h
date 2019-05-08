/*----------------------------------/
/---------------Log-----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_LOG
#define HALE3D_LOG

/* Standard include(s). */
#include <string>
#include <functional>

namespace Hale3D {
	enum class LogType : uint8_t { //lua
		Log,
		Warning,
		Error,
		FatalErrors
	};

	class LogCategory { //lua
	public:
		LogCategory(const std::string& pName, LogType pVerbosity, bool pLogFile); //lua

		/* Method(s). */
		bool IsSuppressed(LogType pVerbosity); //lua
		void ResetVerbosity(); //lua
		void SetVerbosity(LogType pVerbosity); //lua
		LogType GetVerbosity() const; //lua

		/*Callbacks*/
		void SetLogCallback(const std::function<void(LogType)>& pCallback);

	private:
		bool _logFile;
		std::string _name;

		struct {
			LogType m_Original;
			LogType m_Current;
		} _verbosity;

		std::function<void(LogType)> _logCallback = nullptr;
	};
}

//#define HALE3D_LOG(LogObj, ErrorType, Text) \
//TODO: Finish advanced logging.
	

#endif
