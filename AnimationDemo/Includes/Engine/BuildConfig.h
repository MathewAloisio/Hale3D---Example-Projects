/*----------------------------------/
/-----------BuildConfig-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_BUILD_CONFIGURATION
#define HALE3D_BUILD_CONFIGURATION

/* Standard include(s). */
#include <string>

/* Enable 'NETWORK_DEBUG' to enable network debugging. */
#define NETWORK_DEBUG

/* Defines the engine version. */
static const std::string ENGINE_NAME = "Hale3D";
static const std::string ENGINE_VERSION = "0.2.6a";
static const std::string ENGINE_TITLE = ENGINE_NAME + " v" + ENGINE_VERSION;

/* Defines the engine model and animation file extensions. */
static const std::string ENGINE_MODEL_EXT = ".mdl";
static const std::string ENGINE_ANIMATION_EXT = ".anim";
static const std::string ENGINE_PHYSICSMATERIAL_EXT = ".pmf";
static const std::string ENGINE_PHYSICSSHAPE_EXT = ".psf";
static const std::string ENGINE_SKYBOX_EXT = ".skybox";

/* Controls the desired physics FPS of the engine. (Default: 50) */
static constexpr int PHYSICS_FRAME_RATE = 50;

/* Determines the FPS cap of the engine. (Default: 240) */
static constexpr int DEFAULT_FPS_CAP = 1500;

/* Determines the maximum # of textures a material can hold. */
static constexpr size_t MAX_MATERIAL_TEXTURES = 16; // Max of MAX_MATERIAL_TEXTURES textures per material.

#endif
