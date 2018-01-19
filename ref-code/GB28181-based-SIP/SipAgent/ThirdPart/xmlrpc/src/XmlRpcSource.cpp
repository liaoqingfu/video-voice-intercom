
#include "XmlRpcSource.h"
#include "XmlRpcSocket.h"
#include "XmlRpcUtil.h"

namespace XmlRpc {


  XmlRpcSource::XmlRpcSource(int fd /*= -1*/, bool deleteOnClose /*= false*/) 
    : _fd(fd), _deleteOnClose(deleteOnClose), _keepOpen(false)
  {
    XmlRpcSocket::initSock();
  }

  XmlRpcSource::~XmlRpcSource()
  {
    XmlRpcSocket::finiSock();
  }

  bool 
  XmlRpcSource::examine()
  {
    return XmlRpcSocket::examine(_fd); 
  }
  void 
  XmlRpcSource::flush()
  {
    return XmlRpcSocket::flush(_fd); 
  }


  void
  XmlRpcSource::close()
  {
    XmlRpcUtil::log(4,"XmlRpcSource::close: closing socket %d.", _fd);
    XmlRpcSocket::close(_fd);
    XmlRpcUtil::log(4,"XmlRpcSource::close: done closing socket %d.", _fd);
    _fd = -1;
    if (_deleteOnClose) {
      XmlRpcUtil::log(4,"XmlRpcSource::close: deleting this");
      _deleteOnClose = false;
      delete this;
    }
  }

} // namespace XmlRpc
