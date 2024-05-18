#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::AppInterface::implementation
{
    MainPage::MainPage()
    {
      InitializeComponent();

      mUserViewModel = winrt::make<AppInterface::implementation::UserViewModel>();
    }

    winrt::AppInterface::UserViewModel MainPage::UserViewModel()
    {
      return mUserViewModel;
    }
}
