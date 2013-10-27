// pxemuView.h : interface of the CPxemuView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CPxemuView : public CWindowImpl<CPxemuView>
{
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CPxemuView)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_DESTROY(OnDestroy)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(LPCREATESTRUCT cs) {
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);
		if (FAILED(hr))
			return -1;

		return 0;
	}

	void OnDestroy() {
		DiscardDevResources();
		m_factory.Release();
	}

	void OnPaint(CDCHandle /*hDC*/) {
		CPaintDC dc(*this);
		Render(dc);
	}

private:
	void Render(CPaintDC& dc) 
	{
		HRESULT hr;
		if (m_target == NULL) {
			hr = CreateDevResources();
			if (FAILED(hr))
				return;
		}

		hr = m_target->BindDC(dc, &dc.m_ps.rcPaint);

		m_target->BeginDraw();
		m_target->SetTransform(D2D1::Matrix3x2F::Identity());
		m_target->Clear(D2D1::ColorF(D2D1::ColorF::Black));

		// TODO: paint 

		if (D2DERR_RECREATE_TARGET == m_target->EndDraw()) {
			DiscardDevResources();
		}
	}

	HRESULT CreateDevResources() 
	{
		DiscardDevResources();

		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, 
				D2D1_ALPHA_MODE_IGNORE), 
			0,
			0,
			D2D1_RENDER_TARGET_USAGE_NONE,
			D2D1_FEATURE_LEVEL_DEFAULT);
			
		HRESULT hr = m_factory->CreateDCRenderTarget(&props, &m_target);
		if (FAILED(hr))
			return hr;

		// TODO: setup

		return hr;
	}

	void DiscardDevResources() 
	{
		m_target.Release();
	}

	CComPtr<ID2D1DCRenderTarget> m_target;
	CComPtr<ID2D1Factory> m_factory;
};