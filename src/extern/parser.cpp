#include "extern/parser.h"

using namespace EXTERN;

using std::stringstream;
using std::istringstream;
using std::istreambuf_iterator;

string Config::getValue(string key)
{
	return this->kvp[key];
}

int Config::getValueAsInt(string key)
{
	return atoi(this->kvp[key].c_str());
}

void Config::setValue(string key, string value)
{
	this->kvp[key] = value;
}

bool Config::isEmpty()
{
	bool success = false;

	if(this->caption == "" && this->kvp.size() == 0)
	{
		success = true;
	}
	return success;
}

string XML::getValue(string key)
{
	return this->kvp[key];
}

int XML::getValueAsInt(string key)
{
	return atoi(this->kvp[key].c_str());
}

void XML::setValue(string key, string value)
{
	this->kvp[key] = value;
}
/**
* @param type: 0 = BFS, 1 DFS
*/
XML XML::findXML(XML xml, string tag, int type)
{
	XML result;

	for(XML child : xml.children)
	{
		if(child.tag == tag)
		{
			result = child;
			break;
		}
		if(type == 1)
		{
			result = XML::findXML(child, tag, type);
			if(!result.isEmpty())
				break;
		}
	}
	return result;
}

XML XML::findXML(XML xml, string tag)
{
	XML result;
	if(xml.tag == tag)
		result = xml;
	else
	{
		for(XML child : xml.children)
		{
			if(child.tag == tag)
				result = child;
		}
		if(result.tag == "")
			for(XML child : xml.children)
			{
				if(result.tag == "")
					result = XML::findXML(child, tag);
			}
	}
	return result;
}

vector<XML> XML::getChildren()
{
	return this->children;
}

XML XML::getXML(string tag)
{
	XML xml;

	for(XML child : this->children)
	{
		if(child.tag == tag)
		{
			xml = child;
		}
	}
	this->next->getXML(tag);

	return xml;
}

bool XML::isEmpty()
{
	bool success = false;

	if(this->tag == "" && this->kvp.size() == 0 && this->children.size() == 0 &&
	   this->prev == nullptr && this->next == nullptr && this->parent == nullptr)
	{
		success = true;
	}
	return success;
}

void XML::printXML()
{
	cout << this->tag << "\n";
	for(XML child : this->children)
	{
		child.printXML();
	}
}

Directory::Directory(string directory)
{
	DIR   		  * dir 	= opendir(directory.c_str());
	struct dirent * entry;

	if(dir != NULL)
	{
		while((entry = readdir(dir)) != NULL)
		{
			string handle = entry->d_name;
			if(handle != "." && handle != "..")
			{
				if(this->isDir(handle))
				{
					this->dirs.push_back(handle);
				}
				else if(this->isFile(handle))
				{
					this->files.push_back(handle);
				}
			}
		}
	}
}

bool Directory::isDir(string name)
{
	bool success = false;
	DIR * dir = opendir(name.c_str());

	if(dir != NULL)
	{
		success = true;
	}
	return success;
}

bool Directory::isFile(string name)
{
	bool success = false;

	if(!this->isDir(name))
	{
		success = true;
	}
	return success;
}

string Directory::getFileContents(string name)
{
	ifstream ifs(name);
	string content = "";
	content.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	return content;
}

list<string> Directory::getDirs()
{
	return this->dirs;
}

list<string> Directory::getFiles()
{
	return this->files;
}

Directory::~Directory()
{

}

XMLParser::XMLParser(string file) : Parser(file)
{

}

bool XMLParser::hasTags(string line)
{
	if(line.find('<') != string::npos && line.find('>') != string::npos)
	{
		return true;
	}
	return false;
}

bool XMLParser::isEndTag(string line)
{
	string::size_type pos = line.find('/');
	if(pos == 0)
		return true;
	return false;
}

bool XMLParser::isTagLine(string line)
{
	string::size_type pos = line.find('/');
	if(pos > 0)
	{
		return true;
	}
	return false;
}

bool XMLParser::isStartTag(string line)
{
	if(!(line.find('/') != string::npos))
	{
		return true;
	}
	return false;
}

string XMLParser::capTags(string line)
{
	int tagOffset = line.find('<') + 1;
	return line.substr(tagOffset, line.find('>') - tagOffset);
}

string XMLParser::parseTag(string line)
{
	string tag = "";
	if(line.find(' ') != string::npos)
	{
		tag = line.substr(0, line.find(' '));
	}
	else
	{
		if(isEndTag(line))
			tag = line.substr(1, line.length() - 1);
	}
	return tag;
}

