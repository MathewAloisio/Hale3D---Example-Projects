## Renderer Stanards - Hale3D
*-----------------------------------------------------------------*
> IMPORTANT NOTICE: All systems in the engine assume an upper-left origin. (the top-left corner of the monitor is Vector2(0, 0))
> This means that when you are working with OpenGL (expects lower-left origin) you must convert from the engine-provided upper-left origin data to lower-left origin.
> Why did we choose upper-right origin for the engine? Simple, more graphics APIs and third party libraries are made with upper-right origin in mind than lower-left.

***(1)*** The implemented renderer ***MUST*** provide overloads for all *virtual* methods in the base ```Renderer``` class.

>***(1.a)*** *NOTE: The renderer implementation is responsible for the binding of the textures in a material, along with all the material uniforms.*

***(2)*** The implemented renderer ***MUST*** explicitly call ```Entity::PreDraw()``` and ```Entity::PostDraw()```. [This is necessary because the vector of sorted renderable entities are passed to the renderer so it cannot manually execute these methods at the appropriate times. See: *(2.a) Rationale*] 

>***(2.a) Rationale:***
 The renderer is passed the whole vector of sorted-entities instead of an abstract call that's execute per-entity because it provides the renderer with more flexibility as to how it will carry out the actual drawing of these objects. For example, the renderer may choose to delegate threads to handle certain groups of entities. The downside to this is the described in renderer standard (II).
 There is however one exception to this, if the renderer implementation is "null" (does not actual perform rendering) these calls may be skipped as of course, the entity will never be drawn therefore there is no pre/post draw.
 Keep in mind though, the engine comes with a ```NullRenderer``` class intended for use with dedicated servers, etc... so consider if this suites your needs before making your own "null" renderer implementation.
 
***(3)*** If the implemented renderer elects to not draw any entities, they must be removed from the ```renderable entities vector``` during the call to ```Renderer::SortRenderables(std::vector<Entity*> pRenderables)```. (As the engine marks all entities that make it past this point as visible.)

***(4)*** If an object that is defined by the engine provides a remove method, i.e: ```SomeClass::Remove()```, this ***MUST*** be used instead of the ```delete``` keyword.

***(5)*** MOST data types that are passed to the renderer (i.e: Model, Mesh, Texture, Window, Shader.) provide the follows methods: ```void SetRenderData(void* pData);``` and ```template <typename T> T GetRenderData();```. The developer ***MAY*** choose to store any type as a void pointer in these structures. The developer MAY access this data by using the template ```T GetRenderData();``` to return the data stored in the void pointer, statically casted to the appropriate type. [See: *(5.a) Example*] 

>***(5.a) Example:***   *Assume ```MyTextureType``` is our renderer-specific texture implementation*

    void MyRenderer::OnAllocateTexture(Texture* pTexture) {
        MyTextureType* obj = new MyTextureType;
        pTexture->SetData(static_cast<void*>(obj));
    }

    void MyRenderer::OnDeallocateTexture(Texture* pTexture) {
        // Note how the custom texture object is retrieved, and destroyed.
        delete pTexture->GetData<MyTextureType*>();
    }
	
***(6)*** The renderer implementation ***MAY*** elect to flip the origin of the pixels for any image to any origin using the ```TGAManager``` class provided as the member ```TGAManager Texture::image```. The programmer can always assume that: 
> 
* [i] The images origin may be changed using the provided ```TGAManager::SetOrigin(TGAOrigin pOrigin)``` method. 
* [ii] The engine will load the image using the ```TGAOrigin::Any``` enumerate value, meaning the images origin is the same as what it was saved as. 
* [iii] ```TGAManager::SetOrigin(TGAOrigin pOrigin)``` will choose to not carry out any pixel-flipping operations if the images origin is already the same as the one specified as ```pOrigin```. 
* [iv] The ```Texture::image``` member always is constructed with arguments equivalent to the following: ```image(pTexture->GetPath(), TGAManager::ORDER_RGBA, TGAOrigin::Any)```. 
* [v] The image will be in ***Targa (.tga)*** format and can be read using the engines ```TGAManager``` class.

***(7)*** The renderer implementation MUST handle the information handling & binding of shaders, the engine handles nothing related to shaders. The engine does nothing more than provide a unified function to load shaders for the material system to use. [See: *(7.a) Example*]

>***(7.a) Example:*** *This example is taken from the basic OpenGLRenderer implementation.*

	void OpenGLRenderer::RenderEntity(Camera* pCamera, Entity* pEntity) {
		// Render each mesh of the entity.
		for (size_t i = 0; i < pEntity->GetModel()->m_Meshes.size(); ++i) {
			// Determine what material to render this mesh with.
			Material* material = pEntity->GetMaterialOverride();
			if (material == nullptr) material = pEntity->GetMaterial(i);

			// Bind shader, push uniforms.
			OpenGLShader* shader = material->GetShader()->GetRenderData<OpenGLShader*>();
			shader->Bind();
			shader->SetMatrix4("cameraMatrix", pCamera->GetMatrix());
			shader->SetMatrix4("modelMatrix", pEntity->GetTransform()->GetMatrix());
			shader->SetVector4("entityColor", pEntity->GetColor());

			// Bind texture(s).
			material->Bind();

			// Draw the mesh.
			OpenGLMesh& mesh = pEntity->GetModel()->GetRenderData<OpenGLModel*>()->m_Meshes[i];
			mesh.Bind(pEntity->GetMeshBuffer(i));
			mesh.Draw(pEntity->GetMeshBuffer(i));
		}
	}

