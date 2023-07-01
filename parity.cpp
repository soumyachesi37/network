#include <iostream>
#include <bitset>
#include<string>
using namespace std;

// function to calculate parity bit
int calculate_parity(string data, char parity_type) {
    int parity_bit = 0;
    for (int i = 0; i < data.length(); i++) {
        if (data[i] == '1') {
            parity_bit ^= 1;
        }
    }
    if (parity_type == 'o') { // odd parity
        parity_bit ^= 1;
    }
    return parity_bit;
}

int main() {
    int n;
    string data;
    char parity_type;

    // take input from user
    cout << "Enter size of data (n): ";
    cin >> n;
    cout << "Enter " << n-1 << " bit data: ";
    cin >> data;
    cout << "Enter parity type (o for odd, e for even): ";
    cin >> parity_type;

    // calculate parity bit
    int parity_bit = calculate_parity(data, parity_type);

    // add parity bit to data
    data += to_string(parity_bit);

    cout << "Generated n-bit data: " << data << endl;

    // take input from user
    string received_data;
    cout << "Enter received n-bit data: ";
    cin >> received_data;
    cout << "Enter parity type (o for odd, e for even): ";
    cin >> parity_type;

    // check parity
    int received_parity_bit = calculate_parity(received_data.substr(0, received_data.length()-1), parity_type);
    if (received_parity_bit != (received_data[received_data.length()-1] - '0')) {
        cout << "Error: Parity check failed!" << endl;
    } else {
        cout << "Parity check passed!" << endl;
        cout << "Original data: " << received_data.substr(0, received_data.length()-1) << endl;
    }

    return 0;
}
