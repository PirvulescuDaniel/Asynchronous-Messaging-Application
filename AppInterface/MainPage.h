#pragma once

#include "MainPage.g.h"
#include "Models/UserModel.h"
#include "Utility/BooleanToVisibilityConvertor.h"
#include "ViewModels/UserViewModel.h"

namespace winrt::AppInterface::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        winrt::AppInterface::UserViewModel UserViewModel();

        void OnAddNewUser(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        
        AppInterface::UserViewModel mUserViewModel{ nullptr };
    };
}
namespace winrt::AppInterface::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
