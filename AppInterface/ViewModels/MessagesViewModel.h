#pragma once
#include "MessagesViewModel.g.h"
#include "Models/TextMessageModel.h"
#include "winrt/Windows.UI.Xaml.Media.h"
#include "IPC/IClient.h"
#include "IPC/TCPClient.h"
#include "IPC/IServer.h"
#include "IPC/TCPServer.h"

namespace winrt::AppInterface::implementation
{
    struct MessagesViewModel : MessagesViewModelT<MessagesViewModel>
    {
        using MessagesObservableVector = winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::TextMessageModel>;
        using ClientPtr                = std::unique_ptr<IClient>;
        using ServerPtr                = std::unique_ptr<IServer>;

        MessagesViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::TextMessageModel> GetUserMessages(hstring const& aUserIp);

        void AddMessageToConversation(hstring const& aUserIp, hstring const& aMessage, bool aReceived);

    private:

        void OnSuspending(Windows::Foundation::IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&);
        
        Windows::Foundation::Collections::IObservableMap<winrt::hstring, MessagesObservableVector> mMessagesMap;

        ClientPtr mClientPtr;
        ServerPtr mServerPtr;
    };
}
namespace winrt::AppInterface::factory_implementation
{
    struct MessagesViewModel : MessagesViewModelT<MessagesViewModel, implementation::MessagesViewModel>
    {
    };
}
