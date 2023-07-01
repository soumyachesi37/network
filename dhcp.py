import random

# User input for the total number of hosts and the number of initially allocated hosts
total_hosts = int(input("Enter the total number of hosts to be accommodated in the network: "))
initial_hosts = int(input("Enter the number of initially allocated hosts: "))

# Generate a list of unique MAC addresses for all hosts
mac_list = []
for i in range(total_hosts):
    mac_list.append(':'.join(['{:02x}'.format(random.randint(0, 255)) for _ in range(6)]))

# Create a dictionary to store the MAC to IP mapping table
mapping_table = {}

# Create a pool of available IP addresses
pool_list = []
for i in range(2, 256):
    pool_list.append('192.168.1.' + str(i))

# Assign IP addresses to the already allocated hosts
for i in range(initial_hosts):
    random_ip = random.choice(pool_list)
    mapping_table[mac_list[i]] = random_ip
    pool_list.remove(random_ip)

# Print the initial allocation table
print("DHCP Server Allocation Table - Initial Allocation")
print("--------------------------------------------------")
for mac, ip in mapping_table.items():
    print(mac + " | " + ip)

# Handle new requests for IP addresses
for i in range(initial_hosts, total_hosts):
    # Check if MAC address is already in the mapping table
    if mac_list[i] in mapping_table:
        ip = mapping_table[mac_list[i]]
    else:
        # Assign a new IP address to the host
        random_ip = random.choice(pool_list)
        mapping_table[mac_list[i]] = random_ip
        pool_list.remove(random_ip)
        ip = random_ip

    # Print the allocation details for the host
    print("DHCP Server Allocation Table - New Request")
    print("-------------------------------------------")
    print(mac_list[i] + " | " + ip)

# Print the final DHCP server allocation table
print("DHCP Server Allocation Table - Final")
print("------------------------------------")
for mac, ip in mapping_table.items():
    print(mac + " | " + ip)
