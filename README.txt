Subject : "The game must request the opponent's address to connect with him"

Different message type :
	- connect
	- disconnect
	- invite
	- accept
	- deny

	- coordinates
	- success
	- error

Server must handle multiple connections :
	- http://broux.developpez.com/articles/c/sockets/#
	- http://www.binarytides.com/server-client-example-c-sockets-linux/
	- https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/

	- Set a number max of clients
	- link clients between them (1vs1)
	- Server manage message
		- receive / send message from one player to another
	- Client manage message
		- Hit : replace X by x
		- Miss : do anything