# Networking Chat Program
Networking Chat Programm is a Hello World project for the C++ networking library.
The aim of the project is to create a server and a client program, which will be able to communicate with each other. 
The combination of the two will create a chat system where multiple clients can connect to the server and chat with each other in designated rooms.

### How to build
To save memory, the folder doesn't contain a solution file and/or bin and bin-int folder. Premake5 is integrated into the project and is responsible for building the necessary files. 
Clicking the 'GenerateFiles' WBF (Windows Batch File) will open the command prompt and run Premake5. This will generate the required files, after which the user can click any button to close the command prompt.
A solution file should appear in the folder, which can be opened. This project already contains all the necessary links and project settings. Building the solution will generate a client and server executable inside the bin folder. 

### Project structure
All the code written for this project can be found in the src folders. ([TwoNet](Vendor/TwoNet/src), [Client](Chat_Client/src), [Server](Chat_Server/src)) 
The project is split into the following modules, grouped by project:

##### TwoNet Lib
- **Buffer**: The buffer is responsible for serializing data into a byte array. The data in this buffer is used to transfer over the network.
- **Protocol**: The protocol makes sure the data is correctly ordered and serialized in the buffer. Data shouldn't be put in the buffer directly but should pass the protocol first.
- **Response**: The generic response for failed or successful requests.

##### Server
- **NetworkServer**: Responsible for connection, socket management, and listening for data.
- **Commands**: Commands determine which action will be performed, based on the command string added to the data. These commands will forward the data to the right class and retrieve data.
- **Rooms**: The rooms class keeps track of chat messages, and connected clients and will run methods based on certain events.
- **Room manager**: The room manager will keep track of existing rooms and the addition and removal of rooms.

##### Client
- **Client**: The client is responsible for direct connection with the server. It is able to send and receive messages.
- **Networking**: The networking class is an API to send data and execute a callback on receiving data. Methods will safely forward data to the client.
- **StateManager**: Keeps track of the current state and updates the currently active state.

### Using the solution
After building the projects successfully, both the client and server should be booted up. The server does not need human interaction. The client asks for a name. Do NOT leave this empty. Entering a space and clicking enter will automatically generate a name. From here, any room can be joined. To chat, just write a message and hit enter. To leave a room, type x and hit enter.

### Known limitations
- Entering an empty name on the client side will crash the program.
- Sockets will not be deleted upon sudden client disconnection on the server side.
- A simple error on the server side could crash the whole server instead of just throwing an error.

### Evaluation
I am somewhat proud of the project. I think some modules are decent, but others contain a lot of unnecessary dependencies and are not well abstracted. Especially the server side feels like a mess which is hard to expand upon and add new functionality. The same for the client side, where we queue requests instead of sending them with an ID to reference them back to a callback function or something. The TwoNet library is something I think worked out pretty well! Especially in combination with the protocol. I think it's all right for a first networking project and I'll take everything I've learned with me to future projects. 