map<string, string> XMLParser::parseKVP(string line)
{
	map<string, string> kvp;

	while(line.find(' ') != string::npos)
	{
		string sub = line.substr(0, line.find(' '));

		if(sub.find('=') != string::npos)
		{
			string::size_type pos = sub.find('=');
			string key = sub.substr(0, pos);
			string value = sub.substr(pos + 2, sub.length() - (pos + 3));

			kvp.insert(pair<string, string>(key, value));
		}
		int subOffset = line.find(' ');
		line = line.substr(subOffset + 1, line.length() - subOffset);

	}

	if(line.find('=') != string::npos)
	{
		string::size_type pos = line.find('=');
		string key = line.substr(0, pos);
		string value;
		if(line.find('/') != string::npos || line.find('?') != string::npos)
			value = line.substr(pos + 2, line.length() - (pos + 4));
		else
			value = line.substr(pos + 2, line.length() - (pos + 3));
		kvp.insert(pair<string, string>(key, value));
	}

	return kvp;
}

/**
* Reads a xml file. If no head ('xml') tag is found the head tag will be empty.
*/
XML XMLParser::parseLine(fstream & stream, string buffer)
{
	XML xml;
	string line = buffer;

	while(getline(stream, line))
	{
		if(this->hasTags(line))
		{
			line = this->capTags(line);
			if(line.find("?xml") != string::npos)
			{
				xml.tag = "xml";
				xml.kvp = this->parseKVP(line);
			}
			else
			{
				if(this->isStartTag(line))
				{
					XML child = this->parseLine(stream, line);
					child.tag = this->parseTag(line);
					child.kvp = this->parseKVP(line);
					xml.children.push_back(child);

				}
				else if(this->isTagLine(line))
				{
					XML child;
					child.tag = this->parseTag(line);
					child.lineTag = true;
					child.kvp = this->parseKVP(line);
					xml.children.push_back(child);
				}
				else if(this->isEndTag(line))
				{
					return xml;
				}
			}
		}
		else
		{
			line.erase(remove(line.begin(), line.end(), '\t'), line.end());
			xml.content += line;
		}
	}
	return xml;
}

XML XMLParser::read(string file)
{
	XML doc;

    string line;
    fstream in(file, std::ios::in);

    XML head = this->parseLine(in, line);

	if(!head.isEmpty())
		doc = head;

	return doc;
}

bool XMLParser::write(string file, XML xml, string prepend)
{
	bool success = false;

	ofstream out(file, std::ios::out | std::ios::trunc);
    out << '<' << xml.tag;

    for(const auto & kvp : xml.kvp)
    {
        out << ' ' << kvp.first << '=' << '"' << kvp.second << '"';
    }

    if(xml.lineTag)
	{
		out << "/>" << endl;
	}
	else
	{
		out << '>' << endl;
		out.close();
		for(const auto & child : xml.children)
		{
			this->write(file, child, prepend + "\t");
		}
		ofstream out(file, std::ios::app | std::ios::ate);

		out << "</" << xml.tag << '>' << endl;
	}

	return success;
}

XMLParser::~XMLParser()
{

}

INIParser::INIParser(string file) : Parser(file)//, handle(file)
{

}

Config INIParser::read(string file)
{
	Config config;

    string line;
    ifstream in(file, std::ios::in);

    while(getline(in, line))
    {
        if(line.find('[') != string::npos)
        {
            string caption = line.substr(1, line.find(']')-1);

            while(getline(in, line) != NULL)
            {
                if(!line.empty())
                {
                    string option, value;
                    char equals;
                    istringstream ss(line);

                    ss >> option >> equals >> value;
                    this->dict[caption][option] = value;
                }
                else
                {
                    break;
                }
            }
        }
    }
	return config;
}

bool INIParser::write(string file, Config config)
{
	bool success = false;

	ofstream out(file, std::ios::app | std::ios::ate);
    out << '[' << config.caption << ']' << endl;
    success = true;

    for(const auto & kvp : config.kvp)
    {
        out << kvp.first << " = " << kvp.second << "\n";
    }

	return success;
}

map<string, map<string, string>> INIParser::getDict()
{
	return this->dict;
}

Config INIParser::getSection(string caption)
{
	Config config;

	if(!this->dict[caption].empty())
	{
		config.caption = caption;
		for(const auto & kvp : this->dict[caption])
		{
			config.kvp[kvp.first] = kvp.second;
		}
	}

	return config;
}

INIParser::~INIParser()
{

}