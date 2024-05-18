#include "pch.h"
#include "UserViewModel.h"
#include "UserViewModel.g.cpp"
#include "winrt/Windows.Networking.Connectivity.h"
#include "winrt/Windows.ApplicationModel.Core.h"
#include "winrt/Windows.UI.Core.h"

using namespace winrt;
using namespace Windows::Networking::Connectivity;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;

namespace
{
  const char * const   kBroadcastIp   = "255.255.255.255";
  const unsigned short kBroadcastPort = 3333;

  const char * const kHelloMessage = "Hello";
  const char * const kByeMessage   = "Bye";

  const std::chrono::seconds kBroadcastDelay(2);
}

namespace winrt::AppInterface::implementation
{
    UserViewModel::UserViewModel()
      :mDiscoveryManagerPtr(std::make_unique<DiscoveryManager>(kBroadcastIp, kBroadcastPort))
    {
      mUsers = winrt::single_threaded_observable_vector<AppInterface::UserModel>();

      Windows::UI::Xaml::Application::Current().Suspending({ this,&UserViewModel::OnSuspending });

      GetArpInterfaces();

      mDiscoveryManagerPtr->StartListening(std::bind(&UserViewModel::HandleReceivedListenerMessages, this, std::placeholders::_1, std::placeholders::_2));
      mDiscoveryManagerPtr->StartRecurrentBroadcasting(kBroadcastDelay);
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::UserModel> UserViewModel::Users()
    {
      return mUsers;
    }

    void UserViewModel::HandleReceivedListenerMessages(std::string aSender, std::string aMessage)
    {
      const auto& senderIp = winrt::to_hstring(aSender);

      // Do not handle our own broadcast messages.
      if (std::find(mArpInterfaces.begin(), mArpInterfaces.end(), senderIp) != mArpInterfaces.end())
        return;

      auto dispatcher = CoreApplication::MainView().CoreWindow().Dispatcher();

      if (aMessage.find(kHelloMessage) != std::string::npos)
        dispatcher.RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,std::bind(&UserViewModel::OnOnlineUser,this,senderIp));
      else if (aMessage.find(kByeMessage) != std::string::npos)
        dispatcher.RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, std::bind(&UserViewModel::OnOfflineUser, this, senderIp));
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

    void UserViewModel::OnOnlineUser(const winrt::hstring& aUserIp)
    {
      auto & found = std::find_if(mUsers.begin(), mUsers.end(),
        [&aUserIp](auto& aUser)
        {
          return (aUser.Address() == aUserIp);
        }
      );

      if (found == mUsers.end())
      {
            auto newUser = winrt::make<AppInterface::implementation::UserModel>();

            newUser.Username(aUserIp);
            newUser.Address(aUserIp);
            newUser.IsOnline(true);

            mUsers.Append(std::move(newUser));
      }
      else
        (*found).IsOnline(true);
    }

    void UserViewModel::OnOfflineUser(const winrt::hstring& aUserIp)
    {
      auto& found = std::find_if(mUsers.begin(), mUsers.end(),
        [&aUserIp](auto& aUser)
        {
          return (aUser.Address() == aUserIp);
        }
      );

      if(found != mUsers.end())
        (*found).IsOnline(false);
    }
}
