# UDP Server following RDT 2.2
# Author: Peter Valovcik
# November 11, 2016

import binascii
import socket
import struct
import sys
import hashlib

UDP_IP = "127.0.0.1"
UDP_PORT = 5005
UDP_PORT_CLIENT = 5006
unpacker = struct.Struct('I I 8s 32s')

#make a function to create a checksum based on given code for both client and server checksums
def createChecksumClient(ack, seq, data):
    values = (ack, seq, data)
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

#make a function to create a UDP packet based on given code, since it's neater.
def createUDPPacketServer(ack, seq, chksum):
    values = (ack, seq, chksum)
    UDP_Packet_Data = struct.Struct('I I 32s')
    UDP_Packet = UDP_Packet_Data.pack(*values)
    return UDP_Packet;

#Create the socket and listen
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

#set starting sequence number
currentSEQ = 0
#loops forever, user needs to keyboard interrupt to stop it
while True:
    print('**************************************************************************')
    #Receive Data
    data, addr = sock.recvfrom(1024) #buffer size is 1024 bytes
    UDP_Packet_From_Client = unpacker.unpack(data)
    print("received from:", addr)
    print("received message:", UDP_Packet_From_Client)
    #Create the Checksum for comparison
    chksum = createChecksumClient(UDP_Packet_From_Client[0],UDP_Packet_From_Client[1],UDP_Packet_From_Client[2])

    #Compare Checksums to test for corrupt data and make sure that the correct sequence number was recieved
    if UDP_Packet_From_Client[3] == chksum and UDP_Packet_From_Client[1] == currentSEQ:
        #return an ACK and a checksum if the packet was received properly
        chksumReturn = createChecksumServer(1, currentSEQ)
        UDP_Packet = createUDPPacketServer(1, currentSEQ, chksumReturn)
        print('CheckSums Match, Packet OK, Sent ACK')
        sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT_CLIENT))
        currentSEQ = (currentSEQ + 1) % 2
    else:
        #return something that let's the client know the packet was not received properly
        seqRet = (currentSEQ + 1) % 2
        chksumReturn = createChecksumServer(1, currentSEQ)
        UDP_Packet = createUDPPacketServer(1, currentSEQ, chksumReturn)
        if UDP_Packet_From_Client[1] != currentSEQ:
            print('Sequence number mismatch')
        else:
            print('Checksums Do Not Match, Packet Corrupt')
        sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT_CLIENT))
