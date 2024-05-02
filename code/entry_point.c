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

	for (;;)
	{
		Socket client = SocketAccept(listener);
		String message = SocketRead(client);
		printf("from client: %.*s\n", StringVArg(message));
		SocketWrite(client, StringLit("i got your message"));
		SocketClose(client);
	}
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

	SocketWrite(socket, StringLit("i am the impostor"));
	String response = SocketRead(socket);
	printf("from server: %.*s\n", StringVArg(response));
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
