#pragma once

#include "core.h"
#include "strings.h"

function void ExitProcess(S32 exit_code);

typedef struct Socket Socket;
struct Socket
{
	S32 file_descriptor;
};

function Socket SocketConnect(String address, U16 port);
function Socket SocketListen(U16 port);
function Socket SocketAccept(Socket socket);
function String SocketRead(Socket socket);
function void SocketWrite(Socket socket, String message);
function void SocketClose(Socket socket);

function void EntryPoint(StringArray arguments);
