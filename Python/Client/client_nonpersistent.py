'''
Computer Networks - Assignment 1
Client end code for Non-Persistent File Transfer through Socket
'''

#---IMPORTS-----
import socket                   
import time

# User input for number of files

file_count = int (raw_input ("Enter number of files to get: "))
files = []

for i in range (file_count):
    
	# Indivdual entries for names of files to get

	file = raw_input ("Enter file " + str(i+1) + " to get : ")
	files.append(file)

# time count to see transfer time

start_time = time.time()

for filename in files:
	'''
	Iteration for each file to transfer
	'''

	# Connection Establising

	soc = socket.socket()       
	soc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
      
	HOST = ""
	PORT = 6666         

	soc.connect((HOST, PORT))

	soc.send(filename)
	
	# Flag to check if file is present
	flag = soc.recv(1024)
	
	# Handling of case where file is not present
	if flag == 'No':
	    print (filename + " file does not exist")
	    continue

	# If file is present then proceed with transfer
	with open(filename, 'wb') as f:
	    print 'File Opened'
	    while True:
	        print('receiving data...')
	        file_data = soc.recv(1024)
	        if not file_data:
	            break
	        f.write(file_data)

	f.close()

	print('File recieved Successfully')
	soc.close()
	print('Connection closed')

print("Transfer Time : " + str(time.time() - start_time))
