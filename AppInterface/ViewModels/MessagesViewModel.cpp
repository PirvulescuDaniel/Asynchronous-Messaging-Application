#include "pch.h"
#include "MessagesViewModel.h"
#include "MessagesViewModel.g.cpp"

namespace winrt::AppInterface::implementation
{
    MessagesViewModel::MessagesViewModel()
    {
      mMessagesMap = winrt::single_threaded_observable_map<winrt::hstring, MessagesObservableVector>();
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::TextMessageModel> MessagesViewModel::GetUserMessages(hstring const& aUserIp)
    {
      try
      {
        return mMessagesMap.Lookup(aUserIp);
      }
      catch (const winrt::hresult_out_of_bounds& aException)
      {
        // If there is no conversation, we create one.

        auto emptyConversation = winrt::single_threaded_observable_vector<AppInterface::TextMessageModel>();
        mMessagesMap.Insert(aUserIp, emptyConversation);
      }

      return mMessagesMap.Lookup(aUserIp);
    }
}
