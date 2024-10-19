__author__ = 'david'

import socket
import threading
import random
import struct

random.seed()
my_num = random.uniform(0.5, 100.5)
print('Server number: ', my_num)
mylock = threading.Lock()
client_guessed = False
winner_thread = 0
e = threading.Event()
e.clear()
threads = []
client_count = 0
guesses = {}
id_to_socket = {}


def worker(cs):
    global mylock, client_guessed, my_num, winner_thread, client_count, e
    global guesses

    mylock.acquire()
    my_idcount = client_count
    mylock.release()

    print('client #', client_count, 'from: ', cs.getpeername(), cs)
    message = 'Hello client #' + str(client_count) + ' ! You are entering the number guess competion now !'
    cs.sendall(bytes(message, 'ascii'))

    try:
        cnumber = cs.recv(4)
        cnumber = struct.unpack('!f', cnumber)[0]
        mylock.acquire()
        guesses[my_idcount] = cnumber
        mylock.release()
    except socket.error as msg:
        print('Error:', msg.strerror)


def resetSrv():
    global mylock, client_guessed, winner_thread, my_num, threads, e, client_count
    global guesses, id_to_socket

    while True:
        e.wait()
        for t in threads:
            t.join()
        print("all threads are finished now")
        e.clear()
        mylock.acquire()
        threads = []
        winner_thread = -1
        client_count = 0
        guesses = {}
        id_to_socket = {}
        my_num = random.uniform(0.5, 100.5)
        print('Server number: ', my_num)
        mylock.release()


if __name__ == '__main__':
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        rs.settimeout(10)
        rs.bind(('0.0.0.0', 1234))
        rs.listen(5)
    except socket.error as msg:
        print(msg.strerror)
        exit(-1)
    # t = threading.Thread(target=resetSrv, daemon=True)
    # t.start()
    while True:
        try:
            client_socket, addrc = rs.accept()
        except (socket.timeout, TimeoutError):
            print('timeout....')

            who_best = 1
            for i in range(2, client_count + 1):
                if abs(guesses[i] - my_num) < abs(guesses[who_best] - my_num):
                    who_best = i
            print("Client ", who_best, "won with number", guesses[who_best])

            for i in range(1, client_count + 1):
                socket_here = id_to_socket[i]
                if i == who_best:
                    message = "You best with error of " + str(abs(guesses[i] - my_num))
                else:
                    message = "You lost!"
                socket_here.sendall(bytes(message, 'ascii'))
            break

        id_to_socket[client_count + 1] = client_socket
        t = threading.Thread(target=worker, args=(client_socket,))
        threads.append(t)
        mylock.acquire()
        client_count += 1
        mylock.release()
        t.start()

    for socket in id_to_socket.values():
        socket.close()
