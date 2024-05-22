#pragma once

#include "MainPage.g.h"
#include "Models/UserModel.h"
#include "Models/TextMessageModel.h"
#include "Utility/BooleanToVisibilityConvertor.h"
#include "ViewModels/UserViewModel.h"

namespace winrt::AppInterface::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        winrt::AppInterface::UserViewModel UserViewModel();

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