***(8)*** The renderer implementation ***MUST be built as a static library***. (GLFWs weird memory setup causes issues when accessed by DLLs or DYLIBs.)

***(9) The renderer implementation ***MAY*** elect to modify vertices of a mesh when a call to ```Mesh::RecomputeVertices()``` is made (i.e: when the mesh is first created.). The renderer implementation ***MAY*** elect to flip/invert/modify any vertex element including texture coordinates at this time. By default the texture coordinates are assumed to be an ***upper-left origin.*** Editing these vertices at any other time may work, but the behavior is considered to be undefined.

>***(9.a) Example:*** *Assume MyRenderer is some renderer implementation.*
	
	void MyRenderer::OnComputedVertices(std::vector<Vertex>& pVertices) {
		for (const auto& vertex : pVertices) {
			// Flip texture coordinates to bottom-left origin. (Invert texture coordinate 'y'.)
			vertex.texture.y = -vertex.texture.y;
		}
	}
	
***(10)*** In the renderer implementation, ```MyRenderer::OnEngineUpdate()``` is called by the engine at the end of every engine-core update. (Post world/window/console update.)

***(11)*** Renderer implementations MUST implement ```Context::Draw<...>``` methods. The implementation can choose to implement and optimize generic ```Context::Draw<...>``` methods in any way they choose. The engine merely calls these methods and makes no assumptions.

***(12)*** Fonts are loaded using FreeType. When implementing ```MyRenderer::DrawText``` and/or Font support refer to: https://www.freetype.org/freetype2/docs/documentation.html

>***(12.a)*** *```MyRenderer::OnAllocateGlyph(Font* pFont, uint32_t pGlyphIndex, const Glyph& pGlyph, const uint8_t* pBuffer)``` allows us to allocate resources for font glyphs as they are created, or simply track them. ```pBuffer``` contains pixel data that is lost at the end of this callback.
	Note that only glyphs that are correctly loaded, and that have size are sent to the renderer. (So characters like ' ' will in most cases, not be sent to the renderer as no texture needs to be allocated.)*

>***(12.b)*** *The renderer implementation MUST use ```Glyph::IsRenderable()``` when drawing characters as the engine WILL NOT pass invisible glyphs (like the space character) to ```MyRenderer::OnAllocateGlyph(...)```, nor will they be taken into account in the atlas size.*	
		
>***(12.c)*** *The renderer implementation MAY choose to implement a font atlas, in this case the width, and the height required for the atlas texture can be obtained via ```Font::GetAtlas(Width/Height)``` anytime after ```MyRenderer::OnAllocateFont(...)``` has been called.*	

>***(12.d)*** *IF the renderer implementation chooses to implement an atlas, the renderer MUST use the provided ```Glyph::m_AtlasOffset``` member when positioning glyphs in the atlas texture.*		
	
>***(12.e)*** *When ```MyRenderer::OnAllocateFont(Font* pFont, uint32_t pAtlasWidth, uint32_t pAtlasHeight)``` is called, ```pFont->GetGlyphs()``` is empty. Access: ```pFont->GetGlyphs().at(code)```*
 
***(13)*** When implementing shaders a renderer implementation MAY choose to use ```static bool Shader::GetDebugMode()``` to determine if the engine has asked the renderer implementation to supply debug information.

>***(13.a)*** *Example: The OpenGLRenderer implementation will print a warning if ```Shader::GetDebugMode() == true``` and a uniform variable could not be found.*

***(14)*** When implementing ```MyRenderer::Draw<..>``` methods that support textures, UV coordinates MUST map as a quad would even with circles, rounded rectangles, etc.

***(15)*** Renderer implementations ***MUST*** allow for binding and unbinding of ```RenderTarget``` types. The renderer implementation ***MUST*** draw to the currently bound ```RenderTarget``` if one is bound. 

## Provided GLSL examples - Hale3D
The following is an example of ```circle2D.vert``` from the engine's OpenGLRenderer:
```
#version 420 core

layout (location = 0) in vec2 vertexPositions;

out vec2 UV;

const vec2 UVArray[4] = vec2[4](
	vec2(1.0f, 1.0f),
	vec2(1.0f, 0.0f),
	vec2(0.0f, 1.0f),
	vec2(0.0f, 0.0f)
);

void main() {
	gl_Position = vec4(vertexPositions, 0.0f, 1.0f);
	UV = UVArray[gl_VertexID];
}
```

