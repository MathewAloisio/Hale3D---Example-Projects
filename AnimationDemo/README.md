## AnimationDemo

> A program that demonstrates the use of my game engine project in the animating of 3D models.

> The following two screenshots compare the FPS in the scene with the first image having ***multithreading*** disabled and the second image ***multithreading*** is enabled. Note the FPS difference.


> ![](https://raw.githubusercontent.com/MathewAloisio/Hale3D---Example-Projects/master/AnimationDemo/MT-DISABLED.png "Multithreading Disabled")


> ![](https://raw.githubusercontent.com/MathewAloisio/Hale3D---Example-Projects/master/AnimationDemo/MT-ENABLED.png "Multithreading Enabled")

> The scene shows the rendering of a large number of **uniquely** animated entities. Each entity in the demo has it's own skeleton, animations and bind-pose model buffers are shared however each entity has it's own model buffer.
> - Each entity has 36 **uniquely** animated joints. Each joint of each entity is running it's own animation instance. Joints can be independently animated to play any animation at any time in the animations cycle without affecting other joints on the skeleton. For simplicity the engine always provides users with functions to apply animations to all joints in an entity with a single call, however this demo does not use that function.
> - The engine makes use of **multhreading**. Every joint is sorted into as many lists are there are available threads on the computer, threads are then launched that calculate the animations of all joints as fast as possible, splitting the work evenly amongst all available threads before returning to the main application thread as quickly as possible. On my computer in this demo scene I experienced an increase in FPS from ~200 to ~225 just by splitting up this workload.
> - **No** *instancing* or *batching* techniques are used in this demo! The models are only the same because the engine's model importer is currently limited to only import basic Doom MD5 models as the internal model format is a binary version of it. In the near future the AssimpImporter will be released for the engine's editor which will allow the importation of all Assimp supported model and image assets.
> - The demo does not utilize the engine's optional Lua scripting, although the same exact demo would be possible in Lua using almost identical code.
> - All entities in the demo are assigned random scales between 25 and 100 percent of their original size.
> - Because of the design of the model format, one animation may be used by any model that shares the same skeletal structure used in the animation. Because animations and models are separated into individual files, disk space usage is much lower in games.

> If you launch the project using the provided batch file, type 'help' in the console for a list of console commands.

> Normally, when working with the engine you wouldn't have every library in the project. This project contains all neccesary dll and lib files as it is intended to be built without access to the engine.

> This demo is intended only for Windows OS.