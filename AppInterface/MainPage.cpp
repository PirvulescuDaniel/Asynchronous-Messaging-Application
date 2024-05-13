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

    void MainPage::OnAddNewUser(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
      auto user = winrt::make<AppInterface::implementation::UserModel>();

      user.Username(L"Daniel Stefan");
      user.IsOnline(true);

      mUserViewModel.Users().Append(user);
    }
}
