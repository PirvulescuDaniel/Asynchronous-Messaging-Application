#include "pch.h"
#include "BooleanToVisibilityConvertor.h"
#include "BooleanToVisibilityConvertor.g.cpp"

namespace winrt::AppInterface::implementation
{
    winrt::Windows::Foundation::IInspectable BooleanToVisibilityConvertor::Convert(
      winrt::Windows::Foundation::IInspectable const& value,
      winrt::Windows::UI::Xaml::Interop::TypeName const& /*targetType*/,
      winrt::Windows::Foundation::IInspectable const& /*parameter*/,
      hstring const& /*language*/)
    {
      return winrt::unbox_value_or<bool>(value,false) ? winrt::box_value(Visibility::Visible) : winrt::box_value(Visibility::Collapsed);
    }

    winrt::Windows::Foundation::IInspectable BooleanToVisibilityConvertor::ConvertBack(
      winrt::Windows::Foundation::IInspectable const& /*value*/,
      winrt::Windows::UI::Xaml::Interop::TypeName const& /*targetType*/,
      winrt::Windows::Foundation::IInspectable const& /*parameter*/,
      hstring const& /*language*/)
    {
        // NO NEEDS TO IMPLEMENT THIS.
        throw hresult_not_implemented();
    }
}
