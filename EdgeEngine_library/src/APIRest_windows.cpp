#include "APIRest_windows.h"

using namespace Poco::Net;
using namespace Poco;
// using namespace std;

APIRest_windows *APIRest_windows::instance = NULL;

APIRest_windows *APIRest_windows::getInstance()
{
  if (instance == NULL)
  {
    instance = new APIRest_windows();
  }
  return instance;
}
// constructor
APIRest_windows::APIRest_windows()
{
  reposting = false;
}

string APIRest_windows::POSTLogin(string url, string username, string password, string tenant)
{
  try{
    Poco::Net::initializeSSL();
    Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> ptrHandler = new AcceptCertificateHandler(false);
    Context::Ptr ptrContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    SSLManager::instance().initializeClient(0, ptrHandler, ptrContext);

    Poco::Net::SocketAddress address("students.measurify.org:443");
    Poco::Net::SecureStreamSocket socket(address);
    if (socket.havePeerCertificate())
    {
        X509Certificate cert = socket.peerCertificate();
        std::cout<<cert.issuerName()<<"\n"; 
    }
    else
    {
        std::cout<<"No certificate";
    }

  } 
  catch (Poco::Exception& e) {
    std::cout << "Error: " << e.displayText() << "\n";
    return "";
  }

  cout << "LOGGING IN..." << endl;
  // prepare session
  URI uri(url);
  HTTPSClientSession session(uri.getHost(), uri.getPort());
  session.setKeepAlive(true);

  // prepare path
  string path(uri.getPathAndQuery());
  if (path.empty())
    path = "/";

  // send request
  HTTPRequest req(HTTPRequest::HTTP_POST, path, "HTTP/1.1");
  req.setContentType("application/json");

  // set the body
  string body = "{\"username\": \"" + username + "\",\"password\": \"" + password + "\",\"tenant\": \"" + tenant + "\"}";
  req.setContentLength(body.length());

  req.setKeepAlive(true);
 
  ostream &os = session.sendRequest(req);
  os << body;           // sends the body

  req.write(std::cout); // print out request

  // get response
  HTTPResponse res;

  cout << res.getStatus() << " " << res.getReason() << endl;
  istream &is = session.receiveResponse(res);
  // StreamCopier::copyStream(is, cout);
  response = "";
  StreamCopier::copyToString(is, response);
  // itoa(res.getStatus(), status, 10);
  sprintf(status, "%d", res.getStatus());
  response = string(status) + response;
  cout << "RESPONSE:" << endl;
  cout << response << endl;
  // cout << isHTTPCodeOk(res.getStatus()) << endl;
  if (!isHTTPCodeOk(res.getStatus()))
  { //Check for the returning code
    cout << "[HTTPS] POST Login... failed, error: " + res.getStatus() << " " << res.getReason() << endl;
    // if(res.getStatus() < 0)
    //   response = response + " error: " + res.getReason();
  }
  session.abort();
  return response;
}

string APIRest_windows::GETInfoUpdateDate(string url, string token)
{
  // prepare session
  URI uri(url);
  HTTPSClientSession session(uri.getHost(), uri.getPort());

  // prepare path
  string path(uri.getPathAndQuery());
  if (path.empty())
    path = "/";

  // send request
  HTTPRequest req(HTTPRequest::HTTP_GET, path, "HTTP/1.1");
  req.add("Authorization", token.c_str());
  session.sendRequest(req);

  // get response
  HTTPResponse res;
  cout << res.getStatus() << " " << res.getReason() << endl;
  // print response
  response = "";
  istream &is = session.receiveResponse(res);
  StreamCopier::copyToString(is, response);
  // itoa(res.getStatus(), status, 10);
  sprintf(status, "%d", res.getStatus());
  response = string(status) + response;
  cout << "RESPONSE:" << endl;
  cout << response << endl;

  if (isHTTPCodeOk(res.getStatus()))
  {                                                            //Check for the returning code
    startingTime = ((float)clock() / CLOCKS_PER_SEC) * SECOND; //milliseconds
    timestamp = parseResponse(response, "timestamp");
  }
  else
  {
    cout << "[HTTPS] POST Login... failed, error: " + res.getStatus() << " " << res.getReason() << endl;
  }
  session.abort();
  return response;
}

