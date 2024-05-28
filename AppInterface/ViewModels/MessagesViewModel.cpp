#include "pch.h"
#include "MessagesViewModel.h"
#include "MessagesViewModel.g.cpp"
#include "IPC/IRequest.h"
#include "IPC/RequestText.h"

using namespace winrt;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;

namespace winrt::AppInterface::implementation
{
    namespace
    {
      auto kSendAlignment     = Windows::UI::Xaml::HorizontalAlignment::Right;
      auto kReceivedAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;

      constexpr unsigned short kPort = 3333;
    }

    MessagesViewModel::MessagesViewModel()
      :mClientPtr(std::make_unique<TCPClient>())
      ,mServerPtr(std::make_unique<TCPServer>())
    {
      mMessagesMap = winrt::single_threaded_observable_map<winrt::hstring, MessagesObservableVector>();

      Windows::UI::Xaml::Application::Current().Suspending({ this,&MessagesViewModel::OnSuspending });

      mServerPtr->Start(kPort, 2, std::bind(&MessagesViewModel::AddMessageToConversation, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::TextMessageModel> MessagesViewModel::GetUserMessages(hstring const& aUserIp)
    {
      try
      {
        return mMessagesMap.Lookup(aUserIp);
      }
      catch (const winrt::hresult_out_of_bounds&)
      {
        // If there is no conversation, we create one.

        auto emptyConversation = winrt::single_threaded_observable_vector<AppInterface::TextMessageModel>();
        mMessagesMap.Insert(aUserIp, emptyConversation);
      }

      return mMessagesMap.Lookup(aUserIp);
    }

    void MessagesViewModel::AddMessageToConversation(hstring const& aUserIp, hstring const& aMessage, bool aReceived)
    {
      CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal,
        [=]()
        {
          // Add the message to conversation
          auto conversation = GetUserMessages(aUserIp);

          auto message = winrt::make<AppInterface::implementation::TextMessageModel>();
          message.Message(aMessage);
          message.HorizontalAlignment(aReceived ? kReceivedAlignment : kSendAlignment);

          const auto& sendBgBrush = Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::DeepSkyBlue());
          const auto& receivedBgBrush = Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 154, 154, 154));

          message.Background(aReceived ? receivedBgBrush : sendBgBrush);

          auto currentTime = std::chrono::system_clock::now();
          auto currentTime_time_t = std::chrono::system_clock::to_time_t(currentTime);

          std::tm currentTime_tm;
          localtime_s(&currentTime_tm, &currentTime_time_t);

          std::wstringstream timeStream;
          timeStream << std::put_time(&currentTime_tm, L"%I:%M %p");

          message.Timestamp(timeStream.str());

          conversation.Append(std::move(message));
        }
      );

      if (!aReceived)
      {
        const std::string messageStr(aMessage.begin(), aMessage.end());
        const std::string userIpStr(aUserIp.begin(), aUserIp.end());

        std::shared_ptr<IRequest> request = std::make_shared<RequestText>(messageStr, 1);

        mClientPtr->SendRequest(request, userIpStr, kPort);
      }
    }

    void MessagesViewModel::OnSuspending(Windows::Foundation::IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&)
    {
      mClientPtr->Close();
      mClientPtr.reset(nullptr);

      mServerPtr->Stop();
      mServerPtr.reset(nullptr);
    }
}
