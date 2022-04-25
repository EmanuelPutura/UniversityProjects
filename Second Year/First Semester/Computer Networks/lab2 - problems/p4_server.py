import socket
import threading
import struct

mutex = threading.Lock()
reset_event = threading.Event()
finished_event = threading.Event()
finished_event.clear()
array = []
threads = []

def merge(data, array1, array2):
    i = j = k = 0
    
    while i < len(array1) and j < len(array2):
        if array1[i] < array2[j]:
            data[k] = array1[i]
            i += 1
        else:
            data[k] = array2[j]
            j += 1
        k += 1

    while i < len(array1):
        data[k] = array1[i]
        i += 1
        k += 1

    while j < len(array2):
        data[k] = array2[j]
        j += 1
        k += 1

def mergeSort(data):
    if len(data) <= 1:
        return
    
    mid = len(data) // 2
    left = data[:mid]
    right = data[mid:]

    mergeSort(left)
    mergeSort(right)
    merge(data, left, right)

def worker(client_socket, client_address):
    global mutex, array, threads, reset_event, finished_event
    print("...client {} connected to the server".format(client_address[0]))

    n = client_socket.recv(4)
    n = struct.unpack('!I', n)[0]
    print("...received number {} from client {}:{}".format(n, client_address[0], client_address[1]))

    if n == 0:
        mutex.acquire()
        reset_event.set()
        finished_event.set()
        mutex.release()
        return

    numbers = []
    for i in range(n):
        numbers.append(struct.unpack('!f', client_socket.recv(4))[0])

    print("...received list {} from client {}:{}".format(numbers, client_address[0], client_address[1]))

    mutex.acquire()
    array += numbers
    mergeSort(array)
    mutex.release()

    finished_event.wait()

    mutex.acquire()
    print("...sending sorted array {} to client {}:{}".format(array, client_address[0], client_address[1]))
    client_socket.sendall(struct.pack('!I', len(array)))
    for no in array:
        client_socket.sendall(struct.pack('!f', no))
    mutex.release()

    client_socket.close()
    print("...worker {}:{} finished".format(client_address[0], client_address[1]))

def resetServer():
    global mutex, array, threads, event
    reset_event.clear()

    while True:
        reset_event.wait()
        for thread in threads:
            thread.join()

        print("...finished all threads\n")
        print("...restarting the server")
        reset_event.clear()
        mutex.acquire()
        threads = []
        array = []
        mutex.release()

if __name__ == "__main__":
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.bind(("0.0.0.0", 2500))
        server_socket.listen(5)
    except socket.error as error:
        print(error.strerror)
        exit(1)

    event_thread = threading.Thread(target=resetServer, daemon=True)
    event_thread.start()

    while True:
        client_socket, client_address = server_socket.accept()
        thread = threading.Thread(target=worker, args=(client_socket, client_address))
        threads.append(thread)
        thread.start()
