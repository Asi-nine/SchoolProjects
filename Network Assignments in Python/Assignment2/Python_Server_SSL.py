#Python server that responds to the phrase "What is the current date and time?" with its local date and time.
#Written by: Peter Valovcik

import socket
import datetime
import ssl

TCP_IP = '172.16.132.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024
SSL_ON = False  # Set this to True if you want to use SSL and False if not. (Must have client set to the same!)
TRACE = True # Set this to True if you want extra print statements tracing some of the interactions with the client

# Set up socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
if SSL_ON:
	s = ssl.wrap_socket(s, server_side=True, certfile="cert", keyfile="key") # ssl wrapper for socket
s.bind((TCP_IP, TCP_PORT))

# Listen forever on the port (a keyboard interrupt CTRL+C can exit)
while True:
	print("\nWaiting for an incoming connection.")
	s.listen(1)
	conn, addr = s.accept() # Accept an incomming connection
	if TRACE:
		print('Server Address:', TCP_IP) 
		print('Client Address:', addr)
		print("Connection to Client Established")
	data = (conn.recv(BUFFER_SIZE)).decode() # Receive data from the connected client and decode it from bytes
	if TRACE:
		print(data) 
	# Check to see if the received data is requesting the current date and time, if so get the date and time and return that to the client.
	if data == "What is the current date and time?":
		current_datetime = datetime.datetime.now() # get current date and time
		date_string = current_datetime.strftime("%m/%d/%Y") # date formatted to MM/DD/YYYY
		time_string = current_datetime.strftime("%H:%M:%S") # 24 hour time formatted as HH:MM:SS
		data_to_return = "Current date and time: " + date_string + " " + time_string # the string giving the date and time to return
		conn.send(data_to_return.encode()) # encode the data to byte representation and send to client
	# If received data was not requesting date and time, inform the client that is the only request handled by this server.
	else:
		data_to_return = "That is an invalid request. I only handle the request: \"What is the current date and time?\""
		conn.send(data_to_return.encode()) # encode the data to byte representation and send to client
	if TRACE:
			print("Returned: \n" + data_to_return)
	conn.close() # end connection with client
