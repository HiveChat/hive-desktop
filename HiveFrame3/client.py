import socket

def Main():
		host = '127.0.0.1'
		port = 5000

		dest_addr=(host,23233)
		
		mySocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
		mySocket.bind((host,port))
		
		message = input(" -> ")
		
		while True:
				print ('h')

				mySocket.sendto("hello", dest_addr)
				data = mySocket.recv(1024)

				
				print ('Received from server: ' + data)
								
		mySocket.close()

if __name__ == '__main__':
	Main()
