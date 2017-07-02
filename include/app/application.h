#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include "define.h"
#include "gui/window.h"

namespace APP
{
	/**
	*** Timer
	***
	*** @var state:			The current timer state.
	*** @var timerTime: 	The time in milliseconds between all start()/resume() and pause() calls.
	*** @var ivalStart: 	The time in milliseconds between start() and pause() call.
	*** @var ivalStop:		The time in milliseconds between pause() and resume() call.
	*** @var frameCounter:	Counts the frames since the main loop was started. Requires call of
	***						@ref 'initFPSCounter()'
	*** @var frameTime:		The time in milliseconds needed for the amount of @ref 'frameCounter'.
	**/
	class Timer
	{
	protected:
		timer_state 		state;
		long 				timerTime;
		long				ivalStart;
		long				ivalStop;

	public:
		Timer();
		long 			getTicks();
		void 			start();
		long 			pause();
		long 			resume();
		long 			stop();
        long 			getTime();
        static void		sleep(int microseconds);
		static string 	getDateLine();
		static string 	getDateString();
		static string 	getTimeString();
		~Timer();
	};

	/**
	*** System
	***
	***
	**/
    class System
    {
	private:
		const string TAG = "System";
    public:
        static void run(string path, string prefix, string flags);
    };

    /**
    *** Log
    ***
    ***
    **/
    class Log
    {
    public:
        static void log(string tag, const string message);
        static void warning(string tag, const string message);
        static void error(string tag, const string message);
        static void info(string tag, const string message);
        static void debug(string tag, const string message);
        static void console(string tag, const string message, log_state state);
        static void clear(string filename);
    };

	class Application : public QApplication
	{
	private:
		GUI::Window * win;

	public:
		Application(int argc, char ** argv);
		~Application();
	};
}
#endif // APPLICATION_H_INCLUDED
