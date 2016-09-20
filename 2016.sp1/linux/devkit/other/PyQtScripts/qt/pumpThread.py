#Creation Date:  (July 16, 2007)
#Author: John Creson
import maya.cmds as cmds
import maya.utils as utils
import threading
import time
import sys
from PyQt4 import QtCore, QtGui


pumpedThread = None
app = None


def pumpQt():

	global app
	def processor():
		app.processEvents()
                        

	while 1:
		time.sleep(0.01)
		utils.executeDeferred( processor )

def initializePumpThread():
	global pumpedThread
	global app
	if pumpedThread == None:
		app = QtGui.QApplication(sys.argv)
		pumpedThread = threading.Thread( target = pumpQt, args = () )
		pumpedThread.start()
	
		

# Copyright (C) 1997-2014 Autodesk, Inc., and/or its licensors.
# All rights reserved.
#
# The coded instructions, statements, computer programs, and/or related
# material (collectively the "Data") in these files contain unpublished
# information proprietary to Autodesk, Inc. ("Autodesk") and/or its licensors,
# which is protected by U.S. and Canadian federal copyright law and by
# international treaties.
#
# The Data is provided for use exclusively by You. You have the right to use,
# modify, and incorporate this Data into other products for purposes authorized 
# by the Autodesk software license agreement, without fee.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. AUTODESK
# DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTIES
# INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF NON-INFRINGEMENT,
# MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, OR ARISING FROM A COURSE 
# OF DEALING, USAGE, OR TRADE PRACTICE. IN NO EVENT WILL AUTODESK AND/OR ITS
# LICENSORS BE LIABLE FOR ANY LOST REVENUES, DATA, OR PROFITS, OR SPECIAL,
# DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS
# LICENSORS HAS BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES.

