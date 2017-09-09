import serial #version 2.7
from MyPrint import printMessage, printError, printPrefix, printBound, black, red, green, yellow, blue, magenta, cyan, white

#######################################################################################################################
def ComConnect(comPort,timeout,baudrate):
	print("-------------------------------")
	printPrefix(7,"SERIAL", 4, "Connection to port COM{} ...".format(comPort),'\n')
	print("-------------------------------")
	try:
		ser = serial.Serial()
		ser.port = 'COM'+str(comPort)
		ser.timeout = timeout
		ser.baudrate = baudrate
		ser.open()
	except:
		try:
			ser.close()
		except:
			pass
		printError(2,"Could not open port COM{}".format(comPort))
		sys.exit(1)
	return ser

#######################################################################################################################
def ComDisconnect(ser,comPort):
	print("-------------------------------")
	printPrefix(7,"SERIAL", 4, "Closing COM{} ...".format(comPort),'\n')
	try:
		ser.close()
	except:
		printError(2,"Could not close port COM{}".format(comPort))
		return 1
	printPrefix(7,"SERIAL", 4, "COM{} is closed".format(comPort),'\n')
	print("-------------------------------")
	return 0