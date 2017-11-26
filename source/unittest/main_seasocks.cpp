#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/StringUtil.h"
#include "seasocks/WebSocket.h"
#include "seasocks/util/Json.h"

#include <cstring>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <ctime>

#include <boost/circular_buffer.hpp>

using namespace seasocks;
using namespace std;

class MyHandler: public WebSocket::Handler {
public:
    explicit MyHandler(Server* server) : _server(server) {
    }

    virtual void onConnect(WebSocket* connection) {
        _connections.insert(connection);
        cout << "Connected: " << connection->getRequestUri()
                << " : " << formatAddress(connection->getRemoteAddress())
                << endl;
        cout << "Credentials: " << *(connection->credentials()) << endl;
        
        for (auto s : cb_msgs) {
            connection->send(s);      // chat room
        }
    }

    virtual void onData(WebSocket* connection, const char* data) {
        if (0 == strcmp("die", data)) {
            _server->terminate();
            return;
        }
        if (0 == strcmp("close", data)) {
            cout << "Closing.." << endl;
            connection->close();
            cout << "Closed." << endl;
            return;
        }
        
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,sizeof(buffer),"%Y-%m-%d %I:%M:%S", timeinfo);
        std::string str(buffer);
        
        cb_msgs.push_back(str + "$ " + data);
        //cout << cb_msgs.capacity() << endl;
        //cout << cb_msgs.size() << endl;
        
        for (auto c : _connections) {
            c->send(str + "$ " + data);      // chat room
        }
    }

    virtual void onDisconnect(WebSocket* connection) {
        _connections.erase(connection);
        cout << "Disconnected: " << connection->getRequestUri()
                << " : " << formatAddress(connection->getRemoteAddress())
                << endl;
    }

private:
    set<WebSocket*> _connections;
    boost::circular_buffer<string> cb_msgs{20};     // save last 20 msgs
    Server* _server;
};

int main(int /*argc*/, const char* /*argv*/[]) {
    shared_ptr<Logger> logger(new PrintfLogger(Logger::Level::DEBUG));

    Server server(logger);

    shared_ptr<MyHandler> handler(new MyHandler(&server));
    server.addWebSocketHandler("/ws", handler);
    server.serve("web", 9090);
    return 0;
}