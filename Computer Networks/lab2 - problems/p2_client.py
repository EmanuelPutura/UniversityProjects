import socket
import struct
import sys

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("{} <address> <port> <file path>".format(sys.argv[0]))
        exit(1)
    
    server_address = sys.argv[1]
    port = int(sys.argv[2])
    file_path = sys.argv[3]
    file_name = file_path.split('/')[-1]    

    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((server_address, port))
        print("...successfully connected to server {} : {}".format(server_address, port))
    except socket.error as error:
        print(error.strerror)
        exit(-1)

    sock.sendall(struct.pack('!I', len(file_path) + 1))
    sock.sendall(bytes(file_path, 'ascii'))
    n = int(struct.unpack('!I', sock.recv(4))[0])
    # n = int(sock.recv(4))
    print(n)

    if n == -1:
        print("...server sent back -1, hence the given file does not exist\n...disconnecting from the server\n")
        exit(0)

    data = sock.recv(n).decode('ascii')
    file_name += "-copy"

    with open(file_name, "w") as file:
        file.write(data)

    print("...client finished its work")
    sock.close()
