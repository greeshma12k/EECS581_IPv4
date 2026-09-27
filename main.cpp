#include <iostream>
#include <string>

using namespace std;

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool parseOctet(const string &str, size_t &pos, int &value)
{
    int digitCount = 0;
    int number = 0;

    if (pos >= str.length() || !isDigit(str[pos]))
    {
        return false;
    }

    // A leading zero is only allowed when the octet is exactly "0".
    if (str[pos] == '0')
    {
        pos++;

        if (pos < str.length() && isDigit(str[pos]))
        {
            return false;
        }

        value = 0;
        return true;
    }

    // Manually accumulate 1-3 digits.
    while (pos < str.length() && isDigit(str[pos]) && digitCount < 3)
    {
        number = number * 10 + (str[pos] - '0');
        pos++;
        digitCount++;
    }

    // More than three digits is invalid.
    if (pos < str.length() && isDigit(str[pos]))
    {
        return false;
    }

    // Octet must be between 0 and 255.
    if (number > 255)
    {
        return false;
    }

    value = number;
    return true;
}

bool parsePort(const string &str, size_t &pos, int &port)
{
    int number = 0;
    int digitCount = 0;

    if (pos >= str.length() || !isDigit(str[pos]))
    {
        return false;
    }

    // A leading zero is only allowed when the port is exactly "0".
    if (str[pos] == '0')
    {
        pos++;

        if (pos < str.length() && isDigit(str[pos]))
        {
            return false;
        }

        port = 0;
        return true;
    }

    // Manually accumulate 1-5 digits.
    while (pos < str.length() && isDigit(str[pos]) && digitCount < 5)
    {
        number = number * 10 + (str[pos] - '0');
        pos++;
        digitCount++;
    }

    // More than five digits is invalid.
    if (pos < str.length() && isDigit(str[pos]))
    {
        return false;
    }

    // Port must be between 0 and 65535.
    if (number > 65535)
    {
        return false;
    }

    port = number;
    return true;
}

bool extractIPv4(const std::string &str, unsigned long &outAddress, int &outPort)
{
    outAddress = 0;
    outPort = -1;

    for (size_t start = 0; start < str.length(); start++)
    {

        // A candidate must begin with a digit.
        if (!isDigit(str[start]))
        {
            continue;
        }

        // Do not start in the middle of a token.
        // Digits, periods, and colons are token characters.
        //
        // This prevents partial matches such as:
        // 1192.168.1.1
        // from incorrectly becoming 192.168.1.1.
        //
        // But a garbage character such as 'a' DOES allow a new
        // candidate to begin, which is required for:
        // 192a168.1.1.1
        if (start > 0)
        {
            char previous = str[start - 1];

            if (isDigit(previous) || previous == '.' || previous == ':')
            {
                continue;
            }
        }

        size_t pos = start;
        int octets[4];

        bool valid = true;

        // Parse exactly four octets.
        for (int i = 0; i < 4; i++)
        {
            if (!parseOctet(str, pos, octets[i]))
            {
                valid = false;
                break;
            }

            // The first three octets must be followed by a period.
            if (i < 3)
            {
                if (pos >= str.length() || str[pos] != '.')
                {
                    valid = false;
                    break;
                }

                pos++;
            }
        }

        if (!valid)
        {
            continue;
        }

        int port = -1;

        // Optional port.
        if (pos < str.length() && str[pos] == ':')
        {
            pos++;

            // If a colon is present, a valid port is required.
            if (!parsePort(str, pos, port))
            {
                continue;
            }

            // A second colon is invalid.
            if (pos < str.length() && str[pos] == ':')
            {
                continue;
            }
        }

        // A period immediately after the address is invalid.
        if (pos < str.length() && str[pos] == '.')
        {
            continue;
        }

        // Convert A.B.C.D into its 32-bit decimal value.
        unsigned long address =
            static_cast<unsigned long>(octets[0]) * 16777216UL +
            static_cast<unsigned long>(octets[1]) * 65536UL +
            static_cast<unsigned long>(octets[2]) * 256UL +
            static_cast<unsigned long>(octets[3]);

        outAddress = address;
        outPort = port;

        return true;
    }

    return false;
}

int main()
{
    string input;

    while (true)
    {
        cout << "Enter a string (or 'END' to quit): ";
        getline(cin, input);

        if (input == "END")
        {
            cout << "Program terminated." << endl;
            break;
        }

        unsigned long address = 0;
        int port = -1;

        if (extractIPv4(input, address, port))
        {
            unsigned long a = (address / 16777216UL) % 256;
            unsigned long b = (address / 65536UL) % 256;
            unsigned long c = (address / 256UL) % 256;
            unsigned long d = address % 256;

            cout << "Extracted IPv4 address: "
                 << a << "." << b << "." << c << "." << d
                 << " (decimal value: " << address
                 << ", port: ";

            if (port == -1)
            {
                cout << "none";
            }
            else
            {
                cout << port;
            }

            cout << ")" << endl;
        }
        else
        {
            cout << "Invalid input: no valid IPv4 address found" << endl;
        }
    }

    return 0;
}