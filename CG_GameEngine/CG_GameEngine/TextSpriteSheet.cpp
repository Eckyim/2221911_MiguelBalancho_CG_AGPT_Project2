#include "pch.h"
#include "TextSpriteSheet.h"

TextSpriteSheet::TextSpriteSheet(std::string filePath, int col, int row)
	:SpriteSheet(filePath, col, row)
{
	InitializeCharacterMap();
}

void TextSpriteSheet::InitializeCharacterMap()
{
    charToIndex[' '] = 0;
    charToIndex['!'] = 1;
    charToIndex['"'] = 2;
    charToIndex['#'] = 3;
    charToIndex['$'] = 4;
    charToIndex['%'] = 5;
    charToIndex['&'] = 6;
    charToIndex['\''] = 7;

    charToIndex['('] = 8;
    charToIndex[')'] = 9;
    charToIndex['*'] = 10;
    charToIndex['+'] = 11;
    charToIndex[','] = 12;
    charToIndex['-'] = 13;
    charToIndex['.'] = 14;
    charToIndex['/'] = 15;

    charToIndex['0'] = 16;
    charToIndex['1'] = 17;
    charToIndex['2'] = 18;
    charToIndex['3'] = 19;
    charToIndex['4'] = 20;
    charToIndex['5'] = 21;
    charToIndex['6'] = 22;
    charToIndex['7'] = 23;

    charToIndex['8'] = 24;
    charToIndex['9'] = 25;
    charToIndex[':'] = 26;
    charToIndex[';'] = 27;
    charToIndex['<'] = 28;
    charToIndex['='] = 29;
    charToIndex['>'] = 30;
    charToIndex['?'] = 31;

    charToIndex['@'] = 32;
    charToIndex['A'] = 33;
    charToIndex['B'] = 34;
    charToIndex['C'] = 35;
    charToIndex['D'] = 36;
    charToIndex['E'] = 37;
    charToIndex['F'] = 38;
    charToIndex['G'] = 39;

    charToIndex['H'] = 40;
    charToIndex['I'] = 41;
    charToIndex['J'] = 42;
    charToIndex['K'] = 43;
    charToIndex['L'] = 44;
    charToIndex['M'] = 45;
    charToIndex['N'] = 46;
    charToIndex['O'] = 47;

    charToIndex['P'] = 48;
    charToIndex['Q'] = 49;
    charToIndex['R'] = 50;
    charToIndex['S'] = 51;
    charToIndex['T'] = 52;
    charToIndex['U'] = 53;
    charToIndex['V'] = 54;
    charToIndex['W'] = 55;

    charToIndex['X'] = 56;
    charToIndex['Y'] = 57;
    charToIndex['Z'] = 58;
    charToIndex['['] = 59;
    charToIndex['\\'] = 60;
    charToIndex[']'] = 61;
    charToIndex['^'] = 62;
    charToIndex['_'] = 63;

    charToIndex['`'] = 64;
    charToIndex['a'] = 65;
    charToIndex['b'] = 66;
    charToIndex['c'] = 67;
    charToIndex['d'] = 68;
    charToIndex['e'] = 69;
    charToIndex['f'] = 70;
    charToIndex['g'] = 71;

    charToIndex['h'] = 72;
    charToIndex['i'] = 73;
    charToIndex['j'] = 74;
    charToIndex['k'] = 75;
    charToIndex['l'] = 76;
    charToIndex['m'] = 77;
    charToIndex['n'] = 78;
    charToIndex['o'] = 79;

    charToIndex['p'] = 80;
    charToIndex['q'] = 81;
    charToIndex['r'] = 82;
    charToIndex['s'] = 83;
    charToIndex['t'] = 84;
    charToIndex['u'] = 85;
    charToIndex['v'] = 86;
    charToIndex['w'] = 87;

    charToIndex['x'] = 88;
    charToIndex['y'] = 89;
    charToIndex['z'] = 90;
    charToIndex['{'] = 91;
    charToIndex['|'] = 92;
    charToIndex['}'] = 93;
    charToIndex['~'] = 94;
}

Sprite* TextSpriteSheet::GetCharacterSprite(char c)
{
    auto it = charToIndex.find(c);
    if (it != charToIndex.end()) {
        return GetSprite(it->second);
    }

    return GetSprite(0);
}

bool TextSpriteSheet::HasCharacter(char c) const
{
    return charToIndex.find(c) != charToIndex.end();
}