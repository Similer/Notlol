

#include <iostream>
#include <tchar.h>

using namespace std;

void* operator new(size_t sz)
{
	cout << "operator new" << endl;
	return malloc(sz);
}

void operator delete(void* p)   // 어떤 형이 올지 모르니 void* 형
{
	cout << "operator delete" << endl;
	free(p);
}


#include "ticpp.h"




void Parse(const char* pcFilename)
{
	// first load the xml file
	
	ticpp::Document doc(pcFilename);
	doc.LoadFile();

	// parse through all fruit elements
	ticpp::Iterator<ticpp::Element> child;
	for(child = child.begin(doc.FirstChildElement()); child != child.end(); child++)
	{
		// The value of this child identifies the name of this element
		std::string strName;
		std::string strValue;
		child->GetValue(&strName);
		std::cout << "fruit: " << strName << std::endl;
		std::cout << "-------------" << std::endl;

		// now parse through all the attributes of this fruit
		ticpp::Iterator< ticpp::Attribute > attribute;
		for(attribute = attribute.begin(child.Get()); attribute != attribute.end();
			attribute++)
		{
			attribute->GetName(&strName);
			attribute->GetValue(&strValue);
			std::cout << strName << ": " << strValue << std::endl;
		}
		std::cout << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	Parse("fruits.xml");

	
	return 0;
}

