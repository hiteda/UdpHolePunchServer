import socket

UDP_IP = "192.168.1.164"
UDP_PORT = 55176
message = "Hey there!"

print "Sending message!"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(message, (UDP_IP, UDP_PORT))
