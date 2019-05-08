/*----------------------------------/
/----------Hale3D Header------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_INC_HEADER
#define HALE3D_INC_HEADER

#include "Core.h"
#include "BuildConfig.h"

// Engine structures.
#include "Structs/AABB.h"
#include "Structs/Stream.h"
#include "Structs/Color4.h"
#include "Structs/Vertex.h"
#include "Structs/Matrix4.h"
#include "Structs/Vector4.h"
#include "Structs/Transform.h"
#include "Structs/ThreadPool.h"
#include "Structs/Quaternion.h"
#include "Structs/ReferenceTable.h"
#include "Structs/ExpandingBuffer.h"

// Engine user-interface.
#include "UI/UIElement.h"
#include "UI/Elements/UISlider.h"
#include "UI/Elements/UIRectangle.h"
#include "UI/Elements/UIFrameRectangle.h"

// Engine libraries.
#include "Libraries/Log.h"
#include "Libraries/JSON.h"
#include "Libraries/Time.h"
#include "Libraries/Math.h"
#include "Libraries/Util.h"
#include "Libraries/Model.h"
#include "Libraries/Endian.h"
#include "Libraries/System.h"
#include "Libraries/Random.h"
#include "Libraries/Console.h"
#include "Libraries/LuaHook.h"
#include "Libraries/Material.h"
#include "Libraries/Keycodes.h"
#include "Libraries/Keybinds.h"
#include "Libraries/Animation.h"
#include "Libraries/Tokenizer.h"
#include "Libraries/Threading.h"
#include "Libraries/EntManager.h"
#include "Libraries/FileSystem.h"
#include "Libraries/TGAManager.h"
#include "Libraries/Compression.h"
#include "Libraries/Interpreter.h"
#include "Libraries/CursesConsole.h"

// Engine core.
#include "Core/Object.h"
#include "Core/Entity.h"
#include "Core/World.h"

// Engine networking.
#include "Networking/Host.h"
#include "Networking/Peer.h"
#include "Networking/Packet.h"
#include "Networking/Server.h"
#include "Networking/Client.h"
#include "Networking/Reader.h"
#include "Networking/Message.h"
#include "Networking/Handler.h"
#include "Networking/Network.h"
#include "Networking/Interface.h"
#include "Networking/ChannelBuffer.h"
#include "Networking/ChannelBuffers/ReliableBuffer.h"
#include "Networking/ChannelBuffers/UnreliableBuffer.h"

// Engine entities.
#include "Entities/Camera.h"
#include "Entities/FlyCamera.h"
#include "Entities/PointLight.h"
#include "Entities/SpotLight.h"
#include "Entities/DirectionalLight.h"

// Engine rendering.
#include "Rendering/Font.h"
#include "Rendering/Shader.h"
#include "Rendering/Skybox.h"
#include "Rendering/Window.h"
#include "Rendering/Frustum.h"
#include "Rendering/Texture.h"
#include "Rendering/Renderer.h"
#include "Rendering/NullRenderer/NullRenderer.h"

// Engine physics.
#include "Physics/RigidBody.h"
#include "Physics/PhysicsWorld.h"
#include "Physics/PhysicsCollider.h"
#include "Physics/PhysicsCollision.h"

#endif