string APIRest_windows::GETDescr(string url, string token)
{
  // prepare session
  URI uri(url);
  HTTPSClientSession session(uri.getHost(), uri.getPort());

  // prepare path
  string path(uri.getPathAndQuery());
  if (path.empty())
    path = "/";

  // send request
  HTTPRequest req(HTTPRequest::HTTP_GET, path, "HTTP/1.1");
  req.add("Authorization", token.c_str());
  session.sendRequest(req);

  // get response
  HTTPResponse res;
  cout << res.getStatus() << " " << res.getReason() << endl;
  // print response
  response = "";
  istream &is = session.receiveResponse(res);
  StreamCopier::copyToString(is, response);
  // itoa(res.getStatus(), status, 10);
  sprintf(status, "%d", res.getStatus());
  response = string(status) + response;
  cout << "RESPONSE:" << endl;
  cout << response << endl;

  if (!isHTTPCodeOk(res.getStatus()))
  { //Check for the returning code
    cout << "[HTTPS] POST Login... failed, error: " + res.getStatus() << " " << res.getReason() << endl;
    // if(res.getStatus() < 0)
    //   response = response + " error: " + res.getReason();
  }
  session.abort();
  return response;
}

string APIRest_windows::GETScript(string url, string token)
{
  // prepare session
  URI uri(url);
  HTTPSClientSession session(uri.getHost(), uri.getPort());

  // prepare path
  string path(uri.getPathAndQuery());
  if (path.empty())
    path = "/";

  // send request
  HTTPRequest req(HTTPRequest::HTTP_GET, path, "HTTP/1.1");
  req.add("Authorization", token.c_str());
  session.sendRequest(req);

  // get response
  HTTPResponse res;
  cout << res.getStatus() << " " << res.getReason() << endl;
  // print response
  response = "";
  istream &is = session.receiveResponse(res);
  StreamCopier::copyToString(is, response);
  // itoa(res.getStatus(), status, 10);
  sprintf(status, "%d", res.getStatus());
  response = string(status) + response;
  cout << "RESPONSE:" << endl;
  cout << response << endl;

  if (!isHTTPCodeOk(res.getStatus()))
  { //Check for the returning code
    cout << "[HTTPS] POST Login... failed, error: " + res.getStatus() << " " << res.getReason() << endl;
    // if(res.getStatus() < 0)
    //   response = response + " error: " + res.getReason();
  }
  session.abort();
  return response;
}

bool APIRest_windows::POSTMeasurement(sample sam, string token)
{
  // prepare session
  URI uri(sam.url.c_str());
  HTTPSClientSession session(uri.getHost(), uri.getPort());

  // prepare path
  string path(uri.getPathAndQuery());
  if (path.empty())
    path = "/";

  // send request
  HTTPRequest req(HTTPRequest::HTTP_POST, path, "HTTP/1.1");
  req.setContentType("application/json");
  req.add("Authorization", token.c_str());

  // set the body
  string body = ("{\"thing\": \"" + sam.thing + "\", \"feature\": \"" + sam.feature + "\", \"device\": \"" + sam.device + "\", \"script\": \"" + sam.scriptId + "\", \"samples\": {\"values\":" + to_string(sam.value) + "}, \"startDate\": \"" + sam.startDate + "\", \"endDate\": \"" + sam.endDate + "\"}").c_str();
  req.setContentLength(body.length());

  ostream &os = session.sendRequest(req);
  os << body;           // sends the body
  req.write(std::cout); // print out request

  // get response
  HTTPResponse res;
  cout << res.getStatus() << " " << res.getReason() << endl;
  istream &is = session.receiveResponse(res);
  // StreamCopier::copyStream(is, cout);
  response = "";
  StreamCopier::copyToString(is, response);
  // itoa(res.getStatus(), status, 10);
  sprintf(status, "%d", res.getStatus());
  response = string(status) + response;

  if (isHTTPCodeOk(res.getStatus()))
  { //Check for the returning code
    success = true;
  }
  else
  { // something has gone wrong in the POST
    if (needToBeRePOST(response))
    {
      checkSampleBufferSize();     //if there is not space, make it
      sampleBuffer.push_back(sam); // save the datum in a local sampleBuffer
      cout << "[HTTPS] POST NewMeas... failed";
      cout << ", value: ";
      cout << sam.value;
      cout << ", script: ";
      cout << sam.scriptId.c_str() << endl;
      success = false;
    }
    else
    {
      success = true; // if don't need to be resent
      cout << "Measurement aleady POSTed";
    }
  }
  cout << "RESPONSE:" << endl;
  cout << response << endl;
  session.abort();

  if (!reposting)
  {
    reposting = true;
    rePOSTMeasurement(token); // every time we post a new measurement retry to post all the failed ones
  }
  if (!reposting)
  {
    reposting = true;
    // rePOSTIssue(token); // every time we post a new measurement retry to post all the failed alerts
  }

  return success;
}

