#pragma once
#include "UserModel.g.h"

namespace winrt::AppInterface::implementation
{
    struct UserModel : UserModelT<UserModel>
    {
      UserModel();

      static winrt::Windows::UI::Xaml::DependencyProperty UsernameProperty();
      static winrt::Windows::UI::Xaml::DependencyProperty AddressProperty();
      static winrt::Windows::UI::Xaml::DependencyProperty IsOnlineProperty();
      static winrt::Windows::UI::Xaml::DependencyProperty ImageProfilePathProperty();

      hstring Username();
      void Username(hstring const& value);

      hstring Address();
      void Address(hstring const& value);

      bool IsOnline();
      void IsOnline(bool value);

      hstring ImageProfilePath();
      void ImageProfilePath(hstring const& value);

    private:

      static Windows::UI::Xaml::DependencyProperty mUsernameProperty;
      static Windows::UI::Xaml::DependencyProperty mAddressProperty;
      static Windows::UI::Xaml::DependencyProperty mIsOnlineProperty;
      static Windows::UI::Xaml::DependencyProperty mImageProfilePathProperty;
    };
}
namespace winrt::AppInterface::factory_implementation
{
    struct UserModel : UserModelT<UserModel, implementation::UserModel>
    {
    };
}
