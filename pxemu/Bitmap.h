#pragma once

/////////////////////////////////////////////////////////////////////////////
class Bitmap
{
    // Construction / Destruction
public:
    Bitmap();
    ~Bitmap() = default;

    // Interface
    void Render(CDC& dc, const CRect& rc) const;
    void SetPixel(uint16_t x, uint16_t y, uint8_t color) const;

    // Implementation
private:
    void CreateBitmap();
    CBitmap m_bm;
    CDC m_dc;
    LPBYTE m_pBits;
    std::unique_ptr<BITMAPINFO> m_bmi;
};
