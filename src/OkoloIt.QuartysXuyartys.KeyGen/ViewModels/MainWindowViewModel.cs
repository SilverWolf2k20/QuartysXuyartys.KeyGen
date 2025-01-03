using System;

using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;

using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

using OkoloIt.QuartysXuyartys.KeyGen.Models;

namespace OkoloIt.QuartysXuyartys.KeyGen.ViewModels;

public partial class MainWindowViewModel : ViewModelBase
{
    private readonly KeyGenerator _keyGenerator = new();

    [ObservableProperty]
    private string _installationCode = string.Empty;

    [ObservableProperty]
    private string _activationCode = string.Empty;

    [RelayCommand]
    private void OnGenerate()
    {
        try {
            ActivationCode = _keyGenerator.Generate(InstallationCode);
        }
        catch (Exception) {
            ActivationCode = "Ошибка генерации!";
        }
    }

    [RelayCommand]
    private void OnExit()
    {
        if (Application.Current?.ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktopApp)
            desktopApp.Shutdown();
    }
}
