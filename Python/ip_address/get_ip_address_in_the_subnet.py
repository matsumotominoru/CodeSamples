import ipaddress

# スキャン対象のサブネット
SUBNET = '192.168.3.0/24'
if __name__ == '__main__':
    for ip in ipaddress.ip_network(SUBNET).hosts():
        #print all 254 ip address in the range(1 - 254); getting used ip address requires connection test.
        print(str(ip))
