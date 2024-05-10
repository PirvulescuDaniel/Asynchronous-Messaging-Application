#pragma once
#include "BooleanToVisibilityConvertor.g.h"
#include "winrt/Windows.UI.Xaml.h"

using namespace winrt;
using namespace winrt::Windows::UI::Xaml;

namespace winrt::AppInterface::implementation
{
    struct BooleanToVisibilityConvertor : BooleanToVisibilityConvertorT<BooleanToVisibilityConvertor>
    {
        BooleanToVisibilityConvertor() = default;

        winrt::Windows::Foundation::IInspectable Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
        winrt::Windows::Foundation::IInspectable ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
    };
}
namespace winrt::AppInterface::factory_implementation
{
    struct BooleanToVisibilityConvertor : BooleanToVisibilityConvertorT<BooleanToVisibilityConvertor, implementation::BooleanToVisibilityConvertor>
    {
    };
}
