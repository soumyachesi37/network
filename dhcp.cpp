#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include<map>

using namespace std;

string generate_mac_address() {
    stringstream stream;
    stream << setfill('0') << setw(2) << hex << rand() % 256;
    for (int i = 1; i < 6; i++) {
        stream << ":" << setfill('0') << setw(2) << hex << rand() % 256;
    }
    return stream.str();
}

int main() {
    int total_hosts, initial_hosts;
    cout << "Enter the total number of hosts to be accommodated in the network: ";
    cin >> total_hosts;
    cout << "Enter the number of initially allocated hosts: ";
    cin >> initial_hosts;

    srand(time(NULL));
    vector<string> mac_list;
    for (int i = 0; i < total_hosts; i++) {
        string mac_address = generate_mac_address();
        mac_list.push_back(mac_address);
    }

    vector<string> pool_list;
    for (int i = 2; i < 256; i++) {
        pool_list.push_back("192.168.1." + to_string(i));
    }

    map<string, string> mapping_table;

    for (int i = 0; i < initial_hosts; i++) {
        int random_index = rand() % pool_list.size();
        string random_ip = pool_list[random_index];
        mapping_table[mac_list[i]] = random_ip;
        pool_list.erase(pool_list.begin() + random_index);
    }

    cout << "DHCP Server Allocation Table - Initial Allocation" << endl;
    cout << "--------------------------------------------------" << endl;
    for (const auto& pair : mapping_table) {
    cout << pair.first << " | " << pair.second << endl;
    }
    for (int i = initial_hosts; i < total_hosts; i++) {
        string mac_address = mac_list[i];
        if (mapping_table.count(mac_address) > 0) {
            string ip = mapping_table[mac_address];
            cout << "DHCP Server Allocation Table - Request for " << mac_address << endl;
            cout << "--------------------------------------------------" << endl;
            cout << mac_address << " | " << ip << endl;
        }
        else {
            int random_index = rand() % pool_list.size();
            string random_ip = pool_list[random_index];
            mapping_table[mac_address] = random_ip;
            pool_list.erase(pool_list.begin() + random_index);
            cout << "DHCP Server Allocation Table - Request for " << mac_address << endl;
            cout << "--------------------------------------------------" << endl;
            cout << mac_address << " | " << random_ip << endl;
        }
    }

    cout << "DHCP Server Allocation Table - Final" << endl;
    cout << "------------------------------------" << endl;
    for (auto& pair : mapping_table) {
    cout << pair.first << " | " << pair.second << endl;
    }
    return 0;
}
