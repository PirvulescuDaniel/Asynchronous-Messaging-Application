#include "pch.h"
#include "UserModel.h"
#include "UserModel.g.cpp"

namespace winrt::AppInterface::implementation
{
    // Register the control properties.
    Windows::UI::Xaml::DependencyProperty UserModel::mUsernameProperty = Windows::UI::Xaml::DependencyProperty::Register(
        L"Username",
        winrt::xaml_typename<winrt::hstring>(),
        winrt::xaml_typename<AppInterface::UserModel>(),
        Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(L"Username")}
    );

    Windows::UI::Xaml::DependencyProperty UserModel::mAddressProperty = Windows::UI::Xaml::DependencyProperty::Register(
      L"Address",
      winrt::xaml_typename<winrt::hstring>(),
      winrt::xaml_typename<AppInterface::UserModel>(),
      Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(L"0.0.0.0") }
    );

    Windows::UI::Xaml::DependencyProperty UserModel::mIsOnlineProperty = Windows::UI::Xaml::DependencyProperty::Register(
      L"IsOnline",
      winrt::xaml_typename<bool>(),
      winrt::xaml_typename<AppInterface::UserModel>(),
      Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(false) }
    );

    Windows::UI::Xaml::DependencyProperty UserModel::mImageProfilePathProperty = Windows::UI::Xaml::DependencyProperty::Register(
      L"ImageProfilePath",
      winrt::xaml_typename<winrt::hstring>(),
      winrt::xaml_typename<AppInterface::UserModel>(),
      Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(L"Assets/default_avatar.jpg") }
    );

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
