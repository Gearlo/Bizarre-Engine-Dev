/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bizarre
// ULog.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================================================================
// Copyright (c) 2012 Skaiware
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================


#include <BEngine.h>

#include <iostream>
#include <fstream>


// static vars
ULog *			ULog::m_instance = NULL;
int				ULog::m_desired_loglevel = 6;
fstream			ULog::m_logfstream;
stringstream	ULog::m_stringstream;
string			ULog::m_string;


ULog::ULog()
{
	m_instance = this;
	
	// open file stream
	m_logfstream.open("maratis_log.txt", std::fstream::out|std::fstream::trunc);
	
	if(! m_logfstream.good())
		printf("ULog: file fstream not good\n");
	
	char * mll = getenv("MARATIS_LOG_LEVEL");
	if(mll)
	{
		m_logfstream<<"Found env var MARATIS_LOG_LEVEL = "<<mll<<std::endl;
		int desired_loglevel = atoi(mll);
		
		if(desired_loglevel>=0 && desired_loglevel<=7) // MUST be between 0 & 7
			m_desired_loglevel=desired_loglevel;
	}
	
	m_logfstream<<"Log tracked at level :"<< m_desired_loglevel <<std::endl;
}

ULog::~ULog()
{
	m_logfstream.close();
}

static char severities_strings[][64]={{"Emerg"}, {"Alert"}, {"Critic"}, {"Error"}, {"Warn"}, {"Notice"}, {"Info"}, {"Debug"}};

void ULog::log(int severity, const char * function, const char * filename, const int & line_no)
{
	if(severity > m_desired_loglevel)
		return;

	if(! m_instance)
		m_instance = new ULog();

    // todo ? what is the real diff between cerr and cout
	//if (severity<=5)
		//std::cerr<<severity<<" "<<m_string<<std::endl;

    string sev="???";
    if(severity >= 0 && severity <= 7)
		sev = severities_strings[severity];

    std::cout<< sev <<"\t "<< m_string << "\t in " << (function?function:"?")
        //<< " in "<< (filename?filename:"?") // do we add filename in console ?
        << std::endl;

	if(m_logfstream.good())
		m_logfstream<<sev<<"\t "<<m_string<< "\t in " << (function?function:"?") << "\t in "<< (filename?filename:"?") <<std::endl;
}
