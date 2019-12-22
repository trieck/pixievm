#include "StdAfx.h"
#include "PxEmuApp.h"

PxEmuApp _Module;

/////////////////////////////////////////////////////////////////////////////
HRESULT PxEmuApp::Init(_ATL_OBJMAP_ENTRY* pObjMap, HINSTANCE hInstance, 
    const GUID* pLibID)
{
    const auto hr = CAppModule::Init(pObjMap, hInstance, pLibID);
    if (FAILED(hr)) {
        return hr;
    }

    m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (m_d3d == nullptr) {
        return E_FAIL;
    }

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
void PxEmuApp::Term()
{
    m_d3d.Release();

    CAppModule::Term();
}

/////////////////////////////////////////////////////////////////////////////
IDirect3D9Ptr PxEmuApp::direct3d() const
{
    return m_d3d;
}