bool APIRest_windows::POSTIssue(string url, string token, string device, string message, string type, string date)
{
  // prepare session
  URI uri(url);
  HTTPSClientSession session(uri.getHost(), uri.getPort());

  // prepare path
  string path(uri.getPathAndQuery());
  if (path.empty())
    path = "/";

  // send request
  HTTPRequest req(HTTPRequest::HTTP_POST, path, "HTTP/1.1");
  req.setContentType("application/json");
  req.add("Authorization", token.c_str());

  // set the body
  string body = ("{\"device\": \"" + device + "\",  \"date\": \"" + date + "\", \"message\": \"" + message + "\",\"type\": \"" + type + "\"}").c_str();
  req.setContentLength(body.length());

  ostream &os = session.sendRequest(req);
  os << body;           // sends the body
  req.write(std::cout); // print out request

  // get response
  HTTPResponse res;
  cout << res.getStatus() << " " << res.getReason() << endl;
  istream &is = session.receiveResponse(res);
  // StreamCopier::copyStream(is, cout);
  response = "";
  StreamCopier::copyToString(is, response);
  // itoa(res.getStatus(), status, 10);
  sprintf(status, "%d", res.getStatus());
  response = string(status) + response;

  if (isHTTPCodeOk(res.getStatus()))
  { //Check for the returning code
    success = true;
  }
  else
  { // something has gone wrong in the POST
    if (needToBeRePOST(response))
    {
      issue al;
      al.date = date;
      al.device = device;
      al.message = message;
      al.type = type;
      al.url = url;

      checkIssueBufferSize(); //if there is not space, make it
      // if the post has encoutered an error, we want to save datum that will be resent as soon as possible
      issueBuffer.push_back(al); // save the datum in a local sampleBuffer

      cout << "[HTTPS] POST Issue... failed";

      success = false;
    }
    else
    {
      cout << "Issue aleady POSTed";
      success = true; // if don't need to be resent
    }
  }
  cout << "RESPONSE:" << endl;
  cout << response << endl;
  session.abort();

  return success;
}

void APIRest_windows::rePOSTIssue(string token)
{
  // j is useful to count the number of iteration equal to Buffer size;
  // since after repost the first element we erase it, the next one shift to the first position so access issueBuffer[0] till end
  int size = issueBuffer.size();
  for (int j = 0; j < size; j++)
  {
    POSTIssue(issueBuffer[0].url, token, issueBuffer[0].device, issueBuffer[0].message, issueBuffer[0].type, issueBuffer[0].date);
    issueBuffer.erase(issueBuffer.begin()); // don't need to deallocate every issue individually because we passed the struct and not the pointer
  }
  vector<issue>(issueBuffer).swap(issueBuffer); // this create a new Buffer with capacity equal to the size, that frees memory
  reposting = false;
}

string APIRest_windows::getActualDate()
{
  timeElapsed = ((float)clock() / CLOCKS_PER_SEC) * SECOND - startingTime; //in milliseconds
  return string(to_string(atof(timestamp.c_str()) + timeElapsed));
}

int APIRest_windows::getSampleBufferSize()
{ // no usage
  return sampleBuffer.size();
}
int APIRest_windows::getIssueBufferSize()
{ // no usage
  return issueBuffer.size();
}

void APIRest_windows::setSampleBufferSize(int size)
{ // usage in edgine.cpp
  // if(size<sampleBuffer.size()){ [TBD]
  //Call the correct policy
  // }
  if (size < sampleBuffer.size())
  {
    sampleBuffer.erase(sampleBuffer.begin(), sampleBuffer.begin() + (sampleBuffer.size() - size));
    vector<sample>(sampleBuffer).swap(sampleBuffer); // this create a new Buffer with capacity equal to the size, that frees memory allocated with the erased issue
  }
  sampleBufferSize = size;
  sampleBuffer.reserve(size); //useful if (size>sampleBuffer.size()) in other cases it does nothing, no need of "if clause"
}

void APIRest_windows::setIssueBufferSize(int size)
{ // usage in edgine.cpp
  if (size < issueBuffer.size())
  {
    issueBuffer.erase(issueBuffer.begin(), issueBuffer.begin() + (issueBuffer.size() - size)); // don't need to delete every issue individually because we passed the struct and not the pointer
    vector<issue>(issueBuffer).swap(issueBuffer);                                              // this create a new Buffer with capacity equal to the size, that frees memory allocated with the erased issue
  }
  issueBufferSize = size;
  issueBuffer.reserve(size); //useful if (size>issueBuffer.size()) in other cases it does nothing, no need of "if clause"
}

