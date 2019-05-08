/*----------------------------------/
/-----------OpenGLTools-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLTOOLS
#define HALE3D_EXTERNAL_OGLTOOLS

/*Include GLAD & OpenGL*/
#include <glad/glad.h>

/*Standard Include(s)*/
#include <string>

#define GL_GET_STRING(GLIn)													\
	std::string((char*)(glGetString(GLIn)))

namespace Hale3D {
	namespace OpenGLTools {
		uint32_t CreateMSAATextue(int pMSAALevel, int pWidth, int pHeight);
		uint32_t CreateAttachmentTexture(int pWidth, int pHeight, int pType);
	}
}

#endif
