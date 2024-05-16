#pragma once
#include "UserViewModel.g.h"
#include "Models/UserModel.h"
#include "IPC/DiscoveryManager.h"

namespace winrt::AppInterface::implementation
{
    struct UserViewModel : UserViewModelT<UserViewModel>
    {
        UserViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::UserModel> Users();

    private:

        void HandleReceivedListenerMessages(std::string aSender, std::string aMessage);

        void OnSuspending(Windows::Foundation::IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&);

        Windows::Foundation::Collections::IObservableVector<AppInterface::UserModel> mUsers;

        std::unique_ptr<DiscoveryManager> mDiscoveryManagerPtr;
    };
}
