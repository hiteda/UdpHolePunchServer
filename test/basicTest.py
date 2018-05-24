'''
@file:				basicTest.py
@author:			David Hite
@created:			05/22/2018
@description: Attempts to send and receive messages from two sockets
'''
import time
import unittest
from socketTest import SocketTest
from multiprocessing.pool import ThreadPool

class TestBasic(unittest.TestCase):

	def test_basic(self):
		socket1 = SocketTest(None, 55176, 'me', 'other')
		socket2 = SocketTest(None, 55176, 'other', 'me')

		pool = ThreadPool(processes=2)

		result1 = pool.apply_async(socket1.SendMessage, ())
		result2 = pool.apply_async(socket2.SendMessage, ())

		results = result1.get()
		results = results and result2.get()
		self.assertTrue(results)
		
	def test_time(self):
		socket1 = SocketTest(None, 55176, 'me', 'other')
		socket2 = SocketTest(None, 55176, 'other', 'me')
		
		pool = ThreadPool(processes=2)
		result1 = pool.apply_async(socket1.SendMessage, ())
		time.sleep(10)
		result2 = pool.apply_async(socket2.SendMessage, ())
		
		self.assertFalse(result1.get())
		self.assertFalse(result2.get())

if __name__ == '__main__':
	unittest.main()