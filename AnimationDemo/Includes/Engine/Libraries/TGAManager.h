/*----------------------------------/
/------------TGAManager-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_TGAMANAGER
#define HALE3D_TGAMANAGER

/* Standard include(s). */
#include <string>
#include <stdint.h>

/* Hale3D include(s). */
#include "../Structs/ExpandingBuffer.h"

// Definitions
#define TGA_ATTRIB_BITS static_cast<uint8_t>((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3))
#define TGA_RL_BIT static_cast<uint8_t>(1 << 4)
#define TGA_TB_BIT static_cast<uint8_t>(1 << 5)
#define TGA_UNUSED_BITS static_cast<uint8_t>((1 << 6) | (1 << 7))

namespace Hale3D {
	enum class TGAOrigin : uint8_t { //lua
		UpperRight = 0, // Upper right. (0)
		UpperLeft,		// Upper left.  (1)
		LowerLeft,		// Lower left.  (2)
		LowerRight,		// Lower right. (3)
		Any				// Any			(4)
	};

	enum class TGAColorMapType : uint8_t { //lua
		None = 0,
		Palette = 1
	};

	enum class TGAImageType : uint8_t { //lua
		// Uncompressed
		None = 0,
		Indexed = 1,
		RGB = 2,
		Grayscale = 3,
		
		// Compressed
		RLE_Indexed = 9,
		RLE_RGB = 10,
		RLE_Grayscale = 11
	};

	struct TGADimensions { //lua
		uint16_t x; //lua
		uint16_t y; //lua
	};

	struct TGAExtent { //lua
		uint16_t width; //lua
		uint32_t height; //lua
	};

	struct TGAOrder { //lua
		uint32_t r; //lua
		uint32_t g; //lua
		uint32_t b; //lua
		uint32_t a; //lua

		bool operator==(const TGAOrder& pOther) const; //lua
	};

	class TGAManager { //lua
	public:
		/* Constructor(s) & destructor(s). */
		TGAManager() : m_Data(nullptr) {};
		TGAManager(ExpandingBuffer& pBuffer, const TGAOrder& pOrder, TGAOrigin pOrigin);
		TGAManager(const std::string& pPath, const TGAOrder& pOrder, TGAOrigin pOrigin); //lua
		~TGAManager(); //lua

		/* Methods. */
		void SetOrigin(TGAOrigin pOrigin); //lua
		void FlipVertical(); //lua
		void FlipHorizontal(); //lua
		//bool HasExtensionArea() const;
		//bool HasFooterArea() const;
		bool IsRightOrigin() const; //lua
		bool IsTopOrigin() const; //lua
		//bool IsSignatureValid() const;
		size_t GetDataSize() const; //lua 
		Color4 GetPixelColor(size_t pIndex) const; //lua

		/* File operation(s). */
		// WARNING:  The TGAManager::Save functions save the TGA image with as minimal information as possible. (The image is likely to differ in binary form from the original.)
		//			Because of this, no color map is ever stored and if pWriteFooter is false, the resulting file won't contain a TGA2.0 footer,
		//			it will however be load-able via the engine as the engine doesn't validate or load the footer of TGA image files to remain as
		//			fast as possible.
		void Save(Stream& pBuffer, bool pWriteFooter = false) const;
		bool Save(const std::string& pPath, bool pOverwrite, bool pWriteFooter = false) const; //lua

		/* Members. */
		// TGA Header
		// Image ID length, Color map type, Image type.
		uint8_t m_IDLength; //lua
		TGAColorMapType m_ColorMapType;	//lua Color map type - See "enum class TGAColorMapType : uint8_t".
		TGAImageType m_ImageType;		//lua Image type - See "enum class TGAImageType : uint8_t".
				
		// Colormap specification
		struct {
			uint16_t m_Start;			// Index of 1st entry in colorMap.
			uint16_t m_Length;			// # of entries.
			uint8_t m_EntrySize;		// # of bits per entry.
		} m_ColorMap;

		// Image specification
		TGADimensions m_Origin;			//lua Origin: x, y.
		TGAExtent m_Extent;				//lua Size: x, y.

		uint8_t m_BitsPerPixel;			//lua 8, 16, 24, 32. (Pixel depth)
		uint8_t m_DescriptorBits;		//lua Bits 3-0 give alpha channel depth.
										// Bits 5-4 give direction.

		/*struct {
			uint16_t m_Size; // Extension area size. (Bytes)

			// Author info.
			struct {
				char m_Name[41];
				char m_Comment[324];
			} m_Author;

			char m_Timestamp[12]; // Timestamp - Date/Time

			// Job info.
			struct {
				char m_ID[41];
				char m_Time[6];
			} m_Job;

			// Software info.
			struct {
				char m_ID[41];
				char m_Version[3];
			} m_Software;

			uint32_t m_KeyColor;
			uint32_t m_AspectRatio;
			uint32_t m_Gamma;
			
			// Color correction, postage stamp, & scan line offsets.
			struct {
				uint32_t m_ColorCorrection;
				uint32_t m_Postage;
				uint32_t m_ScanLine;
			} m_Offsets;

			uint8_t m_AlphaChannel; // Specifies the alpha channel
		} m_Extension;*/
		
		/*struct {
			// Extension & Developer area offsets.
			struct {
				uint32_t m_Extension;
				uint32_t m_Developer;
			} m_Offsets;

			char m_Signature[17];
		} m_Footer;*/

		TGAOrder m_Order; //lua
		uint32_t* m_Data = nullptr;

		/* Static member(s). */
		static constexpr TGAOrder ORDER_RGBA = { 0, 8, 16, 24 }; //lua
		static constexpr TGAOrder ORDER_BGRA = { 16, 8, 0, 24 }; //lua

		//static const size_t FOOTER_SIZE;
		//static const size_t EXTENSION_SIZE;
		// NOTE: Extension area now silently ignored.
		// NOTE: Developer area silently ignored.
		// NOTE: Footer area now silently ignored.

	private:
		//bool _hasFooterArea = false;
		TGAOrigin _quad;
	};
}

#endif
