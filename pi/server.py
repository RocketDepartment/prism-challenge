import socket
import sys
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('192.168.11.110', 10000)
sock.bind(server_address)

sock.listen(1)
while True:
    #print("Waiting for connection")
    connection, client_address = sock.accept()

    data = connection.recv(16)
    print("Received", data)
    time.sleep(0.2)
