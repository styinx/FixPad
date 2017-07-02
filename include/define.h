#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include "dirent.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <list>

using std::cout;
using std::string;
using std::endl;
using std::vector;
using std::map;
using std::list;
using std::pair;
using std::fstream;
using std::ifstream;
using std::ofstream;

using std::setw;
using std::right;
using std::left;

#include "QtCore/QObject"

#include "QtGui/QFont"
#include "QtGui/QFontMetrics"
#include "QtGui/QIcon"
#include "QtGui/QPixmap"
#include "QtGui/QTextDocument"
#include "QtGui/QSyntaxHighlighter"

#include "QtWidgets/QApplication"
#include "QtWidgets/QMainWindow"

#include "QtWidgets/QGridLayout"
#include "QtWidgets/QHBoxLayout"
#include "QtWidgets/QVBoxLayout"
#include "QtWidgets/QToolBar"
#include "QtWidgets/QMenuBar"
#include "QtWidgets/QMenu"
#include "QtWidgets/QAction"

#include "QtWidgets/QWidget"
#include "QtWidgets/QSplitter"
#include "QtWidgets/QGroupBox"
#include "QtWidgets/QFrame"
#include "QtWidgets/QLabel"
#include "QtWidgets/QCheckBox"
#include "QtWidgets/QPushButton"
#include "QtWidgets/QTextEdit"
#include "QtWidgets/QTabWidget"
#include "QtWidgets/QScrollArea"

enum class log_state		{none, error, warning, log, verbose, debug, release};
enum class timer_state		{idle, started, paused, stopped};

const string PATH_DATA	= "./data/";
const string SPACE		= " ";
const string TAB		= "\t";
const string NEWLINE	= "\n";
const string LOGFILE	= PATH_DATA + "log.txt";
const string LOG		= "[LOG]";
const string INFOFILE 	= PATH_DATA + "info.txt";
const string INFO		= "[INFO]";
const string WARFILE	= PATH_DATA + "war.txt";
const string WAR		= "[WARNING]";
const string ERRFILE	= PATH_DATA + "error.txt";
const string ERR		= "[ERROR]";
const string DEBFILE	= PATH_DATA + "debug.txt";

const QString FP_PATH_DATA = "./data/icon/";
const QString FP_PATH_ICON = "./data/icon/";

#endif // DEFINE_H_INCLUDED
