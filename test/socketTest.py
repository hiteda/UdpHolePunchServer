import argparse
import socket

parser = argparse.ArgumentParser()
parser.add_argument("--host", help="Host IP address")
parser.add_argument("port_number", help="Port number to use", type=int)
args = parser.parse_args()

UDP_IP = "192.168.1.22"
if args.host is not None:
  UDP_IP = args.host
UDP_PORT = args.port_number
message = "me:&:thing1:&:moreStuff"

print "Sending message!"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#sock.bind(('', 4128))
sock.sendto(message, (UDP_IP, UDP_PORT))

data, addr = sock.recvfrom(512)
print "Received: ", data