/*----------------------------------/
/-----------NullRenderer------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_NULLRENDERER
#define HALE3D_NULLRENDERER

/*Hale3D Include(s)*/
#include "../Renderer.h"

/* Standard include(s). */
#include <string>
#include <vector>

namespace Hale3D {
	class Window;

	class NullRenderer : public Renderer {
	public:
		NullRenderer();
		~NullRenderer();

		/* Rendering. */
		virtual void OnSortRenderables(Camera* pCamera, std::vector<Entity*>& pRenderables);
		virtual void RenderEntities(Camera* pCamera, const std::vector<Entity*>& pEntities);

		/* Rendering settings. */
		virtual void SetClearColor(const Color4& pColor);
		virtual Color4 GetClearColor() const;
		virtual void SetMSAASamples(uint32_t pSamples = 0);
		virtual uint32_t GetMSAASamples() const;
		virtual void SetFillMode(uint32_t pMode);
		virtual uint32_t GetFillMode() const;
		
		/* Render target(s). */
		virtual void OnAllocateRenderTarget(RenderTarget* pRenderTarget, uint32_t pWidth, uint32_t pHeight, bool pEnableDepth);
		virtual void OnDeallocateRenderTarget(RenderTarget* pRenderTarget);
		virtual void BindRenderTarget(RenderTarget* pRenderTarget);
		virtual void UnbindRenderTarget(RenderTarget* pRenderTarget);
		virtual void ClearRenderTarget(RenderTarget* pRenderTarget);

		/* Cubemap(s) & skybox(es). */
		virtual void OnAllocateCubemap(Cubemap* pCubemap, CubemapFaceArray& pCubeFaces);
		virtual void OnDeallocateCubemap(Cubemap* pCubemap);

		virtual void OnAllocateSkybox(Skybox* pSkybox);
		virtual void OnDeallocateSkybox(Skybox* pSkybox);

		/* Entity handling. */
		virtual void OnAllocateEntity(Entity* pEntity);
		virtual void OnDeallocateEntity(Entity* pEntity);

		/* Model & animation handling. */
		virtual void OnAllocateModel(Model* pModel);
		virtual void OnDeallocateModel(Model* pModel);
		
		virtual void OnComputedVertexPosition(Vector3& pPosition);
		virtual void OnComputedVertexTextureCoord(Vector2& pUV);
		virtual void OnComputedVertexNormal(Vector3& pNormal);
		virtual void OnComputedVertexTangent(Vector3& pTangent);
		virtual void OnComputedVertexBitangent(Vector3& pBitangent);

		virtual void OnAllocateAnimation(Animation* pAnimation);
		virtual void OnDeallocateAnimation(Animation* pAnimation);

		/* Material & texture handling. */
		virtual void BindMaterial(const Material* pMaterial);
		virtual void UnbindMaterial(const Material* pMaterial);
		virtual void OnAllocateTexture(Texture* pTexture);
		virtual void OnDeallocateTexture(Texture* pTexture);

		/* Shader handling. */
		virtual void OnAllocateShader(Shader* pShader);
		virtual void OnDeallocateShader(Shader* pShader);

		/* Font handling. */
		virtual void OnAllocateFont(Font* pFont);
		virtual void OnDeallocateFont(Font* pFont);
		virtual void OnAllocateGlyph(Font* pFont, uint32_t pGlyphIndex, const Glyph& pGlyph, const uint8_t* pBuffer);

		/* Callback handling. */
		virtual void OnStartFrame();
		virtual void OnFinishFrame();
		virtual void PreWindowCreated(Window* pWindow);
		virtual void OnWindowCreated(Window* pWindow);
		virtual void OnWindowDestroyed(Window* pWindow);
		virtual void OnWindowResized(Window* pWindow);

		/* Surface drawing. */
		virtual void DrawText(const std::string& pText, Font* pFont, Vector2 pOrigin, const Color4& pColor, BaseTexture* pTexture = nullptr, const Vector2& pScale = Vector2(1.f, 1.f), float pRotationDeg = 0.f);
		virtual void DrawCircle(const Vector2& pCenter, const Color4& pColor, float pRadius, BaseTexture* pTexture = nullptr, float pBorderPctRadius = 1.f);
		virtual void DrawRectangle(const RectanglePoints& pPoints, const Color4& pColor, BaseTexture* pTexture = nullptr, bool pFill = true, float pRotationDeg = 0.f);
		virtual void DrawRoundedRectangle(const Vector2& pUpperLeft, const Vector2& pLowerRight, const RectangleRadiuses& pRadiuses, const Color4& pColor, BaseTexture* pTexture = nullptr, bool pFill = true);
		virtual void DrawCubemap(const Cubemap& pCubemap);
	};
}

#endif
