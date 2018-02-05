'''
Computer Networks - Assignment 1
Server end code for Persistent File Transfer through Socket
'''

#---IMPORTS-----
import socket

#---CONSTANTS---
PORT = 6666
HOST = ""

# Socket Creation

soc = socket.socket()
soc.bind((HOST, PORT))
soc.listen(5)

print 'The Server is listening'

conn, addr = soc.accept()
while True:
    print 'Connection Established with Client'
    filename = conn.recv(1024)
    print ('Request Recieved for : '+filename)

    # Handling Request
    try:
        f = open('./Data/'+filename,'rb')

    # In case of non-existence of file
    except IOError:
        conn.send('No')
        print "\nERROR HANDLING : " + filename +\
         " file is not present with the server\n"
        flag = 1
        continue
    
    conn.send('Yes')

    # File Transfer when file is present
    l = f.read(1024)
    while (l):
       conn.send(l)
       l = f.read(1024)
    f.close()
    print('Done sending')
conn.close()
