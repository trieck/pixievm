#pragma once

/////////////////////////////////////////////////////////////////////////////
class Bitmap
{
    // Construction / Destruction
public:
    Bitmap();
    ~Bitmap() = default;

    // Interface
    void render(CDC& dc, const CRect& rc) const;
    LPBYTE bits() const;
    LONG pitch() const;

    // Implementation
private:
    void create();
    CBitmap m_bm;
    CDC m_dc;
    LPBYTE m_pBits;
    std::unique_ptr<BITMAPINFO> m_bmi;
};
