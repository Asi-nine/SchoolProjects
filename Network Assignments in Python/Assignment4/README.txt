README FOR UDP_Server.py AND UDP_Client.py

SETTINGS:

UDP_IP is the ip address for both server and client (make sure this is the same on both, ideally 127.0.0.1, the loopback address)

UDP_PORT is the port of the file you are working on. Make these distinct between the files. 

UDP_PORT_CLIENT is the port of the client the server will respond to

UDP_PORT_SERVER is the port of the server the client will send to

unpacker represents a struct


INSTRUCTIONS:

**Note that all tests were run in linux Mint running a 64-bit Ubuntu kernel for both the server and client and using python3**

1. Set the UDP_IP and UDP_PORT to be used in both files. MAKE SURE THE CLIENT AND SERVER ARE ON DIFFERENT PORTS BUT THE SAME IP!
2. Set UDP_PORT_CLIENT to the UDP_PORT of the client file and the UDP_PORT_SERVER to the UDP_PORT of the server file.
3. Place the files in a directory of your choice on your machine.
4. Open two terminals and change to that directory in command line in both. 
5  Execute 'sudo tc qdisc add dev lo root netem delay 10ms reorder 50% 50% loss 40%' on either terminal
6. Execute 'python3 UDP_Server.py' on the first and then 'python3 UDP_Client.py' on the second. 
7. The server and client should communicate.
8. Execute 'sudo tc qdisc del root dev lo' on either terminal


USEFUL COMMANDS:

 	python3 UDP_Server.py		will launch the server, which waits for a client to communicate with it
	python3 UDP_Client.py		will launch the client and attempt sending packets to the server and wait for the responses
	CTRL+C 						will close the server with a keyboard interrupt (can use on client too if you end up looping)
	
	sudo tc qdisc add dev lo root netem delay 10ms reorder 50% 50% loss 40%				Introduces dropped packets and packet delay.
	sudo tc qdisc del root dev lo														Undoes the previous command.

