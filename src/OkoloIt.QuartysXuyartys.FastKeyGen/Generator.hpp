#ifndef OKOLOIT_QUARTUS_XUYARTYS_KEYGEN_GENERATOR_H_
#define OKOLOIT_QUARTUS_XUYARTYS_KEYGEN_GENERATOR_H_

#include <string>
#include <array>

class Generator
{
public:
    std::wstring GenerateActivateCode(const std::wstring& rawInstallCode);

private:
    int ConvertRawTextToInt(const std::wstring& rawText);
    std::wstring ConvertHexToRawText(std::string hexCode);

private:
    const int m_targetSum = 15'604;
    const int m_divisor   = 7;
    const int m_keyLength = 16;
    const std::array<char, 16> m_keyChars{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
};

#endif OKOLOIT_QUARTUS_XUYARTYS_KEYGEN_GENERATOR_H_ // !OKOLOIT_QUARTUS_XUYARTYS_KEYGEN_GENERATOR_H_
