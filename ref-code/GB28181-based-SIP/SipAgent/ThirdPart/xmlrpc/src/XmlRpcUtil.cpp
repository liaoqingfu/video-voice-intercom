
#include "XmlRpcUtil.h"

#ifndef MAKEDEPEND
# include <ctype.h>
# include <iostream>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
#ifndef _WINDOWS
# include <sys/time.h>
#endif
#endif

#include "XmlRpc.h"

using namespace XmlRpc;

#if defined(_WINDOWS)
//#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <syslog.h>
#endif

// Version id
const char XmlRpc::XMLRPC_VERSION[] = "XMLRPC++ 0.8";

// Default log verbosity: 0 for no messages through 5 (writes everything)
int XmlRpcLogHandler::_verbosity = 3;
int XmlRpcLogHandler::_monitor = 1;
ExtendPrintf XmlRpcLogHandler::extendPrintf = NULL;

// don't use epoll by default.
bool XmlRpc::_epoll = false;

void XmlRpc::setUseEpoll(){ XmlRpc::_epoll = true; }
bool XmlRpc::isUseEpoll() { return XmlRpc::_epoll; }

// Easy API for log verbosity
int XmlRpc::getVerbosity() { return XmlRpcLogHandler::getVerbosity(); }
void XmlRpc::setVerbosity(int level) { XmlRpcLogHandler::setVerbosity(level); }
int XmlRpc::getMonitor() { return XmlRpcLogHandler::getMonitor(); }
void XmlRpc::setMonitor(int monitor) { XmlRpcLogHandler::setMonitor(monitor); }
ExtendPrintf XmlRpc::getExtendPrintf() { return XmlRpcLogHandler::getExtendPrintf(); }
void XmlRpc::setExtendPrintf(ExtendPrintf pFun) { XmlRpcLogHandler::setExtendPrintf(pFun); }
 

void XmlRpcUtil::log(int level, const char* fmt, ...)
{
  if (level <= XmlRpcLogHandler::getVerbosity())
  {     
        va_list args;
        char    buf[1024], *p = buf;
        int n;
        va_start(args, fmt);
        n = vsnprintf(p, sizeof(buf)-3, fmt, args); // buf-3 is room for CR/LF/NUL
        va_end(args);

        n = ((n > 0) && (n < 1021)) ? n :  1021;
        p += n;
        while ( p > buf  &&  isspace(p[-1]) ) *--p = '\0';
        *p++ = '\r';
        *p++ = '\n';
        *p   = '\0';

        if((getMonitor() & 1) == 1)
        {
#ifdef _WINDOWS
          OutputDebugString(buf);
#else
          char tmstamp[24];
          struct timeval tv;
          gettimeofday(&tv, NULL);
          time_t t = tv.tv_sec;
          int tn = strftime(tmstamp, sizeof(tmstamp), "%T.", localtime(&t));
          sprintf(tmstamp+tn, "%06lu ",  tv.tv_usec);

          // 如果设置了外部的日志输出函数,则调用
          if(getExtendPrintf() != NULL)
          {
            ExtendPrintf pFun = getExtendPrintf();
            buf[strlen(buf)-2] = '\0';  // 最后的\r \n \0 三个字符不要
            pFun(level, 0, __FILE__, __FUNCTION__, __LINE__, buf); // 这中间三个宏不能反应真实的日志源信息
          }
          else
          {
            fprintf(stdout, "%s [%d:%x] %s", tmstamp, getpid(), (unsigned int)pthread_self(), buf);
            // std::cout << tmstamp << "[" << getpid() << ":" << std::hex << pthread_self() << "]" << std::dec << buf;
          }


#endif
        }

        if((getMonitor() & 2) == 2)
        {
#ifdef _WINDOWS
            OutputDebugString(buf);
#else
            buf[n] = '\0';
		        syslog(LOG_DEBUG, buf, n); 
#endif 
        }

  }
}


void XmlRpcUtil::error(const char* fmt, ...)
{
        va_list args;
        char    buf[1024], *p = buf;
        int n;
        va_start(args, fmt);
        n = vsnprintf(p, sizeof(buf)-3, fmt, args); // buf-3 is room for CR/LF/NUL
        va_end(args);

        n = ((n > 0) && (n < 1021)) ? n :  1021;
        p += n;
        while ( p > buf  &&  isspace(p[-1]) ) *--p = '\0';
        *p++ = '\r';
        *p++ = '\n';
        *p   = '\0';
//
        if((getMonitor() & 1) == 1)
        {
#ifdef _WINDOWS
            OutputDebugString(buf);
#else
          // 如果设置了外部的日志输出函数,则调用
          if(getExtendPrintf() != NULL)
          {
            ExtendPrintf pFun = getExtendPrintf();
            buf[strlen(buf)-2] = '\0';  // 最后的\r \n \0 三个字符不要
            pFun(3, 0, __FILE__, __FUNCTION__, __LINE__, buf); // 这中间三个宏不能反应真实的日志源信息
          }
          else
          {
            fprintf(stdout, "%s", buf);
            // std::cerr << buf;
          }
          

#endif 
        }

        if((getMonitor() & 2) == 2)
        {
#ifdef _WINDOWS
            OutputDebugString(buf);
#else
            buf[n] = '\0';
		   //     syslog(LOG_ERR, "%s", buf); 
		        syslog(LOG_WARNING, buf, n); 
#endif 
        }

}


