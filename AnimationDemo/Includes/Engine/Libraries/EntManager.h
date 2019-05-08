/*----------------------------------/
/------------EntManager-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_ENTMANAGER
#define HALE3D_ENTMANAGER

#include "../Libraries/Util.h"

/* Standard include(s). */
#include <map>

namespace Hale3D {
	class Entity;

	enum class EntityType : uint8_t { //lua
		None,
		C,
		Lua,
	};

	/*EntManager Namespace*/
	namespace EntManager {
		// Entity factories.
		struct IEntityFactory { virtual Entity* Create() = 0; };

		// Methods
		std::map<std::string, IEntityFactory*>& GetFactories();

		Entity* Create(const std::string& pClassName); //lua
		EntityType GetEntityType(const std::string& pClassName); //lua

		// Entity factory templates.
		template<typename T> struct EntityFactory : public IEntityFactory {
			inline EntityFactory(const std::string& pName) {
				EntManager::GetFactories().insert({ pName, this });
			}

			virtual T* Create() {
				return new T;
			}
		};

		template<typename T> struct BaseFactory : public IEntityFactory {
			inline BaseFactory(const std::string& pName) {
				EntManager::GetFactories().insert({ pName, nullptr });
			}

			virtual T* Create() {
				System::Print("[ERROR] Cannot create base classes.");
				return nullptr;
			}
		};
	}
}

#define DECLARE_ENTITY_CLASS(ClassName)																					\
		static Hale3D::EntManager::EntityFactory<ClassName> CREATE_VAR_NAME(regEntityFactory, ClassName);				\
		static ClassName* Create() {																					\
			ClassName* _createdObj = new ClassName();																	\
			_createdObj->SetClass(#ClassName);																			\
			_createdObj->Initialize();																					\
			return _createdObj;																							\
		};																												

#define DECLARE_BASE_CLASS(ClassName)																					\
		static Hale3D::EntManager::BaseFactory<ClassName> CREATE_VAR_NAME(regBaseFactory, ClassName);					\

#define DEFINE_ENTITY_CLASS(ClassName)																					\
		Hale3D::EntManager::EntityFactory<ClassName> ClassName::CREATE_VAR_NAME(regEntityFactory, ClassName)(#ClassName);

#define DEFINE_BASE_CLASS(ClassName)																					\
		Hale3D::EntManager::BaseFactory<ClassName> ClassName::CREATE_VAR_NAME(regBaseFactory, ClassName)(#ClassName);	
#endif
