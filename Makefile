all: Server Client

Server: UDPServer.c 
	gcc UDPServer.c -o Server

Client: UDPEchoClient.c
	gcc UDPEchoClient.c -o Client

clean:
	rm Client
	rm Server
