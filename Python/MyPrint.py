#######################################################################################################################
# --- Colors
BLACK 	= '\033[90m' # 5 chars
RED   	= '\033[91m' # 5 chars
GREEN 	= '\033[92m' # 5 chars
YELLOW	= '\033[93m' # 5 chars
BLUE	= '\033[94m' # 5 chars
MAGENTA = '\033[95m' # 5 chars
CYAN 	= '\033[96m' # 5 chars
WHITE	= '\033[97m' # 5 chars
RESET 	= '\033[0m'  # 4 chars

#######################################################################################################################
def printError(iLevel,szMessage):
	if(iLevel == 0):
		print("[{pfx: >{fill}}]{sp: <{fill2}}{msg: >{fill3}}".format(pfx='DEBUG', fill='5',sp=' --- ',fill2='5',msg=szMessage,fill3='0'))
	elif(iLevel == 1):
		print("[{pfx: >{fill}}]{sp: <{fill2}}{msg: >{fill3}}".format(pfx='INFO', fill='5',sp=' --- ',fill2='5',msg=szMessage,fill3='0'))
	elif(iLevel == 2):
		print("[{pfx: >{fill}}]{sp: <{fill2}}{msg: >{fill3}}".format(pfx='WARN', fill='5',sp=' --- ',fill2='5',msg=szMessage,fill3='0'))
	elif(iLevel == 3):
		print("[{pfx: >{fill}}]{sp: <{fill2}}{msg: >{fill3}}".format(pfx='ERROR', fill='5',sp=' --- ',fill2='5',msg=szMessage,fill3='0'))
	elif(iLevel == 4):
		print("[{pfx: >{fill}}]{sp: <{fill2}}{msg: >{fill3}}".format(pfx='FATAL', fill='5',sp=' --- ',fill2='5',msg=szMessage,fill3='0'))
	else:
		print("[{pfx: >{fill}}]{sp: <{fill2}}{msg: >{fill3}}".format(pfx='UNKNW', fill='5',sp=' --- ',fill2='5',msg=szMessage,fill3='0'))
		

#######################################################################################################################
def printMessage(iSpace, szMessage, ending):
	try:
		print("{sp: >{fill}}{msg: <{fill2}}".format(sp='', fill=iSpace,msg=szMessage,fill2='0'),end=ending)
	except:
		printError(2,"Error while calling the function printMessage")


#######################################################################################################################		
def printPrefix(iSpacePfx, szPfx, iSpaceMsg, szMsg, ending):
	print("[{pfx: >{fill}}]{sp: <{fill2}}{msg: >{fill3}}".format(pfx=szPfx, fill=iSpacePfx,sp='',fill2=iSpaceMsg,msg=szMsg,fill3='0'),end=ending)

#######################################################################################################################		
def printBound(iSpacePfx, szPfx, ending):
	print("{pfx: >{fill}}".format(pfx=szPfx, fill=iSpacePfx),end=ending)

def black(s):
    return BLACK + s + RESET
def red(s):
    return RED + s + RESET
def green(s):
    return GREEN + s + RESET
def yellow(s):
    return YELLOW + s + RESET
def blue(s):
    return BLUE + s + RESET
def magenta(s):
    return MAGENTA + s + RESET
def cyan(s):
    return CYAN + s + RESET
def white(s):
    return WHITE + s + RESET
