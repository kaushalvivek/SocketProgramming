'''
Computer Networks - Assignment 1
Client end code for Persistent File Transfer through Socket
'''

#---IMPORTS-----
import time
import socket                   

# Connection Established

soc = socket.socket()             
HOST = ""
PORT = 6666

soc.connect((HOST, PORT))

# Input from user for number of files and names

file_count = int(raw_input("Enter No. of files to transfer : "))
files = []

for i in range(file_count):
	file = raw_input("Enter file no. " + str(i + 1) + " to get : ")
	files.append(file)

# time saved to calculate transfer time
start_t = time.time()


for filename in files:

	soc.send(filename)

	# Flag to check if file is present
	flag = soc.recv(1024)
	
	# Handling of case where file is not present
	if flag == 'No':
	    print (filename + " file does not exist")
	    continue

	# If file is present then proceed with transfer
	with open(filename, 'wb') as f:
	    print 'file opened'
	    while True:
	        print('receiving data...')
	        file_data = soc.recv(1024)
	        f.write(file_data)
	        if len(file_data) < 1024:
	            break

	f.close()
	print('File Succesfully Transferred')
print ("Transfer Time : " + str(time.time() - start_t))

soc.close()
print('connection closed')
