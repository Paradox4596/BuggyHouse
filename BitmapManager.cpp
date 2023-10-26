#include "BitmapManager.h"

#pragma comment(lib, "WindwosCodecs.lib")

using namespace std;
using namespace Microsoft::WRL;

HRESULT BitmapManager::LoadWICBitmap(wstring filename, ID2D1Bitmap** ppBitmap)
{
    Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
    HRESULT hr;

    auto pWICFactory = mspWICFactory.Get();
    if (mpFramework == nullptr)
    {
        return E_FAIL;
    }

    auto pWICFactory = mpFramework->GetWICFactory();
    if (pWICFactory == nullptr)
    {
        return E_FAIL;
    }

    hr = pWICFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ,
        WICDecodeMetadataCacheOnLoad, decoder.GetAddressOf());
    ThrowIfFailed(hr);

    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
    ThrowIfFailed(decoder->GetFrame(0, frame.GetAddressOf()));

    Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
    ThrowIfFailed(pWICFactory->CreateFormatConverter(converter.GetAddressOf()));

    hr = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeCustom);

    ThrowIfFailed(hr);

    auto pRT = mpFramework->GetRenderTarget();
    if (pRT == nullptr)
    {
        return E_FAIL;
    }

    hr = pRT->CreateBitmapFromWicBitmap(converter.Get(), mspBitmap.GetAddressOf());
    ThrowIfFailed(hr);

    return S_OK;
}

HRESULT BitmapManager::Initialize(ID2D1HwndRenderTarget* pRT)
{
	if (!pRT)
	{
		return E_FAIL;
	}
	
	mpRenderTarget = pRT;

	HRESULT hr = ::CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(mspWICFactory.GetAddressOf()));
	ThrowIfFailed(hr, "WICFactory Creation failed");

	return hr;
}

void BitmapManager::Release()
{
	mBitmapResources
}

ID2D1Bitmap* BitmapManager::LoadBitmap(std::wstring filename)
{
	// 처음 불렀냐?
    // 이미 로딩했냐?
    if (!mspWICFactory)
    {
        ThrowIfFailed(E_FAIL, "WICFactory must not null");
        return nullptr;
    }



    return nullptr;
}
