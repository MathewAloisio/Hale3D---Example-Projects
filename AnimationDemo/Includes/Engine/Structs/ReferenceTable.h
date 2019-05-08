/*----------------------------------/
/----------ReferenceTable-----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_REFERENCETABLE
#define HALE3D_REFERENCETABLE

/* Standard include(s). */
#include <string>
#include <functional>
#include <unordered_map>

namespace Hale3D {
	template <typename T> struct _Reference {
		T m_Obj;
		uint32_t m_Count;
	};

	template <typename T> class ReferenceTable {
	public:
		ReferenceTable(const std::function<void(T)>& pAllocator = nullptr, const std::function<void(T)>& pDeallocator = nullptr) {
			_allocCallback = pAllocator;
			_deallocCallback = pDeallocator;
		}

		/* Method(s). */
		void Reference(const std::string& pKey, T pObj) {
			if (_referenceMap.find(pKey) != _referenceMap.end()) {
				// Add reference.
				++_referenceMap[pKey].m_Count;
			}
			else { 
				_referenceMap[pKey].m_Count = 1; 
				_referenceMap[pKey].m_Obj = pObj;
				if (_allocCallback != nullptr) _allocCallback(pObj);
			}
		}

		void ReferenceBy(const std::string& pKey, uint32_t pCount, T pObj) {
			if (_referenceMap.find(pKey) != _referenceMap.end()) {
				// Add reference.
				_referenceMap[pKey].m_Count += pCount;
			}
			else {
				_referenceMap[pKey].m_Count = pCount;
				_referenceMap[pKey].m_Obj = pObj;
				if (_allocCallback != nullptr) _allocCallback(pObj);
			}
		}

		void Dereference(std::string pKey) { // NOTE: Passed by copy since lots of the time the argument is a member-variable passed, and the object is often deleted in the dealloc callback.
			--_referenceMap[pKey].m_Count;
			
			if (_referenceMap[pKey].m_Count == 0) {
				if (_deallocCallback != nullptr) _deallocCallback(_referenceMap[pKey].m_Obj);
				_referenceMap.erase(pKey);
			}
		}

		bool HasReference(const std::string& pKey) const {
			return _referenceMap.find(pKey) != _referenceMap.end();
		}

		const _Reference<T>& GetReference(const std::string& pKey) const {
			return _referenceMap.at(pKey);
		}
		
	private:
		std::function<void(T)> _allocCallback;
		std::function<void(T)> _deallocCallback;
		std::unordered_map<std::string, _Reference<T>> _referenceMap;
	};
}

#endif
