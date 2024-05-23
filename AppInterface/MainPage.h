#pragma once

#include "MainPage.g.h"
#include "Models/UserModel.h"
#include "Models/TextMessageModel.h"
#include "Utility/BooleanToVisibilityConvertor.h"
#include "ViewModels/UserViewModel.h"
#include "ViewModels/MessagesViewModel.h"

namespace winrt::AppInterface::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        winrt::AppInterface::UserViewModel UserViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::TextMessageModel> CurrentSelectedUserMessages();

        void OnSendMessage(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        
        AppInterface::UserViewModel mUserViewModel{ nullptr };

        AppInterface::MessagesViewModel mMessagesViewModel{ nullptr };

        Windows::Foundation::Collections::IObservableVector<AppInterface::TextMessageModel> mCurrentSelectedUserMessages{ nullptr };
    };
}
namespace winrt::AppInterface::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
