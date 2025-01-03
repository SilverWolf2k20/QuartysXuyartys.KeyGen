using System;
using System.Globalization;
using System.Text;

namespace OkoloIt.QuartysXuyartys.KeyGen.Models;

internal class KeyGenerator
{
    private const int TargetSum = 15604;
    private const int Divisor   = 7;
    private const int KeyLength = 16;

    private readonly char[] KeyChars = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'];

    internal string Generate(string firstHexKey)
    {
        // Расчет значения второго ключа.
        int firstKey  = int.Parse(firstHexKey, NumberStyles.HexNumber);
        int secondKey = (TargetSum - (firstKey / Divisor)) * Divisor;
        string secondHexKey = secondKey.ToString("X");

        // Создание ключа.
        StringBuilder stringBuilder = new();
        for (var i = 0; i < KeyLength; ++i) {
            // Установка пустого символа для разделения по группам по 4 символа.
            if (i % 4 == 0 && i > 0)
                stringBuilder.Append(' ');

            // Установка символа ключа на первую позицию группы и символа заполнения на остальные.
            if (i % 4 == 0) {
                int index = i / 4;
                stringBuilder.Append(secondHexKey[index]);
            }
            else {
                int index = Random.Shared.Next(KeyChars.Length);
                char randomChar = KeyChars[index];
                stringBuilder.Append(randomChar);
            }
        }

        return stringBuilder.ToString();
    }
}
