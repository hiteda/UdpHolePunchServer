import argparse
import socket

parser = argparse.ArgumentParser()
parser.add_argument("--host", help="Host IP address")
parser.add_argument("port_number", help="Port number to use", type=int)
args = parser.parse_args()

UDP_IP = "192.168.1.164"
if args.host is not None:
  UDP_IP = args.host #"192.168.1.164"
UDP_PORT = args.port_number
message = "me:&:thing:&:moreStuff"

print "Sending message!"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(message, (UDP_IP, UDP_PORT))
