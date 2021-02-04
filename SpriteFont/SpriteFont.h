// SpriteFont

#ifndef _SpriteFont
#define _SpriteFont

#include <string>
#include <xmllite.h>
#include <map>

class Texture;
class CSprite;

class SpriteFont
{
public:
	using Key = int;
	using Glyph = CSprite;

private:

	/** \brief	A name assigned to the string font. This name must match the key used by FontTexture. */
	std::string Name;
	/** \brief	Pointer to the texture that the glyphs will be extracted from. */
	Texture* FontTexture;
	using FontMap = std::map< Key, Glyph* >;
	FontMap fontmap;

	/**********************************************************************************************//**
	 * \fn	void SpriteFont::XMLtoCollection(std::string filename);
	 *
	 * \brief	Internal method for parsing the XML file associated with FontTexture. This should only
	 * 			be called in the SpriteFont's constructor, and the user should not access or modify it.
	 *
	 * \param 	filename	The name of the XML file.
	 **************************************************************************************************/

	void XMLtoCollection(std::string filename);

	/**********************************************************************************************//**
	 * \fn	void SpriteFont::ElementTextToInt(IXmlReader* pReader, int& out);
	 *
	 * \brief	Converts XML elements into integers used to construct glyphs.
	 *
	 * \param pReader	If non-null, the reader.
	 * \param out	   	A reference to an integer variable that the result will be stored in.
	 **************************************************************************************************/

	void ElementTextToInt(IXmlReader* pReader, int& out);

public:
	SpriteFont() = delete;
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;
	//need to do
	~SpriteFont();

	SpriteFont(std::string path);

	/**********************************************************************************************//**
	 * \fn	Glyph* SpriteFont::GetGlyph(char c);
	 *
	 * \brief	Returns the glyph associated with a given char.
	 *
	 * \param 	c	The char.
	 *
	 * \returns	The glyph.
	 **************************************************************************************************/

	Glyph* GetGlyph(char c);
	//
};

#endif _SpriteFont