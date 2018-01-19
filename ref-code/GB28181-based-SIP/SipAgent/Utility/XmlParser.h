#ifndef _DDCPXMLPARSE_H
#define _DDCPXMLPARSE_H


#include <string>
#include "tinyxml.h"

const int max_title = 64;

#define XMLTITLE  "<?xml version=\"1.0\"?>\n"


/*实现以下几个功能:
1 xml文件格式头
2 添加一个根节点
3 给某个节点添加一个子节点 附带: value、attributes、itemname...
4 返回整个xml字符串 char*

5 解析-得到某个节点的值和attribute
*/


struct attributes
{
	std::string attrName;
	std::string attrVal;
};

class XmlParser
{
public:
	XmlParser(void);
	~XmlParser(void);

public:
	//添加根节点
	TiXmlElement* AddRootNode(char* rootName);
	//在一个节点下插入多个子节点
	TiXmlElement* InsertSubNode(char* parentNode, char* itemName, char* textValue);
	//在制定node节点下插入子节点
	TiXmlElement* InsertSubNode(TiXmlElement* parentNode, char* itemName, const char* textValue);

	TiXmlElement* GetSubNode(TiXmlElement* node, const char* item);
	TiXmlElement* GetNextSiblingNode(TiXmlElement* node, const char* value);
	//属性操作
	void SetNodeAttributes(TiXmlElement* node, char* attributeItem, char* attributeTextValue);
	void GetNodeAttributes(TiXmlElement* node, std::string& attributes);

public:
	//解析xml,得到整个xml string
	void getWholeXml(char* xmlBuf, int size, int* actualLen);
  //解析得到某个节点的值和attribute
	void  ParseNode(char* nodeName, std::string& textValue);
	void  ParseNode(TiXmlElement* node, std::string& textValue);
  //解析一段字符串
	int   ParseDocumentXml(char* parseContent);

	void SetXmlTile(char* title);

	int SaveXmlFile(char* fileName);

	int LoadFile(char* fileName, int encoding = 1);

	TiXmlElement* GetRootNode() { if (m_document != NULL) return m_document->RootElement(); }


private:
	//在某个节点下深度查找指定子节点
	TiXmlElement* NodeFind(const char* value, TiXmlElement* node);

private:
	TiXmlDocument* m_document;
	TiXmlElement*  m_rootElement;

	char  m_xmlTitle[max_title];
};



#endif

