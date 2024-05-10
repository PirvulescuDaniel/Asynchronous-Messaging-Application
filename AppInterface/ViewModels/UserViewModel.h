#pragma once
#include "UserViewModel.g.h"
#include "Models/UserModel.h"

namespace winrt::AppInterface::implementation
{
    struct UserViewModel : UserViewModelT<UserViewModel>
    {
        UserViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::UserModel> Users();

    private:

        Windows::Foundation::Collections::IObservableVector<AppInterface::UserModel> mUsers;
    };
}
