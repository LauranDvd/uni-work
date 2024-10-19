__author__ = 'david'

import socket
import struct
import random

if __name__ == '__main__':
    try:
        s = socket.create_connection(('localhost', 1234))
    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)

    random.seed()

    data = s.recv(1024)
    print(data.decode('ascii'))
    step_count = 0
    my_num = random.uniform(0.5, 100.5)
    try:
        s.sendall(struct.pack('!f', my_num))
    except socket.error as msg:
        print('Error: ', msg.strerror)
        s.close()
        exit(-2)
    print('Sent ', my_num)

    data = s.recv(1024)
    print(data.decode('ascii'))
    s.close()
