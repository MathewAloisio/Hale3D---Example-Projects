/*----------------------------------/
/---------OpenGLFramebuffer---------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLFRAMEBUFFER
#define HALE3D_EXTERNAL_OGLFRAMEBUFFER

namespace Hale3D {
	class OpenGLFramebuffer {
	public:
		OpenGLFramebuffer();
		OpenGLFramebuffer(int pFramebufferID);
		~OpenGLFramebuffer();

		/* Methods. */
		void Clear();
		void BlitTo(int pWidth, int pHeight, unsigned int pOtherFBO, int pOtherWidth, int pOtherHeight);
		void BindWriting();
		void BindReading();
		void UnbindWriting();
		void UnbindReading();
		unsigned int GetID();
		bool IsActiveRead();
		bool IsActiveWrite();

		/* Static methods. */
		static int GetActiveReadFBO();
		static int GetActiveWriteFBO();

	private:
		unsigned int framebufferID;
	};
}
#endif
