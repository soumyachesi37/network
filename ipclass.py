import ipaddress

def convert_to_binary(ip_address):
    octets = ip_address.split('.')
    binary_ip = []
    for octet in octets:
        binary_octet = bin(int(octet))[2:].zfill(8)
        binary_ip.append(binary_octet)
    return '.'.join(binary_ip)

def get_ip_class(ip_address):
    first_octet = int(ip_address.split('.')[0])
    if 1 <= first_octet <= 126:
        return 'Class A'
    elif 128 <= first_octet <= 191:
        return 'Class B'
    elif 192 <= first_octet <= 223:
        return 'Class C'
    elif 224 <= first_octet <= 239:
        return 'Class D (Multicast)'
    elif 240 <= first_octet <= 255:
        return 'Class E (Reserved)'

def is_valid_hosts(ip_address, num_hosts):
    network = ipaddress.IPv4Network(ip_address)
    max_hosts = network.num_addresses - 2  # Subtract 2 for network and broadcast addresses
    return 0 <= num_hosts <= max_hosts

def get_network_range(ip_address, num_hosts):
    network = ipaddress.IPv4Network(ip_address)
    network_address = str(network.network_address)
    last_ip = str(network.network_address + num_hosts + 1)
    return network_address, last_ip

# Example usage
ip = input("Enter an IP address in dotted decimal format: ")
num_hosts = int(input("Enter the number of hosts: "))

binary_ip = convert_to_binary(ip)
print("Binary IP address:", binary_ip)

ip_class = get_ip_class(ip)
print("IP address class:", ip_class)

if is_valid_hosts(ip, num_hosts):
    first_ip, last_ip = get_network_range(ip, num_hosts)
    print("First IP of the network:", first_ip)
    print("Last IP of the network:", last_ip)
else:
    print("Invalid number of hosts for the given IP address.")
