#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>

using namespace std;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

char findIPAddressClass(const string& ip) {
    vector<string> octets = split(ip, '.');
    int firstOctet = stoi(octets[0]);

    if (firstOctet >= 0 && firstOctet <= 127) {
        return 'A';
    } else if (firstOctet >= 128 && firstOctet <= 191) {
        return 'B';
    } else if (firstOctet >= 192 && firstOctet <= 223) {
        return 'C';
    } else if (firstOctet >= 224 && firstOctet <= 239) {
        return 'D';
    } else if (firstOctet >= 240 && firstOctet <= 255) {
        return 'E';
    } else {
        return 'N'; // Invalid IP address
    }
}

string convertToBinary(const string& ip) {
    vector<string> octets = split(ip, '.');
    string binaryIP;
    for (const string& octet : octets) {
        int value = stoi(octet);
        bitset<8> binaryValue(value);
        binaryIP += binaryValue.to_string();
    }
    return binaryIP;
}

string findNetworkID(const string& ip, char ipAddressClass) {
    vector<string> octets = split(ip, '.');
    if (ipAddressClass == 'A') {
        return octets[0] + ".0.0.0";
    } else if (ipAddressClass == 'B') {
        return octets[0] + "." + octets[1] + ".0.0";
    } else if (ipAddressClass == 'C') {
        return octets[0] + "." + octets[1] + "." + octets[2] + ".0";
    } else {
        return "N/A"; // Network ID not applicable for classes D and E
    }
}

string findFirstIPAddress(const string& networkID, char ipAddressClass) {
    vector<string> octets = split(networkID, '.');
    if (ipAddressClass == 'A' || ipAddressClass == 'B' || ipAddressClass == 'C') {
        octets.back() = "1"; // Set the last octet to 1
        return octets[0] + "." + octets[1] + "." + octets[2] + "." + octets[3];
    } else {
        return "N/A"; // First IP address not applicable for classes D and E
    }
}

string findLastIPAddress(const string& networkID, char ipAddressClass) {
    vector<string> octets = split(networkID, '.');
    if (ipAddressClass == 'A') {
        octets[1] = "255"; // Set the third octet to 255
        octets[2] = "255"; // Set the third octet to 255
        octets[3] = "255"; // Set the third octet to 255
        return octets[0] + "." + octets[1] + "." + octets[2] + "." + octets[3];
    } else if (ipAddressClass == 'B') {
        octets[2] = "255"; // Set the third octet to 255
        octets[3] = "255"; // Set the third octet to 255
        return octets[0] + "." + octets[1] + "." + octets[2] + "." + octets[3];
    } else if (ipAddressClass == 'C') {
        octets[3] = "255"; // Set the last octet to 255
        return octets[0] + "." + octets[1] + "." + octets[2] + "." + octets[3];
    } else {
        return "N/A"; // Last IP address not applicable for classes D and E
    }
}

bool isSuitableIPClass(char ipAddressClass, int numHosts) {
    if (ipAddressClass == 'A') {
        return numHosts <= 16777214; // 2^24 - 2
    } else if (ipAddressClass == 'B') {
        return numHosts <= 65534; // 2^16 - 2
    } else if (ipAddressClass == 'C') {
        return numHosts <= 254; // 2^8 - 2
    } else {
        return false; // Not applicable for classes D and E
    }
}

int main() {
    string ipAddress;
    cout << "Enter an IP address in dotted decimal format: ";
    cin >> ipAddress;

    char ipAddressClass = findIPAddressClass(ipAddress);
    if (ipAddressClass != 'N') {
        cout << "IP address class: " << ipAddressClass << endl;
        
        int numHosts;
        cout << "Enter the number of hosts required: ";
        cin >> numHosts;

        if (isSuitableIPClass(ipAddressClass, numHosts)) {
            string networkID = findNetworkID(ipAddress, ipAddressClass);
            if (networkID != "N/A") {
                cout << "Network ID: " << networkID << endl;
                string firstIPAddress = findFirstIPAddress(networkID, ipAddressClass);
                string lastIPAddress = findLastIPAddress(networkID, ipAddressClass);
                if (firstIPAddress != "N/A") {
                    cout << "First IP address: " << firstIPAddress << endl;
                    cout << "Last IP address: " << lastIPAddress << endl;
                } else {
                    cout << "First IP address: N/A" << endl;
                    cout << "Last IP address: N/A" << endl;
                }
            } else {
                cout << "Network ID: N/A" << endl;
            }
        } else {
            cout << "The IP class is not suitable for the given number of hosts." << endl;
        }
    } else {
        cout << "Invalid IP address!" << endl;
    }

    return 0;
}
