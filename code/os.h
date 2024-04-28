function void ExitProcess(S32 exit_code);

typedef struct Socket Socket;
struct Socket
{
	S32 file_descriptor;
};

function Socket SocketConnect(void);
function Socket SocketListen(void);
function Socket SocketAccept(Socket socket);
function String SocketRead(Socket socket);
function void SocketWrite(Socket socket, String message);
function void SocketClose(Socket socket);

function void EntryPoint(StringArray arguments);
