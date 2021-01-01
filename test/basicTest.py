'''
@file:				basicTest.py
@author:			David Hite
@created:			05/22/2018
@description:       Attempts to send and receive messages from two sockets
'''
import time
import unittest
from socketTest import SocketTest
from multiprocessing.pool import ThreadPool

class TestBasic(unittest.TestCase):

	def test_basic(self):
		print('test_basic: Checking that server returns data to two clients')
		socket1 = SocketTest(None, 55176, 'me', 'other', False)
		socket2 = SocketTest(None, 55176, 'other', 'me', False)

		pool = ThreadPool(processes=2)

		result1 = pool.apply_async(socket1.SendMessage, ())
		result2 = pool.apply_async(socket2.SendMessage, ())

		results = result1.get()
		results = results and result2.get()
		self.assertTrue(results)
		if results:
			print('test_basic: PASSED')
		else:
			print('test_basic: FAILED')
		
	def test_time(self):
		print('test_time: Checking that no data is returned from server if')
		print('\t\tsecond client takes more than 10 seconds to attempt connection')
		socket1 = SocketTest(None, 55176, 'me', 'other', False)
		socket2 = SocketTest(None, 55176, 'other', 'me', False)
		
		pool = ThreadPool(processes=2)
		result1 = pool.apply_async(socket1.SendMessage, ())
		time.sleep(10)
		result2 = pool.apply_async(socket2.SendMessage, ())
		
		self.assertFalse(result1.get())
		self.assertFalse(result2.get())
		
		if result1.get():
			print('test_time: FAILED, Client 1 received response')
		elif result2.get():
			print('test_time: FAILED, Client 2 received response')
		else:
			print('test_time: PASSED')

if __name__ == '__main__':
	unittest.main()