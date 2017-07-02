#include "app/application.h"

using namespace APP;
using namespace GUI;

Timer::Timer()
{
	this->start();
}

long Timer::getTicks()
{
	return time(0);
}

void Timer::start()
{
	this->timerTime = 0;
	this->ivalStart = this->getTicks();
	this->state = timer_state::started;
}

long Timer::pause()
{
	if(this->state == timer_state::started)
	{
		this->ivalStop = this->getTicks();
		this->state = timer_state::paused;
		this->timerTime += (this->ivalStop - this->ivalStart);
	}
	return this->ivalStop;
}

long Timer::resume()
{
	if(this->state == timer_state::paused)
	{
		this->ivalStart = this->getTicks();
		this->state = timer_state::started;
	}
	return this->ivalStart;
}

long Timer::stop()
{
	if(this->state != timer_state::idle && this->state != timer_state::stopped)
	{
		this->state = timer_state::stopped;
	}
	return timerTime;
}

long Timer::getTime()
{
	this->pause();
	this->resume();
	return this->timerTime;
}

void Timer::sleep(int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

string Timer::getDateLine()
{
	time_t t;
	time(&t);
	return ctime(&t);
}

string Timer::getDateString()
{
	string timeString = Timer::getDateLine();
	return timeString.substr(0, timeString.length()-1);
}

string Timer::getTimeString()
{
	string time = Timer::getDateString();
	return time.substr(11, 8);
}

Timer::~Timer()
{
	this->stop();
}

void System::run(string file, string prefix, string flags)
{
    string command = prefix + " " + file + " " + flags;
    system(command.c_str());
}

void Log::log(string tag, string message)
{
	ofstream log(LOGFILE, std::ios_base::out | std::ios_base::app);
	log << Timer::getTimeString() << SPACE << LOG << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::info(string tag, string message)
{
	ofstream log(INFOFILE, std::ios_base::out | std::ios_base::app);
	log << Timer::getTimeString() << SPACE << LOG << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::warning(string tag, string message)
{
	ofstream war(WARFILE, std::ios_base::out | std::ios_base::app);
	war << Timer::getTimeString() << SPACE << WAR << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::error(string tag, string message)
{
	ofstream err(ERRFILE, std::ios_base::out | std::ios_base::app);
	err << Timer::getTimeString() << SPACE << ERR << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::debug(string tag, string message)
{
	ofstream deb(DEBFILE, std::ios_base::out | std::ios_base::app);
	deb << Timer::getTimeString() << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::console(string tag, string message, log_state state)
{
	if(state >= log_state::error)
	{
		cout << Timer::getTimeString() << SPACE << setw(20) << left << tag << SPACE << message << endl;
	}
}

void Log::clear(string filename)
{
	fstream file(filename, std::ios_base::trunc | std::ios_base::out);
}

Application::Application(int argc, char ** argv) : QApplication(argc, argv)
{
	this->win 			= new Window();

	this->win->setContentsMargins(0, 0, 0, 0);

	this->win->show();
}

Application::~Application()
{

}