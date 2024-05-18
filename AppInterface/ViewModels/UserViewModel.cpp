#include "pch.h"
#include "UserViewModel.h"
#include "UserViewModel.g.cpp"
#include "winrt/Windows.Networking.Connectivity.h"

using namespace winrt;
using namespace Windows::Networking::Connectivity;

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

      GetArpInterfaces();
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::UserModel> UserViewModel::Users()
    {
      return mUsers;
    }

    void UserViewModel::HandleReceivedListenerMessages(std::string aSender, std::string aMessage)
    {
      const auto& senderIp      = winrt::to_hstring(aSender);
      const auto& senderMessage = winrt::to_hstring(aMessage);

      // Do not handle our own broadcast messages.
      if (std::find(mArpInterfaces.begin(), mArpInterfaces.end(), senderIp) != mArpInterfaces.end())
        return;
    }

    void UserViewModel::GetArpInterfaces()
    {
      const auto& hostNames = Windows::Networking::Connectivity::NetworkInformation::GetHostNames();

      for (const auto& host : hostNames)
      {
        if (host.Type() == Windows::Networking::HostNameType::Ipv4)
          mArpInterfaces.push_back(host.CanonicalName());
      }
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
