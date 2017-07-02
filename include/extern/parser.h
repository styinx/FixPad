#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "define.h"
#include "app/application.h"

namespace EXTERN
{
	struct Config
    {
    	string 				caption = "";
    	map<string, string> kvp;

		string 				getValue(string key);
		int 				getValueAsInt(string key);
		void 				setValue(string key, string value);
    	bool 				isEmpty();
    };

    struct XML
    {
    	XML 			  * parent = nullptr;
    	XML				  * prev = nullptr;
    	string 				tag = "";
    	string 				content = "";
    	bool 				lineTag = false;
    	map<string, string> kvp;
    	vector<XML> 		children;
    	XML				  * next = nullptr;

		string 				getValue(string key);
		int 				getValueAsInt(string key);
		void 				setValue(string key, string value);
		static XML			findXML(XML xml, string tag, int type);
		static XML			findXML(XML xml, string tag);
		vector<XML> 		getChildren();
		XML					getXML(string tag);
    	bool 				isEmpty();
    	void				printXML();
    };

    class Directory
	{
	private:
		DIR * currdir;
		list<string> dirs;
		list<string> files;

	public:
		Directory(string dir);
		bool isDir(string name);
		bool isFile(string name);
		static string getFileContents(string name);
		list<string> getDirs();
		list<string> getFiles();
		~Directory();
	};

	/**
	*** Parser
	***
	***
	**/
	template<class T>
	class Parser
	{
	private:
		string filename;

	public:
		APP::Timer 	timer;
		fstream handle;
		Parser(string file){this->filename = file;};
		virtual T 			read(string file = "") = 0;
		virtual bool 		write(string file, T value, string extra = "") = 0;
		~Parser(){};
	};

	/**
	*** XMLParser
	***
	***
	**/
	class XMLParser : public Parser<XML>
	{
	private:
		XML start;

	public:
		XMLParser(string file);
		bool 				hasTags(string line);
		bool 				isEndTag(string line);
		bool 				isTagLine(string line);
		bool 				isStartTag(string line);
		string 				capTags(string line);
		string 				parseTag(string line);
		map<string, string> parseKVP(string line);
		XML 				parseLine(fstream & stream, string buffer = "");
		XML 				read(string file = "");
		bool 				write(string file, XML xml, string prepend = "");
		~XMLParser();
	};

	/**
	*** INIParser
	***
	***
	**/
	class INIParser : public Parser<Config>
	{
	private:
		map<string, map<string, string>> dict;

	public:
		INIParser(string file);
		Config 							read(string file = "");
		bool 							write(string file, Config config);
		map<string,map<string, string>> getDict();
		Config 							getSection(string caption);
		~INIParser();
	};
}

#endif // PARSER_H_INCLUDED
