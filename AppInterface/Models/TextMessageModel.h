#pragma once
#include "TextMessageModel.g.h"

namespace winrt::AppInterface::implementation
{
    struct TextMessageModel : TextMessageModelT<TextMessageModel>
    {
      TextMessageModel();

      static winrt::Windows::UI::Xaml::DependencyProperty MessageProperty();
      static winrt::Windows::UI::Xaml::DependencyProperty TimestampProperty();

      hstring Message();
      void Message(hstring const& value);

      hstring Timestamp();
      void Timestamp(hstring const& value);

    private:

      static Windows::UI::Xaml::DependencyProperty mMessageProperty;
      static Windows::UI::Xaml::DependencyProperty mTimestampProperty;
    };
}
namespace winrt::AppInterface::factory_implementation
{
    struct TextMessageModel : TextMessageModelT<TextMessageModel, implementation::TextMessageModel>
    {
    };
}
