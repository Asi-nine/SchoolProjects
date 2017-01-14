CS3319 ASSIGNMENT 3 README:

Firsly, I would like to apologize for how hacked together this is. It was done within a 36 hour period as I have been very busy.

This was done with Python3, Flask and mySQL, on Ubuntu using Vagrant.

*********************************************************************************************************************************
INSTRUCTIONS:
*********************************************************************************************************************************

1. 	Make sure to have the database up and running on your VM. Filename is 'movietheatre.sql'

2. 	Make sure Flask, and mysql.connector for Python3 are installed on your VM.

3. 	After making sure the database is built and other requirements are installed, navigate to the directory containing the file
	'movietheatre.py' on your VM and execute:
	
								python3 movietheatre.py

4. 	Open your web browser on your local machine and navigate to the page (edit the last line of 'movietheatre.py' if you need to 
	change IPs). For me this was '192.168.33.10:5000' but I have changed the value to 0.0.0.0, so you may be able to use 
	localhost or something. Either way, if you cannot connect make sure that your vagrantfile is forwarding the proper port 
	and modify the IP in 'movietheatre.py' as needed if you want to use a private IP as well.

*********************************************************************************************************************************
POTENTIALLY USEFUL COMMANDS/EDITS
*********************************************************************************************************************************

sudo apt-get install python3-flask 

sudo apt-get install python3-mysql.connector

python3 movietheatre.py

mysql -u root < movietheatre.sql 

*** Line 582 in 'movietheatre.py' *** Edit the IP here as needed ***
  app.run(host="0.0.0.0", debug=True)

*** Creating private IPs or port forwarding in your vagrantfile ***
  config.vm.network "forwarded_port", guest: 22, host: 5000
  config.vm.network "private_network", ip: "192.168.33.10"



*********************************************************************************************************************************
FOR FUTURE IMPROVEMENTS:
*********************************************************************************************************************************

1.	The user searching could use improvement. There are some bugs here, and its functionality may not be 100%.

2. 	Error detection is lacking in a lot of places and coule be improved upon.

3.	Proper authentication system for customers and staff.