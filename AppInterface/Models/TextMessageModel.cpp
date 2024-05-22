#include "pch.h"
#include "TextMessageModel.h"
#include "TextMessageModel.g.cpp"

namespace winrt::AppInterface::implementation
{
    // Register the control properties.
    Windows::UI::Xaml::DependencyProperty TextMessageModel::mMessageProperty = Windows::UI::Xaml::DependencyProperty::Register(
      L"Message",
      winrt::xaml_typename<winrt::hstring>(),
      winrt::xaml_typename<AppInterface::TextMessageModel>(),
      Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(L"Message") }
    );

    Windows::UI::Xaml::DependencyProperty TextMessageModel::mTimestampProperty = Windows::UI::Xaml::DependencyProperty::Register(
      L"Timestamp",
      winrt::xaml_typename<winrt::hstring>(),
      winrt::xaml_typename<AppInterface::TextMessageModel>(),
      Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(L"Timestamp") }
    );

    TextMessageModel::TextMessageModel()
    {
      DefaultStyleKey(winrt::box_value(L"AppInterface.TextMessageModel"));
    }

    winrt::Windows::UI::Xaml::DependencyProperty TextMessageModel::MessageProperty()
    {
      return mMessageProperty;
    }

    winrt::Windows::UI::Xaml::DependencyProperty TextMessageModel::TimestampProperty()
    {
      return mTimestampProperty;
    }

    hstring TextMessageModel::Message()
    {
      return winrt::unbox_value<winrt::hstring>(GetValue(mMessageProperty));
    }

    void TextMessageModel::Message(hstring const& value)
    {
      SetValue(mMessageProperty, winrt::box_value(value));
    }

    hstring TextMessageModel::Timestamp()
    {
      return winrt::unbox_value<winrt::hstring>(GetValue(mTimestampProperty));
    }

    void TextMessageModel::Timestamp(hstring const& value)
    {
      SetValue(mTimestampProperty, winrt::box_value(value));
    }
}
