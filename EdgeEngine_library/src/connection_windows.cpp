#define POCO_WIN32_UTF8
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <iostream>
#include "connection_windows.h"

using namespace Poco::Net;
using namespace Poco;
using namespace std;

connection_windows* connection_windows::instance=NULL;

connection_windows* connection_windows::getInstance(){
  if(instance==NULL){
    instance= new connection_windows();
  }
  return instance;
}

connection_windows::connection_windows(){
    connected=false;
}

bool connection_windows::isConnected() {
    try
    {
        // prepare session
        URI uri("https://www.google.com");
        HTTPClientSession session(uri.getHost(), uri.getPort());

        // prepare path
        string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";

        // send request
        HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
        session.sendRequest(req);

        connected = true;

        cout << "You're connected" << endl;

        return connected;        
    }
    catch (Exception &ex)
    {
        // cerr << "Error: " << ex.displayText() << endl;
        cout << "You're not connected" << endl;
        connected = false;
        return connected;
    }
}

void connection_windows::reconnect() {
  string ack;
  while (!connected)
  {
      cout << "It seems that you don't have any internet connection, please establish one, then press any button and Enter" << endl;
      cin >> ack;
      isConnected();
  }
  cout << "You're now connected" << endl;
}

