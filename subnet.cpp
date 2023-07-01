#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <bitset>
using namespace std;

/*declaring the functions*/

string allocate_ip(int noHosts);
pair<bitset<32>, string> generate_mask(int noHosts);
string binary_to_decimal(bitset<32>, string);
pair<bitset<32>, string> decimal_to_binary(string);
pair<bitset<32>, bitset<32>> reservedIpAddresses(bitset<32> mask, bitset<32> ipAddress);
void unitTest();
string generateNextIpAddress(string ip);
vector<pair<string, string>> subnetting(int noSubnets, int noHosts, vector<int> noSubnetHosts, string ip);

/*Defining the function bodies*/
string allocate_ip(int noHosts)
{
    int bits_no_hosts = ceil(log2(noHosts));
    string assigned_ip = "";
    srand(time(0));
    if (bits_no_hosts <= 16)
    {
        assigned_ip = "192.168." + to_string(rand() % 256) + "." + to_string(rand() % 256) + "/" + to_string(32 - bits_no_hosts);
    }
    else if (bits_no_hosts <= 20)
    {
        assigned_ip = "171." + to_string((rand() + 16) % 32) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256) + "/" + to_string(32 - bits_no_hosts);
    }
    else if (bits_no_hosts <= 24)
    {
        assigned_ip = "10." + to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256) + "/" + to_string(32 - bits_no_hosts);
    }
    else
    {
        cout << "Required number of hosts is too large to be accomodated\n";
        assigned_ip = "";
    }
    return assigned_ip;
}

pair<bitset<32>, string> generate_mask(int noHosts)
{
    int bits = ceil(log2(noHosts));
    if (bits > 24)
    {
        cout << "Desired number of hosts is too large to be accomodated.\n";
        return {bitset<32>(0), "/0"};
    }
    int val = (1 << bits) - 1;
    bitset<32> mask(val);
    mask.flip();
    return {mask, "/" + to_string(32 - bits)};
}

string binary_to_decimal(bitset<32> bs_ip, string mask) // converts the binary ip address( in bitset ) to decimal
{
    string s_ip = bs_ip.to_string();
    string dd_ip = "";
    for (int i = 0; i < 32; i += 8)
    {
        unsigned long octet = bitset<8>(s_ip.substr(i, 8)).to_ulong(); 
        dd_ip += to_string(octet) + ".";
    }
    dd_ip = dd_ip.substr(0, dd_ip.length() - 1);
    return dd_ip + mask;
}

pair<bitset<32>, string> decimal_to_binary(string ip)
{
    // variable declaration.
    string octet, bin_ip;

    // separating the mask from the ip address string
    int pos = ip.find('/');
    string mask = ip.substr(pos);
    ip = ip.substr(0, pos);

    stringstream ip_address(ip); // converts the input stream into a stringstream
    while (getline(ip_address, octet, '.'))
    {
        bitset<8> bin_octet(stoi(octet)); // converts the decimal octet into the binary form as a bitset
        bin_ip += bin_octet.to_string();  // converts the bitset into a binary string
    }
    bitset<32> bin_ip_address(bin_ip);
    return {bin_ip_address, mask};
}

pair<bitset<32>, bitset<32>> reservedIpAddresses(bitset<32> mask, bitset<32> ipAddress)
{
    bitset<32> network_id = (ipAddress & mask);
    bitset<32> broadcast_id = network_id | mask.flip();
    // cout<<network_id<<" "<<broadcast_id<<endl;
    return {network_id, broadcast_id};
}

string generateNextIpAddress(string ip)
{
    // variable declaration.
    vector<int> octet;

    // separating the mask from the ip address string
    int pos = ip.find('/');
    string mask = ip.substr(pos);
    ip = ip.substr(0, pos);

    // turning the ip address into a stringstream
    stringstream intermediate(ip);

    // tokenizing the ip address to extract all octets
    while (getline(intermediate, ip, '.'))
        octet.push_back(stoi(ip));

    octet[3] += 1;
    if (octet[3] > 255)
    {
        for (int i = 3; i > 0; i--)
        {
            octet[i - 1] += (octet[i]) / 256;
            if (octet[0] > 255)
                return "255.255.255.255" + mask;
            octet[i] %= 256;
        }
    }
    return to_string(octet[0]) + "." + to_string(octet[1]) + "." + to_string(octet[2]) + "." + to_string(octet[3]) + mask;
}

