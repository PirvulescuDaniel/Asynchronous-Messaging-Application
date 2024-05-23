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

    void MainPage::OnSendMessage(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
      // TO BE MODIFIED

      auto message = winrt::make<AppInterface::implementation::TextMessageModel>();

      message.Message(L"Sa moara mata fraere.");
      message.Timestamp(L"14:40 PM");
      message.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Right);

      mCurrentSelectedUserMessages.Append(std::move(message));
    }
}