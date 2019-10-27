#include "StdAfx.h"
#include "Palette.h"
#include "exception.h"

constexpr auto HEIGHT = (16 * 16);
constexpr auto WIDTH = (16 * 16);

void SavePalette()
{
    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;

    memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
    memset(&bmih, 0, sizeof(BITMAPINFOHEADER));

    bmfh.bfType = 0x4D42; // 'BM'
    bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
        sizeof(RGBQUAD) * Palette::NUM_COLORS;

    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biWidth = WIDTH;
    bmih.biHeight = -HEIGHT; // top-down
    bmih.biPlanes = 1;
    bmih.biBitCount = 8; // 256 colors
    bmih.biCompression = BI_RGB;
    bmih.biClrUsed = 256;

    FILE* fp;
    if ((fp = fopen("palette.bmp", "wb")) == nullptr){
        throw Exception("Cannot write file \"palette.bmp\".");
    }

    fwrite(&bmfh, 1, sizeof(BITMAPFILEHEADER), fp);
    fwrite(&bmih, 1, sizeof(BITMAPINFOHEADER), fp);

    // write color table
    RGBQUAD rgbColor;
    for (UINT i = 0; i < Palette::NUM_COLORS; ++i){
        rgbColor = Palette::Color(i);
        fwrite(&rgbColor, 1, sizeof(RGBQUAD), fp);
    }

    // write pixel data
    uint8_t color = 0, rowColor = 0;
    for (auto i = 0; i < HEIGHT; ++i){
        if (i > 0 && i % 16 == 0)
            rowColor = color + 1;

        color = rowColor;
        for (auto j = 0; j < WIDTH; ++j){
            if (j > 0 && j % 16 == 0)
                color++;

            fputc(color, fp);
        }
    }

    fclose(fp);
}

int main(int argc, char* argv[])
{
    try{
        SavePalette();
    } catch (const Exception& e){
        cerr << e.getDescription() << endl;
        return 1;
    }

    return 0;
}
