#include "all.h"

#include "core.c"
#include "strings.c"
#include "os.c"

function void
Server(StringArray arguments)
{
	if (arguments.count != 3)
	{
		printf("usage: filevent server [port]\n");
		ExitProcess(1);
	}

	U16 port = (U16)atoi((char *)arguments.strings[2].data);
	Socket listener = SocketListen(port);

	Socket client1 = SocketAccept(listener);
	Socket client2 = SocketAccept(listener);

	SocketWrite(client1, StringFromStruct(&client2));
	SocketWrite(client2, StringFromStruct(&client1));
	SocketClose(client1);
	SocketClose(client2);
	SocketClose(listener);
}

function void
Client(StringArray arguments)
{
	if (arguments.count != 4)
	{
		printf("usage: filevent client [address] [port]\n");
		ExitProcess(1);
	}

	U16 port = (U16)atoi((char *)arguments.strings[3].data);
	Socket socket = SocketConnect(arguments.strings[2], port);

	String response = SocketRead(socket);
	Socket peer = {0};
	MemoryCopyStruct(&peer, response.data);

	printf("peer %d:%d\n", peer.address, peer.port);
	SocketClose(socket);
}

function void
EntryPoint(StringArray arguments)
{
	if (arguments.count < 2)
	{
		printf("usage: filevent [mode]\n");
		ExitProcess(1);
	}

	String mode = arguments.strings[1];

	if (StringMatch(mode, StringLit("server")))
	{
		Server(arguments);
		return;
	}

	if (StringMatch(mode, StringLit("client")))
	{
		Client(arguments);
		return;
	}

	printf("unknown mode “%.*s”.\n", StringVArg(mode));
	printf("try “server” or “client”.\n");
	ExitProcess(1);
}
