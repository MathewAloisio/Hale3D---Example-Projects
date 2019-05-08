/*----------------------------------/
/----------OpenGLRenderer-----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLRENDERER
#define HALE3D_EXTERNAL_OGLRENDERER

/* OpenGLRenderer include(s). */
#include "OpenGLTools.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLFramebuffer.h"

/* Hale3D include(s). */
#include "Engine/Libraries/Util.h"
#include "Engine/Libraries/Console.h"
#include "Engine/Libraries/Material.h"
#include "Engine/Rendering/Renderer.h"

/* Standard include(s). */
#include <string>
#include <vector>

/* Debugging definition(s). */
#ifndef NDEBUG
#define RENDERER_STATUS() reinterpret_cast<Hale3D::OpenGLRenderer*>(Hale3D::Renderer::GetCurrent())->CheckStatus(std::string(__FILE__), __LINE__) 
#else
#define RENDERER_STATUS()
#endif

enum class GLAttribute {
	Position,
	Texture,
	Normal,
	Tangent,
	Bitangent
};

namespace Hale3D {
	class Window;
	struct OpenGLTexture;

	class OpenGLRenderer : public Renderer { //lua
	public:
		/* Constructor(s) & destructor(s). */
		OpenGLRenderer(); //lua
		~OpenGLRenderer(); //lua

		/* Rendering. */
		virtual void OnSortRenderables(Camera* pCamera, std::vector<Entity*>& pRenderables);
		virtual void RenderEntities(Camera* pCamera, const std::vector<Entity*>& pEntities);

		/* Rendering setting(s). */
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

		/* Entity handling, */
		virtual void OnAllocateEntity(Entity* pEntity);
		virtual void OnDeallocateEntity(Entity* pEntity);

		/* Model handling. */
		virtual void OnAllocateModel(Model* pModel);
		virtual void OnDeallocateModel(Model* pModel);

		virtual void OnComputedVertexPosition(Vector3& pPosition);
		virtual void OnComputedVertexTextureCoord(Vector2& pUV);
		virtual void OnComputedVertexNormal(Vector3& pNormal);
		virtual void OnComputedVertexTangent(Vector3& pTangent);
		virtual void OnComputedVertexBitangent(Vector3& pBitangent);

		virtual void OnAllocateAnimation(Animation* pAnimation);
		virtual void OnDeallocateAnimation(Animation* pAnimation);

		/*Material & Texture Handling*/
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

		/* Renderer-specific methods. */
		void RenderEntity(Camera* pCamera, Entity* pEntity);
		void DrawSkybox(Camera* pCamera);
		void DestroyMSAA();
		void CheckStatus(const std::string& pFile, int pLine); // Checks for OpenGL errors.

		static void PrintVendorInfo(); //lua
		static void CreateConsoleCommands();
		static void DestroyConsoleCommands();

	protected:
		uint32_t fillMode;
		uint32_t msaaSamples;
		uint32_t msaaTexture;
		uint32_t depthTexture;
		uint32_t renderBuffer;
		Color4 clearColor;
		struct {
			OpenGLFramebuffer* default = nullptr;
			OpenGLFramebuffer* offscreen = nullptr;
		} framebuffers;

		struct {
			TextBuffer text;
			QuadBuffer quad;
		} buffers;

		struct {
			uint32_t width;
			uint32_t height;
		} screen;

		struct {
			Shader* text2D;
			Shader* rect2D;
			Shader* circle2D;
			Shader* primitive2D;
			Shader* roundedRect2D;
		} shaders;

		/* Private method(s). */
		static void _OnFramebufferResized(GLFWwindow* pWindow, int pWidth, int pHeight);

		/* Static members - protected. */
		static std::vector<std::string> __convars;
		static std::vector<std::string> __consoleCommands;
	};
}

#endif
