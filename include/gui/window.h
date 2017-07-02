#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#pragma once

#include "define.h"

namespace GUI
{
	/**
	*** FixBar
	***
	***
	**/
	class FixBar : public QWidget
	{
		Q_OBJECT

	private:
		QVBoxLayout * centerBox;

		QPushButton * fileBrowser;
		QPushButton * projectBrowser;
		QPushButton * searchReplace;
		QPushButton * settings;

		QGroupBox 	* selection;
		QVBoxLayout * selectionLayout;

	protected:

	public:
		FixBar();
		void setup();
		~FixBar();

	public slots:
		void showFileBrowser();
		void showProjectBrowser();
		void showSearchReplace();
		void showSettings();
	};

	/**
	*** Editor
	***
	***
	**/
	class Editor : public QWidget
	{
	private:
		QVBoxLayout * centerBox;
		QTextEdit 	* editor;

	protected:

	public:
		Editor();
		void setup();
		QTextEdit * getTextEdit();
		void write(QString text);
		~Editor();
	};

	/**
	*** SyntaxHighlighter
	***
	***
	**/
	class SyntaxHighlighter : public QSyntaxHighlighter
	{
	private:

	protected:
		void highlightBlock(const QString & text) Q_DECL_OVERRIDE;

	public:
		SyntaxHighlighter(QTextDocument * editor);
		~SyntaxHighlighter();
	};


	/**
	*** Window
	***
	***
	**/
	class Window : public QMainWindow
	{
		Q_OBJECT

	private:
		QWidget 			* center;
		QHBoxLayout 		* centerBox;
		QSplitter			* splitter;
		QTabWidget			* tabWidget;
		Editor 				* editor;
		SyntaxHighlighter 	* syntaxHighlighter;
		FixBar				* fixbar;

	protected:

	public:
		Window();
		void setup();
		void addToolbar();
		void addMenubar();
		~Window();

	public slots:
		void toggleFullScreen();
	};
}

#endif // WINDOW_H_INCLUDED
