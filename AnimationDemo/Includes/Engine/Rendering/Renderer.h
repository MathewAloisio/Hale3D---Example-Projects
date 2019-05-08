/*----------------------------------/
/-------------Renderer--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_BASERENDERER
#define HALE3D_BASERENDERER

#include "Window.h"
#include "Font.h"
#include "Shader.h"
#include "Texture.h"
#include "Cubemap.h"
#include "RenderTarget.h"
#include "../Core/Entity.h"

#include "../Structs/Vertex.h"
#include "../Structs/Color4.h"
#include "../Structs/Vector4.h"

#include "../Libraries/Model.h"
#include "../Libraries/Primitives.h" // To expose UPPER_LEFT, UPPER_RIGHT, etc.

/* Standard include(s). */
#include <vector>

#ifdef DrawText
#undef DrawText
#endif

namespace Hale3D {
	class Window;
	class Skybox;
	class Renderer { //lua
	public:
		/* Rendering. */
		virtual void OnSortRenderables(Camera* pCamera, std::vector<Entity*>& pRenderables) = 0;
		virtual void RenderEntities(Camera* pCamera, const std::vector<Entity*>& pEntities) = 0;

		/* Rendering settings. */
		virtual void SetClearColor(const Color4& pColor) = 0; //lua
		virtual Color4 GetClearColor() const = 0; //lua
		virtual void SetMSAASamples(uint32_t pSamples = 0) = 0; //lua
		virtual uint32_t GetMSAASamples() const = 0; //lua
		virtual void SetFillMode(uint32_t pMode) = 0; //lua
		virtual uint32_t GetFillMode() const = 0; //lua

		/* Render target(s). */
		virtual void OnAllocateRenderTarget(RenderTarget* pRenderTarget, uint32_t pWidth, uint32_t pHeight, bool pEnableDepth) = 0;
		virtual void OnDeallocateRenderTarget(RenderTarget* pRenderTarget) = 0;
		virtual void BindRenderTarget(RenderTarget* pRenderTarget) = 0;
		virtual void UnbindRenderTarget(RenderTarget* pRenderTarget) = 0;
		virtual void ClearRenderTarget(RenderTarget* pRenderTarget) = 0;

		/* Cubemap(s) & skybox(es). */
		virtual void OnAllocateCubemap(Cubemap* pCubemap, CubemapFaceArray& pCubeFaces) = 0;
		virtual void OnDeallocateCubemap(Cubemap* pCubemap) = 0;

		virtual void OnAllocateSkybox(Skybox* pSkybox) = 0;
		virtual void OnDeallocateSkybox(Skybox* pSkybox) = 0;

		/* Entity handling. */
		virtual void OnAllocateEntity(Entity* pEntity) = 0;
		virtual void OnDeallocateEntity(Entity* pEntity) = 0;

		/* Model & animation handling. */
		virtual void OnAllocateModel(Model* pModel) = 0;
		virtual void OnDeallocateModel(Model* pModel) = 0;

		virtual void OnComputedVertexPosition(Vector3& pPosition) = 0;
		virtual void OnComputedVertexTextureCoord(Vector2& pUV) = 0;
		virtual void OnComputedVertexNormal(Vector3& pNormal) = 0;
		virtual void OnComputedVertexTangent(Vector3& pTangent) = 0;
		virtual void OnComputedVertexBitangent(Vector3& pBitangent) = 0;

		virtual void OnAllocateAnimation(Animation* pAnimation) = 0;
		virtual void OnDeallocateAnimation(Animation* pAnimation) = 0;

		/* Material & texture Handling. */
		virtual void BindMaterial(const Material* pMaterial) = 0;
		virtual void UnbindMaterial(const Material* pMaterial) = 0;
		virtual void OnAllocateTexture(Texture* pTexture) = 0;
		virtual void OnDeallocateTexture(Texture* pTexture) = 0;

		/* Shader handling. */
		virtual void OnAllocateShader(Shader* pShader) = 0;
		virtual void OnDeallocateShader(Shader* pShader) = 0;

		/* Font handling. */
		virtual void OnAllocateFont(Font* pFont) = 0;
		virtual void OnDeallocateFont(Font* pFont) = 0;
		virtual void OnAllocateGlyph(Font* pFont, uint32_t pGlyphIndex, const Glyph& pGlyph, const uint8_t* pBuffer) = 0;

		/* Callback handling. */
		virtual void OnStartFrame() = 0;
		virtual void OnFinishFrame() = 0;
		virtual void PreWindowCreated(Window* pWindow) = 0;
		virtual void OnWindowCreated(Window* pWindow) = 0;
		virtual void OnWindowDestroyed(Window* pWindow) = 0;
		virtual void OnWindowResized(Window* pWindow) = 0;
		
		/* Surface drawing. */
		// NOTE: (DrawLine and DrawRectangle(UpLeft, lowerRight, ...), and single-radius DrawRoundedRectangle are implemented by the engine using 'DrawRectangle(const RectanglePoints& ...)' and multi-radii 'DrawRoundedRectangle(...)' respectively.
		void DrawLine(const Vector2& pStart, const Vector2& pEnd, const Color4& pColor, BaseTexture* pTexture = nullptr, float pThickness = 1.f); //lua
		virtual void DrawText(const std::string& pText, Font* pFont, Vector2 pOrigin, const Color4& pColor, BaseTexture* pTexture = nullptr, const Vector2& pScale = Vector2(1.f, 1.f), float pRotationDeg = 0.f) = 0; //lua
		virtual void DrawCircle(const Vector2& pCenter, const Color4& pColor, float pRadius, BaseTexture* pTexture = nullptr, float pBorderPctRadius = 1.f) = 0; //lua
		virtual void DrawRectangle(const RectanglePoints& pPoints, const Color4& pColor, BaseTexture* pTexture = nullptr, bool pFill = true, float pRotationDeg = 0.f) = 0; //lua
		void DrawRectangle(const Vector2& pUpperLeft, const Vector2& pLowerRight, const Color4& pColor, BaseTexture* pTexture = nullptr, bool pFill = true, float pRotationDeg = 0.f); //lua
		void DrawRoundedRectangle(const Vector2& pUpperLeft, const Vector2& pLowerRight, float pRadius, const Color4& pColor, BaseTexture* pTexture = nullptr, bool pFill = true); //lua
		virtual void DrawRoundedRectangle(const Vector2& pUpperLeft, const Vector2& pLowerRight, const RectangleRadiuses& pRadiuses, const Color4& pColor, BaseTexture* pTexture = nullptr, bool pFill = true) = 0; //lua
		virtual void DrawCubemap(const Cubemap& pCubemap) = 0; //lua

		/* Global state. */
		static void SetCurrent(Renderer* pRenderer); //lua
		static Renderer* GetCurrent(); //lua
	};
}

#endif
