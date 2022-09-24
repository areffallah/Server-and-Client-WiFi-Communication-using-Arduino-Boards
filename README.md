# Server-and-Client-WiFi-Communication-using-Arduino-Boards
The idea is to create a server and a client using Arduino Boards. Data will be communicated as a string message. Server requests data from client and in response client sends the requested data to the server via WiFi. Then, server processes data and responds to client accordingly after performing some analysis.

# Instructions
The codes for Server and client has to be uploaded seperately to two Arduino Boards. This can be done using Arduino IDE or any other compatible IDEs such as VSCode.
Once two boards are powered up, Server establishes a WiFi network and listens for client's connection request. Client connects to server by submitting the authentication credintials. Once connection between client and server is established, they are able to transfer messages as text strings. This text message can be replaced by sensor's data and analysis results.

# Nex Steps
Creating a multi-client connection allows the server to receive data from multiple devices, perform the analysis, and control various actuators.
