#Python client that sends a message to a server based on user input.
#Written by: Peter Valovcik

import socket
import ssl

TCP_IP = '172.16.132.1'
TCP_PORT = 5005
SSL_ON = False # Set this to True if you want to use SSL and False if not. (Must have server set to the same!)
TRACE = True # Set this to True if you want extra print statements tracing some of the interactions with the server
BUFFER_SIZE = 1024

message = input("Please enter a query to send the server: ") # get user input for a message to send the server

if TRACE:
	print ("Attempting to contact server at ",TCP_IP,":",TCP_PORT)
# Set up socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
if SSL_ON:
	s = ssl.wrap_socket(s,  ca_certs="cert", cert_reqs=ssl.CERT_REQUIRED) # ssl wrapper for socket
s.connect((TCP_IP, TCP_PORT)) # connect to server
if TRACE:
	print ("Connection to Server Established")
s.send(message.encode()) # encode the message to byte representation and send to server
if TRACE:
	print("Sent a request to the server.")
data_received = (s.recv(BUFFER_SIZE)).decode()  # Receive data from the server and decode it from bytes

#print the response of the server's local time
print("Server's response is:")
print (data_received)
s.close() # close socket
