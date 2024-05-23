#pragma once
#include "MessagesViewModel.g.h"
#include "Models/TextMessageModel.h"

namespace winrt::AppInterface::implementation
{
    struct MessagesViewModel : MessagesViewModelT<MessagesViewModel>
    {
        using MessagesObservableVector = winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::TextMessageModel>;

        MessagesViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::TextMessageModel> GetUserMessages(hstring const& aUserIp);

    private:

        Windows::Foundation::Collections::IObservableMap<winrt::hstring, MessagesObservableVector> mMessagesMap;

    };
}
namespace winrt::AppInterface::factory_implementation
{
    struct MessagesViewModel : MessagesViewModelT<MessagesViewModel, implementation::MessagesViewModel>
    {
    };
}
