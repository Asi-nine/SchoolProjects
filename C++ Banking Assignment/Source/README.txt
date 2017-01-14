TEST SYSTEM:

Linux 3.13.0-37-generic x86_64
Distributor ID:	LinuxMint
Description:	Linux Mint 17.1 Rebecca
Release:	17.1
Codename:	rebecca

QMake version 3.0
Using Qt version 5.7.0 


This program will likely not work on Windows since there are hardcoded system calls. I have no tested it on 
Windows or any other platform other than my own whatsoever.
*****************************************************************************************************************


ISTALLATION AND RUNNING INSTRUCTIONS:

****************************
IDE STYLE
****************************

1. Put the Banking folder and data folder into the same directory.
2. Open QTCreator (QT5.7) 
3. Select Open Project.
4. Open the Banking.pro file inside of the Banking folder.
5. Run in QTCreator.

****************************
COMMAND LINE STYLE
****************************
NOTE: this will require qmake.
****************************

1. Put the Banking folder and data folder into the same directory.
2. Open terminal and change directory to the Banking folder.
3. Enter 'qmake'
4. Enter 'make'
5. Execute 'Banking'
*****************************************************************************************************************

IMPORTANT INFORMATION:

These are the 3 included users for testing and their credentials:

USER ID:	ROLE:			PIN:
	1		Manager			11
	2		Client			11
	3		Maintenance		11


If you are having trouble with data, make sure it is in the same directory as the Banking folder, or modify the code
as you see fit to point things in the right place.
*****************************************************************************************************************

