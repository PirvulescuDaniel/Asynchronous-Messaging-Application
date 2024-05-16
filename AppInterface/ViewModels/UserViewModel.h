#pragma once
#include "UserViewModel.g.h"
#include "Models/UserModel.h"
#include "IPC/DiscoveryManager.h"

namespace winrt::AppInterface::implementation
{
    struct UserViewModel : UserViewModelT<UserViewModel>
    {
        UserViewModel();

        ~UserViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::UserModel> Users();

    private:

        void HandleReceivedListenerMessages(std::string aSender, std::string aMessage);

        Windows::Foundation::Collections::IObservableVector<AppInterface::UserModel> mUsers;

        DiscoveryManager mDiscoveryManager;
    };
}
