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


class SocketTest:
	UDP_IP = "localhost"
	UDP_PORT = 55176 # Default server port
	device_name = "defaultDeviceName"
	other_device = "defaultOther"
	
	def __init__(self, ip, port, device, other):
		if ip is not None:
			self.UDP_IP = ip
		self.UDP_PORT = port
		if device is not None:
			self.device_name = device
			
		if other is not None:
			self.other_device = other

	def SendMessage(self):
		message = "user:&:" + self.device_name + ":&:" + self.other_device + ":&:other_data"

		print("Sending message!")

		sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		sock.setblocking(0)
		#sock.bind(('', 4128))
		sock.sendto(message.encode('utf-8'), (self.UDP_IP, self.UDP_PORT))

		# Timeout socket receive in 10 seconds
		ready = select.select([sock], [], [], 10)
		if ready[0]:
			data, addr = sock.recvfrom(512)
			print(self.device_name + " received: " + data.decode('utf-8'))
			sock.close()
			return True
		else:
			print("Return from server timed out")
			sock.close()
			return False
	
def DefineArgs():
	parser = argparse.ArgumentParser()
	parser.add_argument("--host", help="Host IP address")
	parser.add_argument("port_number", help="Port number to use", type=int)
	parser.add_argument("device_name", help="Device name to send")
	parser.add_argument("other_device", help="Device name of device trying to connect to")
	return parser
	
if __name__ == "__main__":
	parser = DefineArgs()
	args = parser.parse_args()
	test = SocketTest(args.host, args.port_number, args.device_name, args.other_device)
	test.SendMessage()