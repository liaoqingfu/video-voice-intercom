#include "XmlParser.h"

XmlParser::XmlParser(void)
{
	m_document = new TiXmlDocument();
	m_rootElement = NULL;

//	m_xmlTitle = new char[max_title];

}

XmlParser::~XmlParser(void)
{
	if (m_document != NULL)
	{
		delete m_document;
		m_document = NULL;
	}

/*
	delete []m_xmlTitle;
	m_xmlTitle = NULL;*/

}


//添加根节点
TiXmlElement* XmlParser::AddRootNode(char* rootName)
{
	m_rootElement = new TiXmlElement(rootName);
	if (m_document != NULL)
	{
		m_document->LinkEndChild(m_rootElement);
	}

	return m_rootElement;
}


TiXmlElement* XmlParser::InsertSubNode(TiXmlElement* parentNode, char* itemName, 
																					const char* textValue)
{
	if (m_rootElement == NULL || parentNode == NULL)
		return NULL;
	TiXmlElement* insertNode = NULL;

	insertNode = new TiXmlElement(itemName);
	parentNode->LinkEndChild(insertNode);

	//设置文字字符串
	if (strlen(textValue) != 0)
	{
		TiXmlText* txt = new TiXmlText(textValue);
		insertNode->LinkEndChild(txt);
	}

	return insertNode;

}


//在一个节点下插入多个子节点
TiXmlElement* XmlParser::InsertSubNode(char* parentNode, char* itemName, 
																					char* textValue)
{
	if (m_rootElement == NULL)
		return NULL;
	TiXmlElement* insertNode = NULL;
	TiXmlElement* findNode = NULL;
	if (strcmp(m_rootElement->Value(), parentNode) == 0)
	{
		findNode = m_rootElement;
	}
	else
	{
		findNode = NodeFind(parentNode, m_rootElement);
		if (findNode == NULL)
			return NULL;
	}

	insertNode = new TiXmlElement(itemName);
	findNode->LinkEndChild(insertNode);
	//设置文字字符串
	if (strlen(textValue) != 0)
	{
		TiXmlText* txt = new TiXmlText(textValue);
		insertNode->LinkEndChild(txt);
	}

	return insertNode;
}


//设置属性
void XmlParser::SetNodeAttributes(TiXmlElement* node, char* attributeItem, char* attributeTextValue)
{
	if (node == NULL)
		return ;

	node->SetAttribute(attributeItem, attributeTextValue);
}



//解析xml
void XmlParser::getWholeXml(char* xmlBuf, int size, int* actualLen)
{
	if (xmlBuf == NULL)
		return ;
	TiXmlPrinter printer;
	if (m_document != NULL)
	{
		m_document->Accept(&printer);
		*actualLen = printer.Size() + strlen(m_xmlTitle);
		//bool bw = m_document->SaveFile("DdcpXml.xml");
		if (size > *actualLen)
		{
			if (strlen(m_xmlTitle) != 0)
				strcpy_s(xmlBuf, size, m_xmlTitle); //添加xml头
			strcat_s(xmlBuf, size, (char*)printer.CStr());
		}
	}

}



int XmlParser::ParseDocumentXml(char* parseContent)
{
	if (m_document == NULL || parseContent == NULL)
		return -1;
	if (m_document->Parse(parseContent) == NULL)
		return 0/*-1*/;

	return 0;
}

TiXmlElement* XmlParser::GetSubNode(TiXmlElement* node, const char* item)
{
	TiXmlElement* findNode;
	if (m_document != NULL)
	{
		if (node == NULL)
			findNode = NodeFind(item, m_document->RootElement());
		else
			findNode = NodeFind(item, node);
		return findNode;
	}
	
	return NULL;
}

TiXmlElement* XmlParser::GetNextSiblingNode(TiXmlElement* node, const char* value)
{
	if (node != NULL)
	{
		return node->NextSiblingElement(value);
	}
	return NULL;
}


void XmlParser::SetXmlTile(char* title)
{
	memcpy_s(m_xmlTitle, sizeof(m_xmlTitle), title, sizeof(m_xmlTitle));
}


//

//解析得到某个节点的值和attribute
void  XmlParser::ParseNode(char* nodeName, std::string& textValue)
{
	if (m_document != NULL)
	{
		TiXmlElement* findNode = NodeFind(nodeName, m_document->RootElement());
		if (findNode == NULL)
			return ;
		//节点值
		char* pch = (char*)findNode->GetText();
		if (pch != NULL)
			textValue = pch;
	}
}


void XmlParser::ParseNode(TiXmlElement* node, std::string& textValue)
{
	if (node != NULL)
	{
		char* pch = (char*)node->GetText();
		if (pch != NULL)
			textValue = pch;
	}
}


void XmlParser::GetNodeAttributes(TiXmlElement* node, std::string& attributes)
{
	if (node == NULL)
		return ;
  char* pch = (char*)node->Attribute(attributes.c_str());
	if (pch != NULL)
		attributes = pch;
}



//deep find 
TiXmlElement* XmlParser::NodeFind(const char* value, TiXmlElement* node)
{
	TiXmlElement* findNode;
	if (node == NULL)
		return NULL;

	TiXmlElement* child = (TiXmlElement*)node->FirstChildElement();
	while(child != NULL)
	{
		char* name = (char*)child->Value();
		if (strcmp(name, value) == 0)
			return child;

		findNode = NodeFind(value, child);
		if (findNode != NULL)
			return findNode;

		child = child->NextSiblingElement();
	}

	return NULL;
}


int XmlParser::SaveXmlFile(char* fileName)
{
	int result = 0;
	if (m_document->SaveFile(fileName))
		result = 0;
	else
		result = -1;

	return result;
}


int XmlParser::LoadFile(char* fileName, int encoding)
{
	int result = 0;
	if (m_document->LoadFile(fileName))
		result = 0;
	else
		result = -1;
	
	return result;
}