// Returns contents between <tag> and </tag>, updates offset to char after </tag>
std::string 
XmlRpcUtil::parseTag(const char* tag, std::string const& xml, int* offset)
{
  if (*offset >= int(xml.length())) return std::string();
  size_t istart = xml.find(tag, *offset);
  if (istart == std::string::npos) return std::string();
  istart += strlen(tag);
  std::string etag = "</";
  etag += tag + 1;
  size_t iend = xml.find(etag, istart);
  if (iend == std::string::npos) return std::string();

  *offset = int(iend + etag.length());
  return xml.substr(istart, iend-istart);
}


// Returns true if the tag is found and updates offset to the char after the tag
bool 
XmlRpcUtil::findTag(const char* tag, std::string const& xml, int* offset)
{
  if (*offset >= int(xml.length())) return false;
  size_t istart = xml.find(tag, *offset);
  if (istart == std::string::npos)
    return false;

  *offset = int(istart + strlen(tag));
  return true;
}


// Returns true if the tag is found at the specified offset (modulo any whitespace)
// and updates offset to the char after the tag
bool 
XmlRpcUtil::nextTagIs(const char* tag, std::string const& xml, int* offset)
{
  if (*offset >= int(xml.length())) return false;
  const char* cp = xml.c_str() + *offset;
  int nc = 0;
  while (*cp && isspace(*cp)) {
    ++cp;
    ++nc;
  }

  int len = int(strlen(tag));
  if  (*cp && (strncmp(cp, tag, len) == 0)) {
    *offset += nc + len;
    return true;
  }
  return false;
}

// Returns the next tag and updates offset to the char after the tag, or empty string
// if the next non-whitespace character is not '<'
std::string 
XmlRpcUtil::getNextTag(std::string const& xml, int* offset)
{
  if (*offset >= int(xml.length())) return std::string();

  size_t pos = *offset;
  const char* cp = xml.c_str() + pos;
  while (*cp && isspace(*cp)) {
    ++cp;
    ++pos;
  }

  if (*cp != '<') return std::string();

  std::string s;
  do {
    s += *cp;
    ++pos;
  } while (*cp++ != '>' && *cp != 0);

  *offset = int(pos);
  return s;
}



// xml encodings (xml-encoded entities are preceded with '&')
static const char  AMP = '&';
static const char  rawEntity[] = { '<',   '>',   '&',    '\'',    '\"',    0 };
static const char* xmlEntity[] = { "lt;", "gt;", "amp;", "apos;", "quot;", 0 };
static const int   xmlEntLen[] = { 3,     3,     4,      5,       5 };


// Replace xml-encoded entities with the raw text equivalents.

std::string 
XmlRpcUtil::xmlDecode(const std::string& encoded)
{
  std::string::size_type iAmp = encoded.find(AMP);
  if (iAmp == std::string::npos)
    return encoded;

  std::string decoded(encoded, 0, iAmp);
  std::string::size_type iSize = encoded.size();
  decoded.reserve(iSize);

  const char* ens = encoded.c_str();
  while (iAmp != iSize) {
    if (encoded[iAmp] == AMP && iAmp+1 < iSize) {
      int iEntity;
      for (iEntity=0; xmlEntity[iEntity] != 0; ++iEntity)
	//if (encoded.compare(iAmp+1, xmlEntLen[iEntity], xmlEntity[iEntity]) == 0)
	if (strncmp(ens+iAmp+1, xmlEntity[iEntity], xmlEntLen[iEntity]) == 0)
        {
          decoded += rawEntity[iEntity];
          iAmp += xmlEntLen[iEntity]+1;
          break;
        }
      if (xmlEntity[iEntity] == 0)    // unrecognized sequence
        decoded += encoded[iAmp++];

    } else {
      decoded += encoded[iAmp++];
    }
  }
    
  return decoded;
}


// Replace raw text with xml-encoded entities.

std::string 
XmlRpcUtil::xmlEncode(const std::string& raw)
{
  std::string::size_type iRep = raw.find_first_of(rawEntity);
  if (iRep == std::string::npos)
    return raw;

  std::string encoded(raw, 0, iRep);
  std::string::size_type iSize = raw.size();

  while (iRep != iSize) {
    int iEntity;
    for (iEntity=0; rawEntity[iEntity] != 0; ++iEntity)
      if (raw[iRep] == rawEntity[iEntity])
      {
        encoded += AMP;
        encoded += xmlEntity[iEntity];
        break;
      }
    if (rawEntity[iEntity] == 0)
      encoded += raw[iRep];
    ++iRep;
  }
  return encoded;
}

#ifdef _WINDOWS
#else
int 
XmlRpcUtil::getLock(pthread_mutex_t *mutex)
{
  int res = pthread_mutex_lock(mutex);
  if (res != 0) {
    XmlRpcUtil::log(3, "pthread_mutex_lock return an error code %d", res);
    return -1;
  }

  return 0;
}

int 
XmlRpcUtil::freeLock(pthread_mutex_t *mutex)
{
  int res = pthread_mutex_unlock(mutex);
  if(res != 0) {
    XmlRpcUtil::log(3, "pthread_mutex_unlock return an error code %d", res);
    return -1;
  }
  return 0;
}
#endif


// End