vector<pair<string, string>> subnetting(int noSubnets, int noHosts, vector<int> noSubnetHosts, string ip)
{

    // variable declaration
    vector<pair<string, string>> subnets(noSubnets);
    pair<bitset<32>, string> subnetMask;
    pair<bitset<32>, string> binary_ip = decimal_to_binary(ip);

    for (int i = 0; i < noSubnets; i++)
    {
        subnetMask = generate_mask(noSubnetHosts[i]);
        pair<bitset<32>, bitset<32>> BreservedSubnetAddress = reservedIpAddresses(subnetMask.first, binary_ip.first);
        subnets[i] = {binary_to_decimal(BreservedSubnetAddress.first, subnetMask.second), binary_to_decimal(BreservedSubnetAddress.second, subnetMask.second)};
        binary_ip = decimal_to_binary(generateNextIpAddress(subnets[i].second));
    }

    return subnets;
}

vector<string>  generatePublicIp() {
    int octet=1; bool notPresent = true;
    vector<string> ans;
    srand(time(0));
    for(int i=1;i<=8;i++) {
        int num1 = 1 + (rand() % 256);
        int num2 = 1 + (rand() % 256);
        int num3 = 1 + (rand() % 256);
        int num4 = 1 + (rand() % 256);
        if(num1 == 10) num1 =  (num1 + 1 + rand()) % 256;
        if(num1 == 171) {
            if(num2>=16 && num2<=31) num2 = (num2 + 1 + rand()) % 256;
        }
        else if(num1 == 192) {
            if(num2 == 168) num2 = (num2 + 1 + rand()) % 256;
        }
        string ip = to_string(num1) + "." + to_string(num2) + "." + to_string(num3) + "." + to_string(num4) + "/" + to_string(rand() % 30);
        for(auto it : ans) {
            if(it == ip) {
                i -= 1; notPresent = false; break;
            }
        }
        if(notPresent) ans.push_back(ip);
    }
    return ans;
}

int main()
{
    // input section
    int noHosts, noSubnets, totSubnetHost = 0;
    bool correct = false;
    cout << "Input the desired number of HOSTS in the network : ";
    cin >> noHosts;
    while(1) {
        cout << "Input the desired number of SUBNETS in the network : ";
        cin >> noSubnets;
        if(noSubnets<noHosts) break;
        else cout<<"Invalid number of subnets. Please try again.\n";
    }
    vector<int> noSubnetHosts(noSubnets);
    cout << "Input then number of hosts in each subnet : \n";
    for (int i = 0; i < noSubnets; i++)
    {
        cout << "Subnet - " << i + 1 << " : ";
        cin >> noSubnetHosts[i];
        totSubnetHost += noSubnetHosts[i];
        if (totSubnetHost > noHosts || noSubnetHosts[i] > noHosts)
        {
            cout << "Invalid number of hosts . Please enter again.\n";
            i -= 1;
        }
    }

    pair<bitset<32>, string> mask = generate_mask(noHosts);
    string assignedIp = allocate_ip(noHosts);
    pair<bitset<32>, string> assignedIpBinary = decimal_to_binary(assignedIp);

    pair<bitset<32>, bitset<32>> reservedIpBinary = reservedIpAddresses(mask.first, assignedIpBinary.first);
    pair<string, string> reservedIp = {binary_to_decimal(reservedIpBinary.first, mask.second), binary_to_decimal(reservedIpBinary.second, mask.second)};
    string startingIp = generateNextIpAddress(reservedIp.first);
    vector<pair<string, string>> subnets = subnetting(noSubnets, noHosts, noSubnetHosts, startingIp);

    // print section
    cout << "-----------------------------------------------------------------\n";
    cout << "Network id : " << reservedIp.first << endl;
    cout << "Broadcast id : " << reservedIp.second << endl;
    cout << "-----------------------------------------------------------------\n";
    for (int i = 0; i < noSubnets; i++)
    {
        cout << "Subnet - " << i + 1 << endl;
        int pos = (subnets[i].first).find('/');
        cout << "Mask : "<<subnets[i].first.substr(pos)<<endl;
        cout << "Network id : " << subnets[i].first << endl;
        cout << "Broadcast id : " << subnets[i].second << endl;
        cout << "-----------------------------------------------------------------\n";
    }
    cout<<"Public IPs assigned by NAT are : "<<endl;
    auto publicIp = generatePublicIp();
    for(auto it : publicIp) cout<<it<<" "<<endl;
        cout << "-----------------------------------------------------------------\n";
}

