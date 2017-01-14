README FOR Server.py AND Client.py

SETTINGS:

TCP_IP is the ip address of the server.

TCP_PORT is the port to communicate over.

BUFFER_SIZE is the max size of bytes read by recv.

SSL_ON option eneables SSL communications of the server and client. It MUST be set to the same value on both (either True or False).

TRACE is an option that can be set to True or False. It just provides some print statements to show what is happening.


INSTRUCTIONS:

**Note that all tests were run in linux Mint running a 64-bit Ubuntu kernel for both the server and client and using python3**

1. Set the TCP_IP and TCP_PORT to be used in both Server.py and Client.py files. 
2. Place the Server.py file in a directory of your choice on one machine or VM and then change to that directory in command line.
3. On another machine or VM, place the Client.py file in a directory of your choice and change to that directory in command line. 
4. Execute 'python3 Server.py' on the first machine and then 'python3 Client.py' on the second. 
5. When prompted by the client housing machine, enter 'What is the current date and time?' as a query to send the server. 
6. The server should respond.


USEFUL COMMANDS:

 	python3 Server.py		will launch the server, which waits for a client to connect
	python3 Client.py		will launch the client asking the user to input a request, then connect to the server sending the request
	CTRL+C 					will close the server with a keyboard interrupt



****************************************************************OPTIONAL SSL TESTING***********************************************************

If you want to use SSL, then SSL_ON must be set to true in both the server and client files. The directory containing the server file must 
also have the 'cert' and 'key' files in it, and the directory containing the client file must have the 'cert' file in it.

If the key or cert files expire, new ones can be generated using the following command line arguments with openssl:
	
	openssl genrsa 1024 > key											generates a key

	openssl req -new -x509 -nodes -sha1 -days 365 -key key > cert		generates a self-signed certificate based on the key

Note that these files must be placed in the correct directories as describes above. These are also only for testing purposes, do not use these
for any non-testing implementation of SSL. Creation of these requires openssl.

******************** Further note with SSL: I have run into issues resulting in:
				ssl.SSLError: [SSL: TLSV1_ALERT_UNKNOWN_CA] tlsv1 alert unknown ca (_ssl.c:600)

This was happening when I created the key and cert files on the server machine and simply tried to transfer a copy of the cert to the client machine. I then transfered the key to the client VM, created a new cert there, and transfered a copy of that cert back to the server machine as well as leaving a copy on the client VM. This allowed for SSL to function. I am not certain about the intricacies of why this worked, so if you want to try using SSL then you may need to waste some time generating key and cert files to get it working. ******************
