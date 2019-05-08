/*----------------------------------/
/-----------RenderTarget------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
// - A render target allows for scenes to be rendered to a texture in the underlying format of the renderer, they can be drawn to the screen or manually converted into TGA textures.
// - RenderTargets are a generic renderer type, their functionality is implemented by the renderer.
// - When bound renderer implementations MUST render to the RenderTarget's underlying texture.
#ifndef HALE3D_BASERENDERTARGET
#define HALE3D_BASERENDERTARGET

#include "BaseTexture.h"

namespace Hale3D {
	class RenderTarget : public BaseTexture { //lua
	public:
		/* Constructor(s) & destructor(s). */
		RenderTarget(uint32_t pWidth, uint32_t pHeight, bool pEnableDepth); //lua
		~RenderTarget(); //lua

		/* Binding & unbinding. */
		void Bind(); //lua
		void Unbind(); //lua

		/* Width & height. */
		const uint32_t& GetWidth() const; //lua
		const uint32_t& GetHeight() const; //lua

		/* Clear & reset. */
		void Clear(); //lua

	private:
		struct {
			uint32_t width;
			uint32_t height;
		} _size;
	};
}
#endif
