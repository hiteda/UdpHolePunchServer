'''
@file:				socketTest.py
@author:			David Hite
@created:			11/17/2017
@description: Sends a request to the server socket, then listens for 10 seconds
							for a response
'''
import argparse
import socket
import select
import sys

parser = argparse.ArgumentParser()
parser.add_argument("--host", help="Host IP address")
parser.add_argument("port_number", help="Port number to use", type=int)
parser.add_argument("device_name", help="Device name to send")
parser.add_argument("other_device", help="Device name of device trying to connect to")
args = parser.parse_args()

UDP_IP = "localhost"
if args.host is not None:
  UDP_IP = args.host
UDP_PORT = args.port_number

device_name = "defaultDeviceName"
if args.device_name is not None:
	device_name = args.device_name
	
other_device = "defaultOther"
if args.other_device is not None:
	other_device = args.other_device

message = "user:&:" + device_name + ":&:" + other_device + ":&:other_data"

print "Sending message!"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setblocking(0)
#sock.bind(('', 4128))
sock.sendto(message, (UDP_IP, UDP_PORT))

# Timeout socket receive in 10 seconds
ready = select.select([sock], [], [], 10)
if ready[0]:
	data, addr = sock.recvfrom(512)
	print "Received: ", data
	sys.exit(0)
else:
	sys.exit(1)