#include "gui/window.h"
#include "extern/parser.h"

using namespace GUI;

Window::Window()
{
	this->setup();
}

void Window::setup()
{
	this->center 		= new QWidget();
	this->centerBox		= new QHBoxLayout(center);
	this->splitter 		= new QSplitter(Qt::Horizontal);
	this->tabWidget		= new QTabWidget();
	this->fixbar 		= new FixBar();
	this->editor 		= new Editor();
	this->syntaxHighlighter = new SyntaxHighlighter(this->editor->getTextEdit()->document());

	Editor * ed1 = new Editor();
	Editor * ed2 = new Editor();
	Editor * ed3 = new Editor();
	Editor * ed4 = new Editor();

	this->tabWidget->addTab(editor, "Editor1");
	this->tabWidget->addTab(ed1, "Editor2");
	this->tabWidget->addTab(ed2, "Editor2");
	this->tabWidget->addTab(ed3, "Editor2");
	this->tabWidget->addTab(ed4, "Editor2");
	this->splitter->addWidget(fixbar);
	this->splitter->addWidget(tabWidget);

	this->setMinimumSize(200, 200);
	this->setGeometry(8, 31, 1024, 768);

	this->center->setContentsMargins(0, 0, -1, 0);
	this->centerBox->addWidget(splitter);
	this->addToolbar();
	this->addMenubar();
	this->splitter->setStretchFactor(0, 0);
	this->splitter->setStretchFactor(1, 1);
	this->centerBox->setSpacing(0);
	this->centerBox->setContentsMargins(0, 0, 0, 0);

	this->setCentralWidget(center);
	this->setStyleSheet(EXTERN::Directory::getFileContents("./data/style/themes/debug.css").c_str());

	this->setWindowTitle("FixPad");
}

void Window::addToolbar()
{
	QToolBar * toolbar 			= this->addToolBar("Main Toolbar");
	QAction * actionNew 		= toolbar->addAction(QIcon(QPixmap(FP_PATH_ICON + "new.png")), "New");
	QAction * actionSave 		= toolbar->addAction(QIcon(QPixmap(FP_PATH_ICON + "save.png")), "Save");
	QAction * actionLoad 		= toolbar->addAction(QIcon(QPixmap(FP_PATH_ICON + "load.png")), "Load");
	QAction * actionFullscreen 	= toolbar->addAction(QIcon(QPixmap(FP_PATH_ICON + "fullscreen.png")), "Fullscreen");

	connect(actionNew, SIGNAL(triggered()), this, SLOT(toggleFullScreen()));
	connect(actionSave, SIGNAL(triggered()), this, SLOT(toggleFullScreen()));
	connect(actionLoad, SIGNAL(triggered()), this, SLOT(toggleFullScreen()));
	connect(actionFullscreen, SIGNAL(triggered()), this, SLOT(toggleFullScreen()));

	this->addToolBar(toolbar);
}

void Window::addMenubar()
{
	QMenu * file = this->menuBar()->addMenu("&File");
	file->addAction(new QAction(QPixmap(FP_PATH_ICON + "new.png"), "&New", this));

	QMenu * edit = this->menuBar()->addMenu("&Edit");
	edit->addAction(new QAction(QPixmap(FP_PATH_ICON + "load.png"), "&Load", this));
}

void Window::toggleFullScreen()
{
	if(this->isFullScreen())
		this->setWindowState(Qt::WindowMaximized);
	else
		this->setWindowState(Qt::WindowFullScreen);
}

Window::~Window()
{

}

FixBar::FixBar()
{
	this->setup();
}

