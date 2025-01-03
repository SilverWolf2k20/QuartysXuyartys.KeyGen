#include "Generator.hpp"

#include <format>
#include <random>
#include <sstream>

std::wstring Generator::GenerateActivateCode(const std::wstring& rawInstallCode)
{
    int installCode  = ConvertRawTextToInt(rawInstallCode);
    int activateCode = (m_targetSum - (installCode / m_divisor)) * m_divisor;

    std::string rawActivateHexCode = std::format("{:x}", activateCode);
    std::stringstream stream;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib{ 0, static_cast<int>(m_keyChars.size() - 1)};

    for (auto i = 0; i < m_keyLength; ++i) {
        // Установка пустого символа для разделения по группам по 4 символа.
        if (i % 4 == 0 && i > 0)
            stream << ' ';

        // Установка символа ключа на первую позицию группы и символа заполнения на остальные.
        if (i % 4 == 0) {
            int index = i / 4;
            stream << rawActivateHexCode[index];
        }
        else {
            int index = distrib(gen);
            char randomChar = m_keyChars[index];
            stream << randomChar;
        }
    }

    return ConvertHexToRawText(stream.str());
}

int Generator::ConvertRawTextToInt(const std::wstring& rawText)
{
    std::string hexCode;

    std::transform(rawText.begin(), rawText.end(), std::back_inserter(hexCode), [](wchar_t c) {
        return static_cast<char>(c);
    });

    return std::stoi(hexCode, nullptr, 16);
}

std::wstring Generator::ConvertHexToRawText(std::string hexCode)
{
    std::wstring rawText;

    std::transform(hexCode.begin(), hexCode.end(), std::back_inserter(rawText), [](char c) {
        return static_cast<wchar_t>(std::toupper(c));
    });

    return rawText;
}