The following is an example of ```circle2D.frag``` from the engine's OpenGLRenderer:
```
#version 420 core

layout (location = 0) out vec4 outColor;

in vec2 UV;

uniform float radius;
uniform float borderPctRadius;
uniform vec2 position;
uniform vec4 color;
uniform bool useTexture;
uniform sampler2D texture0; // texture0 - image.

float circle(in vec2 pUV, in float pInnerRadius, in float pUVLength) {
	if (pUVLength > radius) discard; // Although anti-aliasing would handle it, this is a less expensive check.
	if (borderPctRadius < 1.0f && pUVLength < pInnerRadius) discard;
	float pctRadius = radius * 0.01f;
	return 100.0f - smoothstep(radius - pctRadius, radius + pctRadius, dot(pUV, pUV));
}

float antialias(in vec2 pUV, in float pInnerRadius, in float pUVLength) {
	const float border = 1.0f;
	float uvDist = radius - pUVLength; // Outer-edge check. (abs() not needed as pixel is discarded earlier if pUVLength > radius.)
	if (uvDist > border) {
		uvDist = abs(pInnerRadius - pUVLength); // Inner-edge check.
		if (uvDist < border) {
			return uvDist / border;
		}
		else { return 1.0f; }
	}
	else { return uvDist / border; }
}

void main() {
	// Calculate fragment distance from center. along with this length & the inner radius.
	vec2 uv = gl_FragCoord.xy - position;
	float uvLength = length(uv);
	float innerRadius = radius - (radius * borderPctRadius);
	
	// Output the final color.
	if (useTexture) {
		vec4 mixedColor = mix(texture(texture0, UV), color, 0.5f);
		outColor = vec4(mixedColor.xyz * vec3(circle(uv, innerRadius, uvLength)), antialias(uv, innerRadius, uvLength) * mixedColor.w);
	}
	else { outColor = vec4(color.xyz * vec3(circle(uv, innerRadius, uvLength)), antialias(uv, innerRadius, uvLength) * color.w); }
}
```

The next code snippet is the implementation of ```OpenGLRenderer::DrawCircle(...)```:
```
void OpenGLRenderer::DrawCircle(const Vector2& pCenter, const Color4& pColor, float pRadius, BaseTexture* pTexture, float pBorderPctRadius) {
	Window* window = Window::GetCurrent();

	// Bind shader, push uniforms.
	OpenGLShader* shader = shaders.circle2D->GetRenderData<OpenGLShader*>();

	shader->Bind();
	shader->SetFloat("radius", pRadius); // FS
	shader->SetFloat("borderPctRadius", pBorderPctRadius); // FS
	shader->SetVector2("position", Vector2(pCenter.x, window->GetSize().y - pCenter.y)); // FS - NOTE: y component converted to lower-left origin.
	shader->SetVector4("color", pColor); // FS

	if (pTexture != nullptr) {
		shader->SetInt("useTexture", 1); // FS
		pTexture->GetRenderData<OpenGLTexture*>()->Bind(0, shader); // FS - texture0
	}
	else { shader->SetInt("useTexture", 0); } // FS

	// Calculate fitted quad boundaries. (Reduces # of fragments rasterizer has to process.)
	buffers.quad.Bind();
	Vector2 scaledCenter = ((pCenter / window->GetSize()) * 2) - 1; // Center in clip-pos.
	Vector2 scaledLengths = Vector2((pRadius * 2) / window->GetSize().x, (pRadius * 2) / window->GetSize().y);

	// Before generating the vertices, flip the y components. (Convert to lower-left origin. [the engine passes the renderer upper-left origin data.])
	scaledCenter.y *= -1;

	const std::array<Vector2, 4> vertices = {
		Vector2(scaledCenter.x - scaledLengths.x, scaledCenter.y + scaledLengths.y), // Upper-left corner.
		Vector2(scaledCenter.x - scaledLengths.x, scaledCenter.y - scaledLengths.y), // Lower-left corner.
		Vector2(scaledCenter.x + scaledLengths.x, scaledCenter.y + scaledLengths.y), // Upper-right corner.
		Vector2(scaledCenter.x + scaledLengths.x, scaledCenter.y - scaledLengths.y)  // Lower-right corner.
	};
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector2), vertices.data(), GL_DYNAMIC_DRAW);

	// Execute draw call.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(vertices.size()));
}
```

> Note that the non-virtual ```Renderer::DrawLine(...)```, ```Renderer::DrawRectangle(Vector2 pUpperLeft, Vector2 pLowerRight, ...)``` and single-radius ```Renderer::DrawRoundedRectangle(...)``` functions are implemented by the engine using ```Renderer::DrawRectangle(const RectanglePoints& ...)``` for both ```DrawLine``` and ```DrawRectangle``` from origin and end-points, and multi-radii ```Renderer::DrawRoundedRectangle(...)``` for implementing single-radius ```DrawRoundedRectangle```.

> NOTE: The other Renderer::Draw... methods are more simple to implement and will not be covered in this document.

## Suggested optimization(s) - Hale3D
> (I) The renderer implementation MAY elect to perform frustum culling against the active camera based on the axis-aligned bounding box (AABB) provided by each MeshBuffer. This optimization is suggested for renderers intended to render large models made of smaller meshes.