void FixBar::setup()
{
	this->centerBox 		= new QVBoxLayout(this);
	this->fileBrowser		= new QPushButton("File Browser");
	this->projectBrowser 	= new QPushButton("Project Browser");
	this->searchReplace 	= new QPushButton("Search / Replace");
	this->settings		 	= new QPushButton("Settings");

	this->centerBox->addWidget(fileBrowser);
	this->centerBox->addWidget(projectBrowser);
	this->centerBox->addWidget(searchReplace);
	this->centerBox->addWidget(settings);

	connect(this->fileBrowser, SIGNAL(clicked()), this, SLOT(showFileBrowser()));
	connect(this->projectBrowser, SIGNAL(clicked()), this, SLOT(showProjectBrowser()));
	connect(this->searchReplace, SIGNAL(clicked()), this, SLOT(showSearchReplace()));
	connect(this->settings, SIGNAL(clicked()), this, SLOT(showSettings()));

	this->centerBox->setContentsMargins(10, 10, 10, 10);
	this->centerBox->setSpacing(0);
	this->showFileBrowser();
}

void FixBar::showFileBrowser()
{
	this->centerBox->removeWidget(this->selection);
	delete this->selection;

	this->selection			= new QGroupBox("File Browser");
	this->selectionLayout	= new QVBoxLayout(selection);

	QPushButton	* button = new QPushButton("ButtonF");

	this->selectionLayout->addWidget(button);
	this->centerBox->addWidget(this->selection);
}

void FixBar::showProjectBrowser()
{
	this->centerBox->removeWidget(this->selection);
	delete this->selection;

	this->selection			= new QGroupBox("Project Browser");
	this->selectionLayout	= new QVBoxLayout(selection);

	QPushButton	* button = new QPushButton("ButtonP");

	this->selectionLayout->addWidget(button);
	this->centerBox->addWidget(this->selection);
}

void FixBar::showSearchReplace()
{
	this->centerBox->removeWidget(this->selection);
	delete this->selection;

	this->selection			= new QGroupBox("Search/Replace");
	this->selectionLayout	= new QVBoxLayout(selection);

	QPushButton	* button = new QPushButton("ButtonSR");

	this->selectionLayout->addWidget(button);
	this->centerBox->addWidget(this->selection);
}

void FixBar::showSettings()
{
	this->centerBox->removeWidget(this->selection);
	delete this->selection;

	this->selection			= new QGroupBox("Settings");
	this->selectionLayout	= new QVBoxLayout(selection);

	QCheckBox	* hideMenubar		= new QCheckBox("Hide Menubar");
	QCheckBox	* hideToolbar		= new QCheckBox("Hide Toolbar");

	this->selectionLayout->addWidget(hideMenubar);
	this->selectionLayout->addWidget(hideToolbar);
	this->centerBox->addWidget(this->selection);
}

FixBar::~FixBar()
{

}

Editor::Editor()
{
	this->setup();
}

void Editor::setup()
{
	this->centerBox 			= new QVBoxLayout(this);
	QLabel			* lines 	= new QLabel();
	QScrollArea		* scrollBar = new QScrollArea();
	QHBoxLayout		* hbox		= new QHBoxLayout(scrollBar);
	this->editor 	= new QTextEdit();
	QFont 			* font		= new QFont();
	QFontMetrics 	  metrics(*font);

	font->setFamily("Courier");
	font->setStyleHint(QFont::Monospace);
	font->setFixedPitch(true);
	font->setPointSize(11);

	editor->setFont(*font);
	editor->setTabStopWidth(8 * metrics.width(' '));

	QString line;
	for(int i = 0; i < 42; ++i)
	{
		line += QString::number(i) + "\n";
	}
	lines->setText(line);

	hbox->setContentsMargins(0, 0, 0, 0);
	hbox->setSpacing(0);
	this->centerBox->setContentsMargins(0, 0, 0, 0);
	this->centerBox->setSpacing(0);

	hbox->addWidget(lines);
	hbox->addWidget(editor);
	this->centerBox->addWidget(scrollBar);
}

QTextEdit * Editor::getTextEdit()
{
	return this->editor;
}

void Editor::write(QString text)
{
	this->editor->setText(text);
}

Editor::~Editor()
{

}

SyntaxHighlighter::SyntaxHighlighter(QTextDocument * editor) : QSyntaxHighlighter(editor)
{

}

void SyntaxHighlighter::highlightBlock(const QString & text)
{

}

SyntaxHighlighter::~SyntaxHighlighter()
{

}