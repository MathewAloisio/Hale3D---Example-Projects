/*----------------------------------/
/-------------Console---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_CONSOLE
#define HALE3D_CONSOLE
#include "Util.h"
#include "System.h"
#include "../BuildConfig.h"

/* Standard include(s). */
#include <map>
#include <string>
#include <vector>
#include <functional>

typedef std::vector<std::string> ARGS;
namespace Hale3D {
	/*ConVar flags.*/
	enum class CVarFlags : uint8_t { //lua
		None = 0,
		SaveLoad = 0x01,
		Cheat = 0x02,
		Unlisted = 0x04
	};
	ENABLE_BITMASK_OPERATORS(CVarFlags)

	/*Console command flags.*/
	enum class CommandFlags : uint8_t { //lua
		None = 0,
		ConVar = 0x01
	};
	ENABLE_BITMASK_OPERATORS(CommandFlags)

	/*ConCommand Structure*/
	struct ConCommand {
		/*Constructors*/
		ConCommand();
		ConCommand(const ConCommand& pOther);
		ConCommand(const std::string& pName, const std::function<void(ARGS)>& pCallback, const std::string& pDescription = "No description.", CommandFlags pFlags = CommandFlags::None);

		/* Member(s). */
		std::function<void(ARGS)> m_Callback;
		std::string m_Name;
		std::string m_Description;
		CommandFlags m_Flags;

		/* Method(s). */
		bool HasFlag(CommandFlags pFlag) const;

		void AddFlag(CommandFlags pFlag);
		void RemoveFlag(CommandFlags pFlag);
	};

	/*ConVar Structure*/
	struct ConVar {
		/* Constructor(s) & destructor(s). */
		ConVar();
		ConVar(const std::string& pCommand, const std::string& pDefaultValue = "", CVarFlags pFlags = CVarFlags::None, const std::function<void()>& pCallback = nullptr);
		ConVar(const ConVar& pOther);

		/* Member(s). */
		std::string m_Description;
		std::string m_Value = "";
		CVarFlags m_Flags;

		/* Method(s). */
		bool HasFlag(CVarFlags pFlag) const;

		void AddFlag(CVarFlags pFlag);
		void RemoveFlag(CVarFlags pFlag);

		// Conversions:
		float GetFloat();
		std::string GetString();

		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		T GetNumber() {
			return Conversion::StringToNumber<T>(m_Value);
		}
	};

	namespace Console {
		/*Variables*/
		extern std::map<std::string, ConCommand>* concommands;
		extern std::map<std::string, ConVar>* conVars;

		/* Method(s). */
		std::map<std::string, ConCommand>& GetCommands();
		std::map<std::string, ConVar>& GetConVars();

		bool IsCommandRegistered(const std::string& pName);
		void RegisterCommand(const std::string& pName, const std::function<void(ARGS)>& pCallback, const std::string& pDesc = "No Description.", CommandFlags pFlags = CommandFlags::None);
		void RemoveCommand(const std::string& pName);
		void ExecuteCommand(std::string pInfo); //lua
	
		bool IsConVarRegistered(const std::string& pName);
		void RegisterConVar(const std::string& pCommand, const std::string& pDefaultValue = "", CVarFlags pFlags = CVarFlags::None, const std::function<void()>& pCallback = nullptr);
		void RemoveConVar(const std::string& pCommand);
	}
}

#define DECLARE_CONCOMMAND(Command, Callback, Description) \
	static Hale3D::ConCommand CREATE_VAR_NAME(command, __LINE__)(Command, Callback, Description);

#define DECLARE_CONCOMMAND_FLAGS(Command, Callback, Description, Flags) \
	static Hale3D::ConCommand CREATE_VAR_NAME(command, __LINE__)(Command, Callback, Description, Flags);

#define DECLARE_CONVAR(Command, Default, Flags) \
	static Hale3D::ConCommand CREATE_VAR_NAME(command, __LINE__)( \
		Command, \
		[](ARGS pArgs) { \
			if (pArgs.size() == 0) { \
				std::string cmd(Command); \
				Hale3D::System::Print(">> \"" + std::string(cmd) + "\" = \"" + Hale3D::Console::GetConVars()[std::string(cmd)].m_Value + "\" (Default: \"" + std::string(Default) + "\")\n"); \
			} \
			else { Hale3D::Console::GetConVars()[std::string(Command)].m_Value = pArgs[0]; } \
		}, \
		"", \
		Hale3D::CommandFlags::ConVar \
	); \
	static Hale3D::ConVar CREATE_VAR_NAME(var, __LINE__)(Command, Default, Flags);

#define DECLARE_CONVAR_CALLBACK(Command, Default, Flags, Callback) \
	static Hale3D::ConCommand CREATE_VAR_NAME(command, __LINE__)( \
		Command, \
		[](ARGS pArgs) { \
			if (pArgs.size() == 0) { \
				std::string cmd(Command); \
				Hale3D::System::Print(">> \"" + std::string(cmd) + "\" = \"" + Hale3D::Console::GetConVars()[std::string(cmd)].m_Value + "\" (Default: \"" + std::string(Default) + "\")\n"); \
			} \
			else { \
				std::string lastValue = Hale3D::Console::GetConVars()[std::string(Command)].m_Value; \
				Hale3D::Console::GetConVars()[std::string(Command)].m_Value = pArgs[0]; \
				Callback(); \
			} \
		}, \
		"", \
		Hale3D::CommandFlags::ConVar \
	); \
	static Hale3D::ConVar CREATE_VAR_NAME(var, __LINE__)(Command, Default, Flags);

#define GetConVar(Command) \
	Hale3D::Console::GetConVars()[Command]

#define SetConVar(Command, Value) \
	Hale3D::Console::ExecuteCommand(std::string(Command) + " \"" + std::string(Value) + '"') // <- So callback is executed (If there is one). [OLD: Hale3D::Console::GetConVars()[Command] = Value]

#endif
