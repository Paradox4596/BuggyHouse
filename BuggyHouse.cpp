#include "BuggyHouse.h"

HRESULT BuggyHouse::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;
    hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr, "Failed in D2DFramework::Initialize()");

    mspBackground = std::make_shared<Actor>(this, L"Images/back.png", 0.0f, 0.0f, 1.0f);

    for (int i = 0; i < 40; i++)
    {
        mBugList.push_back(std::make_shared<Actor>(this, L"Images/back.png", 0.0f, 0.0f, 1.0f));
    }

    return S_OK;
}

void BuggyHouse::Render()
{
}

void BuggyHouse::Release()
{

}
