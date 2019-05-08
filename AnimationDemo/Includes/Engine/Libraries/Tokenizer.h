/*----------------------------------/
/---------String Tokenizer----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_TOKENIZER
#define HALE3D_TOKENIZER
#include "../BuildConfig.h"

#include <string>
#include <vector>

namespace Hale3D {
	class Tokenizer {
	public:
		/* Constructor(s) & destructor(s). */
		Tokenizer(const std::string& pInput, const bool pIgnoreFirst = false);
		
		/*Variables*/
		std::vector<std::string> m_Tokens;
		std::string m_Token;
		std::string m_First;

	private:
		short _tokenCount;

		/*Internal Methods*/
		void AddChar(char pChar);
		void FinishToken();
	};
}

#endif
