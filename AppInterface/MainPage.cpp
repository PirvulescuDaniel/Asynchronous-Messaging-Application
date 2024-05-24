#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::AppInterface::implementation
{
    MainPage::MainPage()
    {
      InitializeComponent();

      mUserViewModel = winrt::make<AppInterface::implementation::UserViewModel>();

      mMessagesViewModel = winrt::make<AppInterface::implementation::MessagesViewModel>();

      mCurrentSelectedUserMessages = winrt::single_threaded_observable_vector<AppInterface::TextMessageModel>();
    }

    winrt::AppInterface::UserViewModel MainPage::UserViewModel()
    {
      return mUserViewModel;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::TextMessageModel> MainPage::CurrentSelectedUserMessages()
    {
      return mCurrentSelectedUserMessages;
    }

    void MainPage::CurrentSelectedUserMessages(winrt::Windows::Foundation::Collections::IObservableVector<winrt::AppInterface::TextMessageModel> const& value)
    {
      if (mCurrentSelectedUserMessages != value)
      {
        mCurrentSelectedUserMessages = value;
        mPropertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"CurrentSelectedUserMessages" });
      }
    }

    winrt::event_token MainPage::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
      return mPropertyChanged.add(handler);
    }

    void MainPage::PropertyChanged(winrt::event_token const& token) noexcept
    {
      mPropertyChanged.remove(token);
    }

    void MainPage::OnSendMessage(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
      const auto& selectedUser = UsersListBox().SelectedItem().try_as<AppInterface::UserModel>();
      const auto& textMessage = TextPane().Text();

      if (!selectedUser || textMessage.empty())
        return;

      mMessagesViewModel.AddMessageToConversation(selectedUser.Address(), textMessage, false);
      TextPane().Text(L"");
    }

    void MainPage::OnUserSelectionChanged(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const&)
    {
      auto listItem = UsersListBox().SelectedItem();

      if (const auto user = listItem.try_as<AppInterface::UserModel>())
        CurrentSelectedUserMessages(mMessagesViewModel.GetUserMessages(user.Address()));
    }
}

