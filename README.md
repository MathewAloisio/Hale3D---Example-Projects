# Hale3D Example Projects
* **AnimationDemo** - [available here](https://github.com/MathewAloisio/Hale3D---Example-Projects/tree/master/AnimationDemo)
	* Shows off the engine's ability to animate each individual joint of an entity while staying fast by taking advantage of all available threads to calculate final joint positions in as little time as possible without having to send bone data to the GPU.

# Purpose
* This repository is meant to showcase some of the engine's current features including:
	* ***Live Lua refresh***, allowing you to see your Lua code changes in real-time without restarting the application.
	* ***Automated Lua binding generation***, the engine's editor helps you by automatically exposing whatever C++ types, functions, and classes it can to Lua.
	* ***Multithreaded joint animation***, that evenly distributes the calculation of final joint positions amongst all available threads resulting in a significant FPS increase.
	* ***Easy resource importing***, the engine allows users to easily import TGA images to use as textures and provides a material system to allow users to specify information about the "material" as well as specify what shader to use for entities that use the given material. Currently only MD5 models nad animations are supported, but soon all assimp supported model formats will be import-able into the engine by simply clicking-and-dragging them into the editor. Skyboxes are stored in their own file, however they are simply a header and a collection of 6 TGA images written back-to-back into the `.skybox` file.
	* ***Powerful Lua integration and event system***, the engine allows users to easily add to or change engine behavior through the use of a powerful event system that I call LuaHook. There are also object, entity, and UI specific events that are executed for specific entities. See examples below:

> **C++ LuaHook Examples**
> ```
> LuaHook::Run("World::OnRendered", 1, [this]() { Interpreter::GLOBAL.PushUserType(static_cast<void*>(this), "World"); });
> -------------------------------------------------------------------------------------------------------------------------------
> if (!LuaHook::Callback("World::ShouldRender", 1, [this]() { Interpreter::GLOBAL.PushUserType(static_cast<void*>(this), "World"); })) return;```

> **Lua LuaHook Examples**
> ```
> hook.Add("World::OnRendered", function(pWorld) print("World rendered!") end)
> -------------------------------------------------------------------------------
> hook.Add("World::ShouldRender", function(pWorld) return false end) -- Never render the world!

> **C++ Entity/UIElement Lua Event**
> ```
>someEntity->RunLuaFunction("OnSomeEventName")
>
>bool retVal = someEntity->CallLuaFunction("ShouldDoSomething")
>
>someUIElement->RunLuaFunction("OnSomeEventName")
>
>bool retVal = someUIElement->CallLuaFunction("ShouldDoSomething")\

> **Lua Entity/UIElement Lua Event Behavior Defintion Example**
> ```
> someEntity.OnSomeEventName = function() end
> 
> someEntity.ShouldDoSomething = function() return true end -- Always do something!
