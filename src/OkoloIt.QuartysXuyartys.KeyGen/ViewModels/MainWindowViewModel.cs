using CommunityToolkit.Mvvm.ComponentModel;

using OkoloIt.QuartysXuyartys.KeyGen.Models;

namespace OkoloIt.QuartysXuyartys.KeyGen.ViewModels;

public partial class MainWindowViewModel : ViewModelBase
{
    public MainWindowViewModel()
    {
        KeyGenerator keyGenerator = new();
        string key = keyGenerator.Generate("C787");

    }

    [ObservableProperty]
    private string _message = "Welcome to QuartysXuyartys KeyGen!";
}
