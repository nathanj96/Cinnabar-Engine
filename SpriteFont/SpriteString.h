#ifndef SPRITE_STRING
#define SPRITE_STRING

#include <vector>
#include "SpriteFont.h"

//contains a vector of glyphs

class SpriteString
{
private:
	using GlyphCollection = std::vector<SpriteFont::Glyph*>;
	GlyphCollection glyphs;

	/** \brief	The sprite font the string will be rendered using. */
	SpriteFont* sfont;

	/** \brief	The height of the entire string.*/
	int height;
	/** \brief	The width of the entire string.*/
	int width;
	/** \brief	The starting x position of the rendered string.*/
	int posx;
	/** \brief	The starting y position of the rendered string. */
	int posy;
public:
	SpriteString() = delete;
	SpriteString(const SpriteString&) = default;
	SpriteString& operator=(const SpriteString&) = default;
	~SpriteString() = default;

	SpriteString(SpriteFont* sf, std::string s, int x, int y);

	/**********************************************************************************************//**
	 * \fn	SpriteString::SpriteString(SpriteFont* sf);
	 *
	 * \brief	Constructs an empty sprite string that uses the given sprite font. The string to render
	 * 			and the (x, y) coordinates need to be set separately before the sprite string will be usable.
	 *
	 * \param	sf	The sprite font to use.
	 **************************************************************************************************/

	SpriteString(SpriteFont* sf);

	int getHeight() const;
	int getWidth() const;
	void Render();
	void Set(int x, int y);

	/**********************************************************************************************//**
	 * \fn	void SpriteString::Set(SpriteFont* sf, std::string s, int x, int y);
	 *
	 * \brief	Essentially makes a new sprite string without creating another instance of one. This makes
	 * 			it so multiple strings can be rendered in succession without needing a separate SpriteString
	 * 			object for each; the Screen Log uses this technique.
	 *
	 * \param 	sf	The new sprite font to use.
	 * \param 	s 	The new string to render.
	 * \param 	x 	The new x position of the rendered string.
	 * \param 	y 	The new y position of the rendered string.
	 **************************************************************************************************/

	void Set(SpriteFont* sf, std::string s, int x, int y);
};

#endif SPRITE_STRING