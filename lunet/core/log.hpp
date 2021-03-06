#ifndef __LOG__
#define __LOG__
#include "core/define.h"
#include "core/Core.h"
#include "core/Context.h"
namespace Lunet{
namespace Logger{
std::ostream & operator << (std::ostream & os, IContext& context)
{
    os<<"["<<typeid(context).name()<<"("<<context.getid()<<")]";
    return os;
}

std::ostream & operator << (std::ostream & os, IContext* context)
{
    os<<"["<<typeid(*context).name()<<"("<<context->getid()<<")]";
    return os;
}

void log(std::stringstream& stream, eLogLevel level)
{
    CoreIns::instance()->log(std::move(stream), level);
}

template <typename T, typename ... Args>
void log(std::stringstream& stream, eLogLevel level, T&& head, Args ... args)
{
    stream << head;
    log(stream, level, args...);
}

const char* logI2S[] = {"D", "W", "I", "E"};
template <typename ... Args>
void log(eLogLevel level, const char* file, const int line, Args&& ... args)
{
    std::stringstream stream;
    stream << "[" << file << "." << line << "][" << logI2S[level] << "]";
    log(stream, level, args...);  
}

template <typename ... Args>
void logd(Args&& ... args)
{
    log(eDebug, args...);
}

template <typename ... Args>
void logw(Args&& ... args)
{
    log(eWarn, args...);
}

template <typename ... Args>
void logi(Args&& ... args)
{
    log(eInfo, args...);
}

template <typename ... Args>
void loge(Args&& ... args)
{
    log(eErro, args...);
}

#define LOGD(...) logd(__FILE__, __LINE__, __VA_ARGS__)
#define LOGW(...) logw(__FILE__, __LINE__, __VA_ARGS__)
#define LOGI(...) logi(__FILE__, __LINE__, __VA_ARGS__)
#define LOGE(...) logE(__FILE__, __LINE__, __VA_ARGS__)

void SetLogLevel(eLogLevel level)
{
    CoreIns::instance()->SetLogLevel(level);
}
};
};
#endif //__LOG__