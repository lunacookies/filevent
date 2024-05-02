#include "all.h"

function void
ExitProcess(S32 exit_code)
{
	exit(exit_code);
}

function Socket
SocketConnect(String address, U16 port)
{
	Socket result = {0};

	result.file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (result.file_descriptor < 0)
	{
		perror("failed to open socket");
		ExitProcess(1);
	}

	struct sockaddr_in server_address = {0};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = inet_addr((char *)address.data);

	if (connect(result.file_descriptor, (struct sockaddr *)&server_address,
	            sizeof(server_address)) < 0)
	{
		perror("failed to connect socket");
		ExitProcess(1);
	}

	return result;
}

function Socket
SocketListen(U16 port)
{
	Socket result = {0};
	result.file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (result.file_descriptor < 0)
	{
		perror("failed to open socket");
		ExitProcess(1);
	}

	struct sockaddr_in server_address = {0};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = INADDR_ANY;

	if (bind(result.file_descriptor, (struct sockaddr *)&server_address,
	            sizeof(server_address)) < 0)
	{
		perror("failed to bind socket");
		ExitProcess(1);
	}

	if (listen(result.file_descriptor, 5) < 0)
	{
		perror("failed to listen on socket");
		ExitProcess(1);
	}

	return result;
}

function Socket
SocketAccept(Socket socket)
{
	struct sockaddr_in client_address = {0};
	socklen_t client_address_size = sizeof(client_address);

	Socket client = {0};
	client.file_descriptor = accept(
	        socket.file_descriptor, (struct sockaddr *)&client_address, &client_address_size);
	if (client.file_descriptor < 0)
	{
		perror("failed to accept connection");
		ExitProcess(1);
	}

	return client;
}

function String
SocketRead(Socket socket)
{
	String result = {0};
	U32 length = 0;

	if (read(socket.file_descriptor, &length, sizeof(length)) < 0)
	{
		perror("failed to read message length");
		ExitProcess(1);
	}

	result.count = length;
	result.data = malloc(result.count);

	if (read(socket.file_descriptor, result.data, result.count) < 0)
	{
		perror("failed to read message contents");
		ExitProcess(1);
	}

	return result;
}

function void
SocketWrite(Socket socket, String message)
{
	U32 length = (U32)message.count;

	if (write(socket.file_descriptor, &length, sizeof(length)) < 0)
	{
		perror("failed to write message length");
		ExitProcess(1);
	}

	if (write(socket.file_descriptor, message.data, message.count) < 0)
	{
		perror("failed to write message contents");
		ExitProcess(1);
	}
}

function void
SocketClose(Socket socket)
{
	close(socket.file_descriptor);
}

S32
main(S32 argument_count, char **arguments_c_string)
{
	StringArray arguments = {0};
	arguments.count = (U64)argument_count;
	arguments.strings = calloc(arguments.count, sizeof(String));

	for (U64 i = 0; i < arguments.count; i++)
	{
		String argument = StringFromCString(arguments_c_string[i]);
		arguments.strings[i] = argument;
	}

	EntryPoint(arguments);
}
