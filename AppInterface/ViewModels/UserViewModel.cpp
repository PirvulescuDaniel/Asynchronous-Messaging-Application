#include "pch.h"
#include "UserViewModel.h"
#include "UserViewModel.g.cpp"

namespace winrt::AppInterface::implementation
{
    UserViewModel::UserViewModel()
    {
      mUsers = winrt::single_threaded_observable_vector<AppInterface::UserModel>();
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::UserModel> UserViewModel::Users()
    {
      return mUsers;
    }
}
