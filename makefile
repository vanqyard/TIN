all: bin/Server bin/Client

bin/Server: src/Daemon/UDPServer.c 
	gcc src/Daemon/UDPServer.c -o bin/Server

bin/Client: src/Downloader/UDPEchoClient.c
	gcc src/Downloader/UDPEchoClient.c -o bin/Client

clean:
	rm bin/Client
	rm bin/Server
