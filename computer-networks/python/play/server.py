import socket
import socketserver
import struct
import random
import threading
from threading import Thread

the_number = random.randint(1, 1000)
my_lock = threading.Lock()
all_comm_sockets = []
game_over = False


def job(comm_socket: socket.socket, addr):
    global game_over

    print("in the job for addr" + str(addr[0]) + " " + str(addr[1]))

    while True:
        my_lock.acquire()
        if game_over:
            break
        try:
            data = comm_socket.recv(4)
        except socket.error as e:
            print(e)
            break
        my_lock.release()

        guess = struct.unpack('i', data)[0]
        print(addr[1], guess)

        my_lock.acquire()
        if guess == the_number and not game_over:
            game_over = True
            my_lock.release()

            comm_socket.send("You won!".encode())
            print("Game won by " + str(addr))
            for other_comm in all_comm_sockets:
                other_comm.send("You lost!".encode())
                other_comm.close()
            comm_socket.close()
            break
        else:
            my_lock.release()

            if guess < the_number:
                comm_socket.send("too small".encode())
            else:
                comm_socket.send("too large".encode())



if __name__ == '__main__':
    welcoming_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
    welcoming_socket.bind(('127.0.0.1', 1234))
    welcoming_socket.listen()

    while True:
        comm_socket, addr = welcoming_socket.accept()
        all_comm_sockets.append(comm_socket)

        thread = Thread(target=job, args=[comm_socket, addr])
        thread.start()
