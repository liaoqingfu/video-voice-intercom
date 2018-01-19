// FileClient.cpp : A simple xmlrpc client. Usage: FileClient serverHost serverPort xmlfile
// Reads an xmlrpc request from the specified xmlfile and calls the method on the server.
// 
// Link against xmlrpc lib and whatever socket libs your system needs (ws2_32.lib on windows)

#include "XmlRpc.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace XmlRpc;

std::string parseRequest(std::string const& xml, XmlRpcValue& params);

#define SYSTEM_DFT_USER     "server"
#define SYSTEM_DFT_PASSWD   "cf1e8c14e54505f60aa10ceb8d5d8ab3"
#define USER_ACTOR_NORMAL   (1)    // 普通用户,客户端登录时使用
#define USER_ACTOR_CENTER   (1<<1) // 中心用户,
#define USER_ACTOR_ACCESS   (1<<2) // 门禁用户
#define USER_ACTOR_SYSTEM   (1<<3) // 系统内部用户

int main(int argc, char* argv[])
{
  if (argc < 4) {
    std::cerr << "Usage: FileClient serverHost serverPort requestXmlFile [LOGIN]\n";
    return -1;
  }
  int port = atoi(argv[2]);

  XmlRpc::setVerbosity(5);
  XmlRpcClient c(argv[1], port);
  c.setWaitTimeout(2);

  
  // 如果指定了login,则先登录
  if(argc == 5 && strcasecmp(argv[4], "login") == 0)
  {
    XmlRpcValue params, result;
    params["name"] = SYSTEM_DFT_USER;
    params["password"] = SYSTEM_DFT_PASSWD;  // 密码由调用者保证是MD5后的
    params["actor"] = USER_ACTOR_SYSTEM;
    if (c.execute("Security.Session.login", params, result))
    {
      if (c.isFault())
      {
        std::cout << "login failed:\n" << result << std::endl;
        return -1;
      }
    }
    else
    {
      std::cout << "Error calling 'Security.Session.login'\n\n";
      return -1;
    }
  }
  


  std::ifstream infile(argv[3]);
  if (infile.fail()) {
    std::cerr << "Could not open file '" << argv[3] << "'.\n";
    return -1;
  }

  // Suck in the file. This is a one-liner in good compilers (which vc++ 6 is not)...
  infile.seekg(0L, std::ios::end);
  long nb = infile.tellg();
  infile.clear();
  infile.seekg(0L);
  char* b = new char[nb+1];
  infile.read(b, nb);
  b[nb] = 0;

  std::cout << "Read file.\n";

  // Find the methodName and parse the params
  std::string s(b);
  XmlRpcValue params;
  std::string name = parseRequest(s, params);

  if (name.empty()) {
    std::cerr << "Could not parse file\n";
    return -1;
  }

  for (;;) {
    XmlRpcValue result;
    std::cout << "Calling " << name << std::endl;
    if (c.execute(name.c_str(), params, result))
      std::cout << "------------------------- Result --------------------------\n" << result << "\n\n";
    else
      std::cout << "Error calling '" << name << "'\n\n";
    std::cout << "Again? [y]: ";
    std::string ans;
    // continue;
    
    /*
      退出程序;
    */
    return 0;

    std::cin >> ans;
    if (ans != "" && ans != "y") break;
  }

  return 0;
}


// 
std::string
parseRequest(std::string const& xml, XmlRpcValue& params)
{
  const char METHODNAME_TAG[] = "<methodName>";
  const char PARAMS_TAG[] = "<params>";
  const char PARAMS_ETAG[] = "</params>";
  const char PARAM_TAG[] = "<param>";
  const char PARAM_ETAG[] = "</param>";

  int offset = 0;   // Number of chars parsed from the request

  std::string methodName = XmlRpcUtil::parseTag(METHODNAME_TAG, xml, &offset);
  XmlRpcUtil::log(3, "XmlRpcServerConnection::parseRequest: parsed methodName %s.", methodName.c_str()); 

  if (! methodName.empty() && XmlRpcUtil::findTag(PARAMS_TAG, xml, &offset))
  {
    int nArgs = 0;
    while (XmlRpcUtil::nextTagIs(PARAM_TAG, xml, &offset)) {
      std::cout << "Parsing arg " << nArgs+1 << std::endl;
      XmlRpcValue arg(xml, &offset);
      if ( ! arg.valid()) {
        std::cerr << "Invalid argument\n";
        return std::string();
      }
      std::cout << "Adding arg " << nArgs+1 << " to params array." << std::endl;
      params[nArgs++] = arg;
      (void) XmlRpcUtil::nextTagIs(PARAM_ETAG, xml, &offset);
    }

    XmlRpcUtil::log(3, "XmlRpcServerConnection::parseRequest: parsed %d params.", nArgs); 

    (void) XmlRpcUtil::nextTagIs(PARAMS_ETAG, xml, &offset);
  }

  return methodName;
}
