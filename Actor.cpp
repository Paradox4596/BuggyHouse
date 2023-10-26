#include "Actor.h"

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename) :
    mpFramework(pFramework),
    mspBitmap(),
    mX(), mY(), mOpacity(1.0f)
{
    LoadWICImage(filename);
}

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename, float x, float y, float opacity) :
    Actor(pFramework, filename)
{
    mX = x;
    mY = y;
    mOpacity = opacity;
}

Actor::~Actor()
{
    mspBitmap.Reset();
}

HRESULT Actor::LoadWICImage(LPCWSTR filename)
{
    
}

void Actor::Draw(float x, float y, float opacity)
{
    auto pRT = mpFramework->GetRenderTarget();
    if (pRT == nullptr)
    {
        return;
    }
    auto size{ mspBitmap->GetPixelSize() };
    D2D1_RECT_F rect{ x,y,
        static_cast<float>(x + size.width),
        static_cast<float>(y + size.height) };

    pRT->DrawBitmap(mspBitmap.Get(), rect, opacity);
}

void Actor::Draw()
{
    Draw(mX, mY, mOpacity);
}