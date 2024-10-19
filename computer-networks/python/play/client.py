import random
import socket
import struct
from time import sleep

if __name__ == '__main__':
    my_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)

    my_socket.connect(('127.0.0.1', 1234))

    left = 0
    right = 1000
    while True:
        guess = random.randint(left, right)
        my_socket.send(struct.pack('i', guess))

        response = my_socket.recv(1024).decode()
        if response == "too small":
            left = guess + 1
        elif response == "too large":
            right = guess - 1
        else:
            print(response)
            break

        sleep(1)

    my_socket.close()
