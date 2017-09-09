__author__ = "Olivier Herrou"
__credits__ = ["Olivier Herrou"]
__license__ = "GPL"
__version__ = "1.0.0"
__maintainer__ = "Olivier Herrou"
__email__ = "oli.herrou@gmail.com"
__status__ = "Production"

# This software is for Windows only
# Tested on Windows 7 64bits
# Python version is 3.6.1

from MyPrint import printMessage, printError, printPrefix, printBound, black, red, green, yellow, blue, magenta, cyan, white
from MySerial import ComConnect, ComDisconnect
import COBS as cobs
import sys
import binascii
import msvcrt # Windows Only
import csv
import colorama
import os
from colorama import Fore, Back, Style #https://pypi.python.org/pypi/colorama
import struct
import time
#######################################################################################################################
def kbfunc(): 
	x = msvcrt.kbhit()
	if x: 
		ret = ord(msvcrt.getch()) 
	else: 
		ret = 0 
	return ret

#######################################################################################################################	
def ReadData(ser):
	data = bytearray()
	mystr = ""
	while 1:
		incByte = ser.read(1)
		if(incByte):
			if(incByte[0] == 0):
				return data
			data += incByte
			# # data.append(incByte)
			# mystr = mystr + str(incByte)
			# # data.append(hex(incByte[0]))#format(incByte.decode("utf-8")))

		else:
			return 0

#######################################################################################################################
#######################################################################################################################
#######################################################################################################################
#######################################################################################################################
#######################################################################################################################
#######################################################################################################################
# --- Variable
script, comPort, baudrate, timeout = sys.argv;
comPort = int(comPort)
baudrate = int(baudrate)
timeout = int(timeout)
print(str(timeout))
# --- Start
colorama.init()
# os.system("mode con: cols=130 lines=15")
printError(1,"PRESS ESCAPE TO EXIT THE APPLICATION")
payload = []
ser 	= ComConnect(comPort,timeout,baudrate)
while (1):
	try:
		payload = ReadData(ser)
		if(payload):
			decoded = cobs.decode(payload)
			print(str(decoded))
			encoded = cobs.encode(decoded)
			print(str(encoded))
			ser.write(bytearray(encoded))
	except:
		printError(2,"while loop error")
print("-------------------------------")
ComDisconnect(ser,comPort)
sys.exit(1)