bool APIRest_windows::isHTTPCodeOk(int code)
{
  return code >= 200 && code <= 308;
}

string APIRest_windows::parseResponse(string response, string fieldName, bool quotedField)
{
  deleteSpaces(response);
  if (response.find(fieldName) == -1)
  {
    cout << fieldName.c_str();
    cout << " field is not present!" << endl;
    return "";
  }
  int beginOfValue = response.find(":", response.find(fieldName)) + 1; //find starting index of field value
  int endOfValue;
  string fieldValue;

  if (quotedField)
  {                                                     // example "fieldName": "fieldValue"
    endOfValue = response.find('\"', beginOfValue + 1); // start looking for the last delimiter from the next value
    fieldValue = response.substr(beginOfValue + 1, endOfValue - (beginOfValue + 1));
  }
  else
  {                                                // example "fieldName": fieldValue
    endOfValue = response.find(',', beginOfValue); // start looking for the last delimiter from the next value
    if (response.at(endOfValue - 1) == '}' || response.at(endOfValue - 1) == ']')
    { // if the field is the last of the a JSON objects({...}) or JSON array([...])
      endOfValue -= 1;
    }
    else if (endOfValue == -1)
    { //if the object is the last of response
      endOfValue = response.find('}', beginOfValue);

      if (endOfValue == -1)
      { //if the array is the last of response
        endOfValue = response.find(']', beginOfValue);
      }
    }
    fieldValue = response.substr(beginOfValue, endOfValue - beginOfValue);
  }
  return fieldValue;
}

void APIRest_windows::deleteSpaces(string str)
{
  int pos = 0;
  while ((pos = str.find(" ")) != -1)
  {
    str.erase(pos, 1); //delete whitespace
  }
}

bool APIRest_windows::needToBeRePOST(string response)
{
  if (parseResponse(response, "value", false) == "6")
  { // "value"= 6 means that the resource was not created for some problem(usually because it already exists), so do not try create it again
    return false;
  }
  return true;
}

void APIRest_windows::checkSampleBufferSize()
{ // usage 2x inside this class
  if (sampleBufferSize <= sampleBuffer.size() - (reposting ? 1 : 0))
  { //if the rePOSTing of a sample fails, when this check is done the sample is already at the begin of sampleBuffer,
    // so do not take into account its presence (so sampleBuffer.size()-1), beacuse the sample will be deleted from the begin of the queue and added back to the end.
    // [TBD]
    // don't need to deallocate every sample individually because we passed the struct and not the pointer
    sampleBuffer.erase(sampleBuffer.begin(), sampleBuffer.begin() + sampleBufferSize / decimationPolicyFactor); //delete sampleBufferSize/decimationPolicyFactor sample
    vector<sample>(sampleBuffer).swap(sampleBuffer);                                                            // this create a new Buffer with capacity equal to the size, that frees memory allocated with the erased samples
  }
}

void APIRest_windows::rePOSTMeasurement(string token)
{ // usage inside this class 2x
  // j is useful to count the number of iteration equal to sampleBuffer size;
  // since after repost the first element we erase it, the next one shift to the first position so access sampleBuffer[0] till end
  int size = sampleBuffer.size();
  for (int j = 0; j < size; j++)
  {
    POSTMeasurement(sampleBuffer[0], token);
    sampleBuffer.erase(sampleBuffer.begin());
  }
  vector<sample>(sampleBuffer).swap(sampleBuffer); // this create a new sampleBuffer with capacity equal to the size

  reposting = false;
}

void APIRest_windows::checkIssueBufferSize()
{ // usage 2x inside this class
  if (issueBufferSize <= issueBuffer.size() - (reposting ? 1 : 0))
  { //if the rePOSTing of an issue fails, when this check is done the issue is already at the begin of issueBuffer,
    // so do not take into account its presence (so issueBuffer.size()-1), beacuse the issue will be deleted from the begin of the queue and added back to the end.
    // don't need to deallocate every issue individually because we passed the struct and not the pointer
    issueBuffer.erase(issueBuffer.begin(), issueBuffer.begin() + issueBufferSize / decimationPolicyFactor); //delete issueBufferSize/decimationPolicyFactor issue
    vector<issue>(issueBuffer).swap(issueBuffer);                                                           // this create a new Buffer with capacity equal to the size, that frees memory allocated with the erased issues
  }
}