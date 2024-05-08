#include "pch.h"
#include "UserModel.h"
#include "UserModel.g.cpp"

namespace winrt::AppInterface::implementation
{
    UserModel::UserModel()
    {
      DefaultStyleKey(winrt::box_value(L"AppInterface.UserModel"));
    }

    winrt::Windows::UI::Xaml::DependencyProperty UserModel::UsernameProperty()
    {
      return mUsernameProperty;
    }

    winrt::Windows::UI::Xaml::DependencyProperty UserModel::AddressProperty()
    {
      return mAddressProperty;
    }

    winrt::Windows::UI::Xaml::DependencyProperty UserModel::IsOnlineProperty()
    {
      return mIsOnlineProperty;
    }

    winrt::Windows::UI::Xaml::DependencyProperty UserModel::ImageProfilePathProperty()
    {
      return mImageProfilePathProperty;
    }

    hstring UserModel::Username()
    {
      return winrt::unbox_value<winrt::hstring>(GetValue(mUsernameProperty));
    }

    void UserModel::Username(hstring const& value)
    {
      SetValue(mUsernameProperty, winrt::box_value(value));
    }

    hstring UserModel::Address()
    {
      return winrt::unbox_value<winrt::hstring>(GetValue(mAddressProperty));
    }

    void UserModel::Address(hstring const& value)
    {
      SetValue(mAddressProperty, winrt::box_value(value));
    }

    bool UserModel::IsOnline()
    {
      return winrt::unbox_value<bool>(GetValue(mIsOnlineProperty));
    }

    void UserModel::IsOnline(bool value)
    {
      SetValue(mIsOnlineProperty, winrt::box_value(value));
    }

    hstring UserModel::ImageProfilePath()
    {
      return winrt::unbox_value<winrt::hstring>(GetValue(mImageProfilePathProperty));
    }

    void UserModel::ImageProfilePath(hstring const& value)
    {
      SetValue(mImageProfilePathProperty, winrt::box_value(value));
    }
}
