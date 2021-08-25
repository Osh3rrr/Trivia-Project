#include "Communicator.h"

Communicator::Communicator()
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");

	m_handlerFactory = new RequestHandlerFactory();
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(m_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	bindAndListen();
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET to use TCP protocl, AF_INET - Family of TCP protocol.
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will always use "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		accept();
	}
}

void Communicator::accept()
{
	SOCKET client_socket = ::accept(m_serverSocket, NULL, NULL); // accepting the client, the saving the client socket in var.

	if (client_socket == INVALID_SOCKET) // if there is an error with the client socket.
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	// The function below handles the conversation with the client
	std::thread clientHandlerThread(&Communicator::handleNewClient, this, client_socket);
	clientHandlerThread.detach();

	LoginRequestHandler* newLoginReq = m_handlerFactory->createLoginRequestHandler(this->m_handlerFactory); // creating new login request
	this->m_clients[client_socket] = new LoginRequestHandler(*newLoginReq); // adding the client socket and the request to the dict.
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	bool isLogged = false;
	RequestResult res;
	RequestInfo info;
	int msg_len = 0;

	try
	{
		while (true)
		{
			info.id = Helper::getMessageTypeCode(clientSocket); // that's will give us the type code of the message (login/signup/error etc...)

			time_t my_time = time(NULL); // declare a time var
			info.recivalTime = ctime(&my_time); // ctime() used to give the present time

			msg_len = Helper::getIntPartFromSocket(clientSocket, MSG_LEN); //Get the length of the message
			info.buffer = (char*)malloc(sizeof(char) * msg_len); // allocating memory for the msg data by the msg length.
			strcpy(info.buffer, (char*)Helper::getStringPartFromSocket(clientSocket, msg_len).c_str()); // copying the message data to the buffer.

			std::cout << info.buffer << std::endl;

			if (this->m_clients.at(clientSocket)->isRequestRelevant(info)) // cheking if the request is relevant.
			{
				res = this->m_clients.at(clientSocket)->handleRequest(info); // sending the request to the handle functin.
				this->m_clients.at(clientSocket) = res.newHandler;
			}

			else // if the request is not relevent, we should return error.
			{
				ErrorResponse response;
				std::vector<unsigned char> buff = JsonResponsePacketSerializer::serializeResponse(response);
				Helper::sendData(clientSocket, std::string(buff.begin(), buff.end()));
			}
			

			std::string sendBuff(res.response.begin(), res.response.end());
			Helper::sendData(clientSocket, sendBuff);
		}
		closesocket(clientSocket); // end of the conversation, closing the socket.
	}

	catch (const std::exception& e)
	{
		closesocket(clientSocket);
	}
}


