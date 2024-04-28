// TODO(luna):
// - replace malloc with arena memory management
// - better error handling
// - logging using os_log
// - multiple networking backends (sockets + kqueue, sockets + Dispatch, Network.framework)
// - pass port on CLI
// - pass server address on CLI

#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "core.h"
#include "strings.h"
#include "os.h"

#include "strings.c"
#include "os.c"

function void
Server(void)
{
	Socket listener = SocketListen();

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
Client(void)
{
	Socket socket = SocketConnect();
	SocketWrite(socket, StringLit("i am the impostor"));
	String response = SocketRead(socket);
	printf("from server: %.*s\n", StringVArg(response));
	SocketClose(socket);
}

function void
EntryPoint(StringArray arguments)
{
	if (arguments.count > 2)
	{
		printf("too many arguments\n");
		ExitProcess(1);
	}

	if (arguments.count < 2)
	{
		printf("usage: filevent [mode]\n");
		ExitProcess(1);
	}

	String mode = arguments.strings[1];

	if (StringMatch(mode, StringLit("server")))
	{
		Server();
		return;
	}

	if (StringMatch(mode, StringLit("client")))
	{
		Client();
		return;
	}

	printf("unknown mode “%.*s”.\n", StringVArg(mode));
	printf("try “server” or “client”.\n");
	ExitProcess(1);
}
