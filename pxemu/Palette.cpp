#include "stdafx.h"
#include "Palette.h"

/////////////////////////////////////////////////////////////////////////////
COLORREF Palette::m_palette[NUM_COLORS] = {
	RGB(0, 0, 0),
	RGB(128, 0, 0),
	RGB(0, 128, 0),
	RGB(128, 128, 0),
	RGB(0, 0, 128),
	RGB(128, 0, 128),
	RGB(0, 128, 128),
	RGB(192, 192, 192),
	RGB(192, 220, 192),
	RGB(166, 202, 240),
	RGB(255, 240, 212),
	RGB(255, 226, 177),
	RGB(255, 212, 142),
	RGB(255, 198, 107),
	RGB(255, 184, 72),
	RGB(255, 170, 37),
	RGB(255, 170, 0),
	RGB(220, 146, 0),
	RGB(185, 122, 0),
	RGB(150, 98, 0),
	RGB(115, 74, 0),
	RGB(80, 50, 0),
	RGB(255, 227, 212),
	RGB(255, 199, 177),
	RGB(255, 171, 142),
	RGB(255, 143, 107),
	RGB(255, 115, 72),
	RGB(255, 87, 37),
	RGB(255, 85, 0),
	RGB(220, 73, 0),
	RGB(185, 61, 0),
	RGB(150, 49, 0),
	RGB(115, 37, 0),
	RGB(80, 25, 0),
	RGB(255, 212, 212),
	RGB(255, 177, 177),
	RGB(255, 142, 142),
	RGB(255, 107, 107),
	RGB(255, 72, 72),
	RGB(255, 37, 37),
	RGB(255, 0, 0),
	RGB(220, 0, 0),
	RGB(185, 0, 0),
	RGB(150, 0, 0),
	RGB(115, 0, 0),
	RGB(80, 0, 0),
	RGB(255, 212, 227),
	RGB(255, 177, 199),
	RGB(255, 142, 171),
	RGB(255, 107, 143),
	RGB(255, 72, 115),
	RGB(255, 37, 87),
	RGB(255, 0, 85),
	RGB(220, 0, 73),
	RGB(185, 0, 61),
	RGB(150, 0, 49),
	RGB(115, 0, 37),
	RGB(80, 0, 25),
	RGB(255, 212, 240),
	RGB(255, 177, 226),
	RGB(255, 142, 212),
	RGB(255, 107, 198),
	RGB(255, 72, 184),
	RGB(255, 37, 170),
	RGB(255, 0, 170),
	RGB(220, 0, 146),
	RGB(185, 0, 122),
	RGB(150, 0, 98),
	RGB(115, 0, 74),
	RGB(80, 0, 50),
	RGB(255, 212, 255),
	RGB(255, 177, 255),
	RGB(255, 142, 255),
	RGB(255, 107, 255),
	RGB(255, 72, 255),
	RGB(255, 37, 255),
	RGB(255, 0, 255),
	RGB(220, 0, 220),
	RGB(185, 0, 185),
	RGB(150, 0, 150),
	RGB(115, 0, 115),
	RGB(80, 0, 80),
	RGB(240, 212, 255),
	RGB(226, 177, 255),
	RGB(212, 142, 255),
	RGB(198, 107, 255),
	RGB(184, 72, 255),
	RGB(170, 37, 255),
	RGB(170, 0, 255),
	RGB(146, 0, 220),
	RGB(122, 0, 185),
	RGB(98, 0, 150),
	RGB(74, 0, 115),
	RGB(50, 0, 80),
	RGB(227, 212, 255),
	RGB(199, 177, 255),
	RGB(171, 142, 255),
	RGB(143, 107, 255),
	RGB(115, 72, 255),
	RGB(87, 37, 255),
	RGB(85, 0, 255),
	RGB(73, 0, 220),
	RGB(61, 0, 185),
	RGB(49, 0, 150),
	RGB(37, 0, 115),
	RGB(25, 0, 80),
	RGB(212, 212, 255),
	RGB(177, 177, 255),
	RGB(142, 142, 255),
	RGB(107, 107, 255),
	RGB(72, 72, 255),
	RGB(37, 37, 255),
	RGB(0, 0, 255),
	RGB(0, 0, 220),
	RGB(0, 0, 185),
	RGB(0, 0, 150),
	RGB(0, 0, 115),
	RGB(0, 0, 80),
	RGB(212, 227, 255),
	RGB(177, 199, 255),
	RGB(142, 171, 255),
	RGB(107, 143, 255),
	RGB(72, 115, 255),
	RGB(37, 87, 255),
	RGB(0, 85, 255),
	RGB(0, 73, 220),
	RGB(0, 61, 185),
	RGB(0, 49, 150),
	RGB(0, 37, 115),
	RGB(0, 25, 80),
	RGB(212, 240, 255),
	RGB(177, 226, 255),
	RGB(142, 212, 255),
	RGB(107, 198, 255),
	RGB(72, 184, 255),
	RGB(37, 170, 255),
	RGB(0, 170, 255),
	RGB(0, 146, 220),
	RGB(0, 122, 185),
	RGB(0, 98, 150),
	RGB(0, 74, 115),
	RGB(0, 50, 80),
	RGB(212, 255, 255),
	RGB(177, 255, 255),
	RGB(142, 255, 255),
	RGB(107, 255, 255),
	RGB(72, 255, 255),
	RGB(37, 255, 255),
	RGB(0, 255, 255),
	RGB(0, 220, 220),
	RGB(0, 185, 185),
	RGB(0, 150, 150),
	RGB(0, 115, 115),
	RGB(0, 80, 80),
	RGB(212, 255, 240),
	RGB(177, 255, 226),
	RGB(142, 255, 212),
	RGB(107, 255, 198),
	RGB(72, 255, 184),
	RGB(37, 255, 170),
	RGB(0, 255, 170),
	RGB(0, 220, 146),
	RGB(0, 185, 122),
	RGB(0, 150, 98),
	RGB(0, 115, 74),
	RGB(0, 80, 50),
	RGB(212, 255, 227),
	RGB(177, 255, 199),
	RGB(142, 255, 171),
	RGB(107, 255, 143),
	RGB(72, 255, 115),
	RGB(37, 255, 87),
	RGB(0, 255, 85),
	RGB(0, 220, 73),
	RGB(0, 185, 61),
	RGB(0, 150, 49),
	RGB(0, 115, 37),
	RGB(0, 80, 25),
	RGB(212, 255, 212),
	RGB(177, 255, 177),
	RGB(142, 255, 142),
	RGB(107, 255, 107),
	RGB(72, 255, 72),
	RGB(37, 255, 37),
	RGB(0, 255, 0),
	RGB(0, 220, 0),
	RGB(0, 185, 0),
	RGB(0, 150, 0),
	RGB(0, 115, 0),
	RGB(0, 80, 0),
	RGB(227, 255, 212),
	RGB(199, 255, 177),
	RGB(171, 255, 142),
	RGB(143, 255, 107),
	RGB(115, 255, 72),
	RGB(87, 255, 37),
	RGB(85, 255, 0),
	RGB(73, 220, 0),
	RGB(61, 185, 0),
	RGB(49, 150, 0),
	RGB(37, 115, 0),
	RGB(25, 80, 0),
	RGB(240, 255, 212),
	RGB(226, 255, 177),
	RGB(212, 255, 142),
	RGB(198, 255, 107),
	RGB(184, 255, 72),
	RGB(170, 255, 37),
	RGB(170, 255, 0),
	RGB(146, 220, 0),
	RGB(122, 185, 0),
	RGB(98, 150, 0),
	RGB(74, 115, 0),
	RGB(50, 80, 0),
	RGB(255, 255, 212),
	RGB(255, 255, 177),
	RGB(255, 255, 142),
	RGB(255, 255, 107),
	RGB(255, 255, 72),
	RGB(255, 255, 37),
	RGB(255, 255, 0),
	RGB(220, 220, 0),
	RGB(185, 185, 0),
	RGB(150, 150, 0),
	RGB(115, 115, 0),
	RGB(80, 80, 0),
	RGB(242, 242, 242),
	RGB(230, 230, 230),
	RGB(218, 218, 218),
	RGB(206, 206, 206),
	RGB(194, 194, 194),
	RGB(182, 182, 182),
	RGB(170, 170, 170),
	RGB(158, 158, 158),
	RGB(146, 146, 146),
	RGB(134, 134, 134),
	RGB(122, 122, 122),
	RGB(110, 110, 110),
	RGB(98, 98, 98),
	RGB(86, 86, 86),
	RGB(74, 74, 74),
	RGB(62, 62, 62),
	RGB(50, 50, 50),
	RGB(38, 38, 38),
	RGB(26, 26, 26),
	RGB(14, 14, 14),
	RGB(255, 251, 240),
	RGB(160, 160, 164),
	RGB(128, 128, 128),
	RGB(255, 0, 0),
	RGB(0, 255, 0),
	RGB(255, 255, 0),
	RGB(0, 0, 255),
	RGB(255, 0, 255),
	RGB(0, 255, 255),
	RGB(255, 255, 255)
};

/////////////////////////////////////////////////////////////////////////////
RGBQUAD Palette::Color(UINT index)
{
	RGBQUAD color;

	index %= Palette::NUM_COLORS;

	color.rgbBlue = GetBValue(m_palette[index]);
	color.rgbGreen = GetGValue(m_palette[index]);
	color.rgbRed = GetRValue(m_palette[index]);
	color.rgbReserved = 0;

	return color;
}
