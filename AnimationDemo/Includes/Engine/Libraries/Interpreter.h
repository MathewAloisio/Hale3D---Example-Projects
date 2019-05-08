/*----------------------------------/
/-----------Interpreter-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_INTERPRETER
#define HALE3D_INTERPRETER

/* Standard include(s). */
#include <map>
#include <string>
#include <functional>

/* Include lua header(s). */
extern "C" {
	#include <lua/lua.h>
	#include <lua/lualib.h>
	#include <lua/lauxlib.h>
}

/* Include tolua++ header. */
#include <tolua++.h>

namespace Hale3D {
	namespace Network {
		class Host;
	}

	class Entity;
	struct Color4;
	struct Vector2;
	struct Vector3;
	struct Vector4;

	// Reference: https://www.lua.org/manual/5.2/manual.html
	class Interpreter {
	public:
		void Reset();
		void Pop(const int pLevels) const;
		void PushValue(const int pIndex) const;
		void Remove(const int pIndex) const;
		int GetStackSize() const;
		void SetStackSize(const int pSize) const;
		void Invoke(const int pIn, const int pOut, const int pErrFunc) const;
		void Invoke(const int pIn, const int pOut) const;
		bool SafeInvoke(const int pIn, const int pOut, const int pErrFunc = 0) const;
		int Next(const int pIndex) const;
		void Insert(const int pindex) const;
		void RawGet(const int pIndex = -2) const;
		void RawSet(const int pIndex = -3) const;
		void SetTable(const int pIndex = -3) const;
		void GetField(const std::string& pName, const int pIndex = -1) const;
		void SetField(const std::string& pName, const int pIndex = -2) const;
		void GetTable(const int pIndex = -2) const;
		void GetMetaTable(const int pIndex = -1) const;
		void GetMetaTableByName(const std::string& pName) const;
		void GetGlobal(const std::string& pString) const;
		void SetGlobal(const std::string& pString) const;
		void PushNil() const;
		void PushString(const std::string& pString) const;
		void PushStringLiteral(const std::string& pString) const;
		void SetMetaTable(const int pIndex = -1);
		void PushUserType(void* pObj, const std::string& pTypeName) const;
		void PushLightUserData(void* pUserData) const;
		void TraverseTable(const std::function<bool()>& pIterFunc, int pIndex = -1) const; // NOTE: pIterFunc is executed every iteration, return true to kill loop. [Arguments: pKey, pValue]
		bool IsString(const int pIndex = -1) const;
		std::string ToString(const int pIndex = -1) const;
		bool IsNumber(const int pIndex = -1) const;
		bool IsUserData(const int pIndex = -1) const;
		double ToNumber(const int pIndex = -1) const;
		bool IsFunction(const int pIndex = -1) const;
		bool IsTable(const int pIndex = -1) const;
		bool IsBool(const int pIndex = -1) const;
		bool IsNil(const int pIndex = -1) const;
		bool ToBool(const int pIndex = -1) const;
		void* ToUserData(const int pIndex = -1) const;
		bool IsClassRegistered(const std::string& pName) const;
		void NewTable() const;
		void CreateTable(int pSequencedElementCount, int pRandomElementCount) const;
		void Close();
		void CopyTable(int pIndex = -1, bool pRawSet = false) const;
		void MergeTable(int pDstIndex = -2, int pSrcIndex = -1, bool pRawSet = false);
		bool ExecuteFile(const std::string& pPath) const;
		bool ExecuteString(const std::string& pCode) const;
		void DumpStack() const;

		bool IsActiveLuaState() const;
		lua_State* GetState();

		// Usertype function calling
		void RunUserTypeFunction(const std::string& pFuncName, void* pUserTypeObj, const std::string& pUserTypeName, int pArgCount, const std::function<void()>& pArgsFn);
		bool CallUserTypeFunction(const std::string& pFuncName, void* pUserTypeObj, const std::string& pUserTypeName, bool pDefaultReturn, int pArgCount, const std::function<void()>& pArgsFn);

		// Engine specific types
		void PushHost(Network::Host* pHost) const;
		void PushEntity(Entity* pEntity) const;
		void PushColor4(Color4* pColor) const;
		void PushVector2(Vector2* pVec) const;
		void PushVector3(Vector3* pVec) const;
		void PushVector4(Vector4* pVec) const;

		/* Lua entities. */
		void RegisterEntityScripts(const std::string& pPath, bool pRecursive); // Registers all lua entities in pPath (and subdirectories if pRecursive).
		void FindAndRegisterEntityScript(const std::string& pPath, const std::string& pClassName, bool pRecursive); // Searches pPath (and subdirectories if pRecusive) for pPath, if found registers the lua entity.
		void RegisterEntityScript(const std::string& pFilePath); // Registers a lua entity at a specified file path.

		// Template stack operations.
		template<typename T, typename = typename std::enable_if<std::is_enum<T>::value, T>::type>
		void PushEnumerate(T pEnum) {
			tolua_pushnumber(_luaState, static_cast<lua_Number>(pEnum));
		}

		template<typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		void PushInteger(T pIntegral) {
			lua_pushinteger(_luaState, static_cast<lua_Integer>(pIntegral));
		}

		template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
		void PushFloatingPoint(T pFloatingPoint) {
			lua_pushnumber(_luaState, static_cast<lua_Number>(pFloatingPoint));
		}

		/* Static method(s). */
		static Interpreter* GetCurrent();
		static void SetCurrent(Interpreter* pInterpreter); // NOTE: This should always be 'Interpreter::GLOBAL'. "include" will use the current interpreter's Lua state.
		
		/* Static member(s). */
		static Interpreter GLOBAL;
		static constexpr int MAX_DEBUG_LEVELS = 5;
		static bool LUA_REFRESH_ENABLED; // NOTE: This value is set by the engine and SHOULD NOT be modified.

	private:
		lua_State* _luaState;
	};
}

/* Lua refresh. */
struct _LuaFile {
	time_t m_LastModified;
	const Hale3D::Interpreter* m_Interpreter;
};
typedef std::map<std::string, _LuaFile> _LuaFileMap;

void _RegisterLuaFile(const std::string& pPath, const Hale3D::Interpreter* pInterpreter, time_t pLastModifiedTime);
void _DeregisterLuaFile(const std::string& pPath);
const _LuaFileMap& GetLuaFileMap();

/* Lua file execution. */
bool include(const std::string& pPath); //lua

#endif
