# UDP Server following RDT 2.2
# Author: Peter Valovcik
# November 11, 2016

import binascii
import socket
import struct
import sys
import hashlib

UDP_IP = "127.0.0.1"
UDP_PORT = 5006
UDP_PORT_SERVER = 5005
unpacker = struct.Struct('I I 32s')


print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT_SERVER)

#make a function to create a checksum based on given code for both client and server checksums
def createChecksumClient(ack, seq, data):
	values = (ack, seq, data.encode())
	UDP_Data = struct.Struct('I I 8s')
	packed_data = UDP_Data.pack(*values)
	chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")
	return chksum;

def createChecksumServer(ack, seq):
    values = (ack, seq)
    UDP_Data = struct.Struct('I I')
    packed_data = UDP_Data.pack(*values)
    chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")
    return chksum;    

#made a function to create a UDP packet based on given code, since it's neater.
def createUDPPacketClient(ack, seq, data, chksum):
	values = (ack, seq, data.encode(), chksum)
	UDP_Packet_Data = struct.Struct('I I 8s 32s')
	UDP_Packet = UDP_Packet_Data.pack(*values)
	return UDP_Packet;

#create the packets to be sent
chksum1 = createChecksumClient(0,0,'NCC-1701')
UDP_Packet1 = createUDPPacketClient(0,0,'NCC-1701',chksum1)

chksum2 = createChecksumClient(0,1,'NCC-1664')
UDP_Packet2 = createUDPPacketClient(0,1,'NCC-1664',chksum2)

chksum3 = createChecksumClient(0,0,'NCC-1017')
UDP_Packet3 = createUDPPacketClient(0,0,'NCC-1017',chksum3)

#store the packets in a list
UDP_Packets = (UDP_Packet1, UDP_Packet2, UDP_Packet3)

#set up the client socket since we will need to listen for responses from the server
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
  # Set timeout to 9 ms
sock.bind((UDP_IP, UDP_PORT))

#Want to have a counter corresponding to which packet we are sending
packetNumber = 1
CurrentSEQ = 0
#keep attempting to send packets as long as there are some left in the packet list
while packetNumber < len(UDP_Packets) + 1:
    print("*********************************************************************")
    #get the current packet and send it
    print("Sending Packet Number:", packetNumber)
    currentPacket = UDP_Packets[packetNumber-1]
    currentUnpack = struct.Struct('I I 8s 32s')
    print("Sending Message:", currentUnpack.unpack(currentPacket))
    sock.sendto(currentPacket, (UDP_IP, UDP_PORT_SERVER))
    sock.settimeout(0.009)
    try:
        #Receive Data
        data, addr = sock.recvfrom(1024) #buffer size is 1024 bytes
        UDP_Packet_From_Server = unpacker.unpack(data)
        print("received from:", addr)
        print("received message:", UDP_Packet_From_Server)
        #Create the Checksum for comparison
        chksum = createChecksumServer(UDP_Packet_From_Server[0],UDP_Packet_From_Server[1])
        #Compare Checksums to test for corrupt data and the SEQ vs SEQ
        currentTemp = currentUnpack.unpack(currentPacket)
        sentSEQ = currentTemp[1]
        if UDP_Packet_From_Server[2] == chksum and UDP_Packet_From_Server[1] == sentSEQ:
            #move onto the next packet if the packet was receieved properly by the server
            print('CheckSums Match, Packet OK')
            #inform user if the next packet will be sent or if all have been sent
            if packetNumber == len(UDP_Packets):
                print('All Packets Successfully Sent!')
            else:
                print('Sending Next')
            packetNumber=packetNumber+1
        elif UDP_Packet_From_Server[2] != chksum or UDP_Packet_From_Server[1] != sentSEQ:
            #resend the packet if it was not received properly by the server (loops back to start) 
            if UDP_Packet_From_Server[1] != sentSEQ:
                print('Sequence number mismatch, resending')
            else:
                print('Checksums Do Not Match, Packet Corrupt, Resending')
    except socket.timeout:
        print('Packet timeout, Resending')

