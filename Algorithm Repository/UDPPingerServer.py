import sys
import time
from socket import *

# Get the server hostname and port as command line arguments
argv = sys.argv
host = argv[1]
port = argv[2]
timeout = 1000  # in second

serversocket = socket(AF_INET, SOCK_DGRAM)

# Command line argument is a string, change the port into integer
port = int(port)

serversocket.bind((host, port))

print("Waiting to receive message...")

while 1:
    message, address = serversocket.recvfrom(1024)

    print("Server receive message:" + message.decode())

    message = message.decode()[0] + 'o' + message.decode()[2:]

    serversocket.sendto(message.encode(), address)

    print("Reply succesfully!")

seversocket.close()
