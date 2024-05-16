#include "pch.h"
#include "UserViewModel.h"
#include "UserViewModel.g.cpp"

namespace
{
  const char * const   kBroadcastIp   = "255.255.255.255";
  const unsigned short kBroadcastPort = 3333;

  const std::chrono::seconds kBroadcastDelay(2);
}

namespace winrt::AppInterface::implementation
{
    UserViewModel::UserViewModel()
      :mDiscoveryManagerPtr(std::make_unique<DiscoveryManager>(kBroadcastIp, kBroadcastPort))
    {
      mUsers = winrt::single_threaded_observable_vector<AppInterface::UserModel>();

      mDiscoveryManagerPtr->StartListening(std::bind(&UserViewModel::HandleReceivedListenerMessages, this, std::placeholders::_1, std::placeholders::_2));
      mDiscoveryManagerPtr->StartRecurrentBroadcasting(kBroadcastDelay);

      Windows::UI::Xaml::Application::Current().Suspending({ this,&UserViewModel::OnSuspending });
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

    void UserViewModel::OnSuspending(Windows::Foundation::IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&)
    {
      mDiscoveryManagerPtr->StopListening();
      mDiscoveryManagerPtr->StopRecurrentBroadcasting();

      /*
        We release manually because the destructor of UserViewModel will never be called,
        implicitly the destructor of DiscoveryManager will not be called and the "Bye" message will not be sent.
      */
      mDiscoveryManagerPtr.reset(nullptr);
    }
}
