#pragma once

#include "StdAfx.h"

class PxEmuApp : public CAppModule
{
public:
    HRESULT Init(_ATL_OBJMAP_ENTRY* pObjMap, HINSTANCE hInstance, const GUID* pLibID = nullptr);
    void Term();
    IDirect3D9Ptr direct3d() const;

private:
    IDirect3D9Ptr m_d3d;
};
