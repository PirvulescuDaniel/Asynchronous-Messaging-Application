#include "pch.h"
#include "UserViewModel.h"
#include "UserViewModel.g.cpp"

namespace
{
  const char * const   kBroadcastIp   = "255.255.255.255";
  const unsigned short kBroadcastPort = 3333;

  const std::chrono::seconds kBroadcastDelay(5);
}

namespace winrt::AppInterface::implementation
{
    UserViewModel::UserViewModel()
      :mDiscoveryManager(kBroadcastIp, kBroadcastPort)
    {
      mUsers = winrt::single_threaded_observable_vector<AppInterface::UserModel>();

      mDiscoveryManager.StartListening(std::bind(&UserViewModel::HandleReceivedListenerMessages, this, std::placeholders::_1, std::placeholders::_2));
      mDiscoveryManager.StartRecurrentBroadcasting(kBroadcastDelay);
    }

    UserViewModel::~UserViewModel()
    {
      mDiscoveryManager.StopListening();
      mDiscoveryManager.StopRecurrentBroadcasting();
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::UserModel> UserViewModel::Users()
    {
      return mUsers;
    }

    void UserViewModel::HandleReceivedListenerMessages(std::string aSender, std::string aMessage)
    {
      aSender;
      aMessage;


    }
}
