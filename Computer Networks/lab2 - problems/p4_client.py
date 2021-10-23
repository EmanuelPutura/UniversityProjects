import socket
import struct
from sys import getsizeof

def readValues(data):
    n = int(input("n >> "))
    for i in range(n):
        data.append(float(input("input no >> ")))
    print("...client got the numbers {}".format(str(data)))

if __name__ == "__main__":
    numbers = []
    readValues(numbers)
    
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect(("192.168.1.108", 2500))
    except socket.error as error:
        print(error.strerror)
        exit(1)

    n = len(numbers)
    client_socket.sendall(struct.pack('!I', n))

    for i in range(n):
        client_socket.sendall(struct.pack('!f', numbers[i]))

    if n == 0:
        exit(0)

    n = client_socket.recv(4)
    n = struct.unpack('!I', n)[0]
    print("...client will receive {} numbers from the server".format(n))

    all_sorted = []
    for i in range(n):
        current = struct.unpack('!f', client_socket.recv(4))[0]
        all_sorted.append(current)

    print("...client received list {} from the server\n".format(all_sorted))
    client_socket.close()
