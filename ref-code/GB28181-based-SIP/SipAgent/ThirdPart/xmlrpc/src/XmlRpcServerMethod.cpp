
#include "XmlRpcServerMethod.h"
#include "XmlRpcServer.h"
#include "XmlRpcValue.h"

namespace XmlRpc {

XmlRpcServerMethod::XmlRpcServerMethod(std::string const& name, XmlRpcServer* server, bool needAuth)
{
    _name = name;
    _server = server;
    _needAuth = needAuth;
    _executor = NULL;
    if (_server) _server->addMethod(this);
}

XmlRpcServerMethod::XmlRpcServerMethod(XmlRpcServer* server, std::string const& name, Executor* executor, bool needAuth)
{
    _name = name;
    _server = server;
    _needAuth = needAuth;
    _executor = executor;
    if (_server) _server->addMethod(this);
}

XmlRpcServerMethod::~XmlRpcServerMethod()
{
    _executor = NULL;
    if (_server) _server->removeMethod(this);
}

void XmlRpcServerMethod::execute(XmlRpcValue& params, XmlRpcValue& result)
{
  if(_executor)
  {
     _executor(params[0], result);
  }
  
}

} // namespace XmlRpc


