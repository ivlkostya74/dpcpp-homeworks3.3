#include "LogMessage.h"

LogMessage::LogMessage(Type type, const std::string& message) :
    mType_(type), message_(message) {}

LogMessage::Type LogMessage::type() const
{
    return mType_;
}

const std::string& LogMessage::message() const
{
    return message_;
}

std::shared_ptr<LogMessageHandler> LogMessageHandler::setNext(std::shared_ptr<LogMessageHandler> nextHandler)
{
    nextHandler_ = nextHandler;
    return nextHandler;
}

void LogMessageHandler::handle(const LogMessage& lm)
{
    if (nextHandler_)
    {
        nextHandler_->handle(lm);
    }
}

void WarningHandler::handle(const LogMessage& lm)
{
    if (lm.type() == LogMessage::Type::WARNING)
    {
        std::cout << "Warning: " << lm.message() << std::endl;
    }
    else
    {
        return LogMessageHandler::handle(lm);
    }
}

ErrorHandler::ErrorHandler(const std::string& fileName)
{
    fout.open(fileName, std::ofstream::app);
    if (!fout.is_open())
    {
        std::cout << "ErrorLog isn't opened!" << std::endl;
    }
}

void ErrorHandler::handle(const LogMessage& lm)
{
    if (lm.type() == LogMessage::Type::ERROR)
    {
        fout.seekp(0, std::ios::end);
        fout << "Error: " << lm.message() << std::endl;
        std::cout << "Error: " << lm.message() << std::endl;
    }
    else
    {
        return LogMessageHandler::handle(lm);
    }
}

ErrorHandler::~ErrorHandler()
{
    fout.close();
}

void FatalErrorHandler::handle(const LogMessage& lm)
{
    if (lm.type() == LogMessage::Type::FATAL_ERROR)
    {
        std::cout << "Fatal error: " << lm.message() << std::endl;
        throw std::runtime_error("FATAL_ERROR!");
    }
    else
    {
        return LogMessageHandler::handle(lm);
    }
}

void UnknowErrorHandler::handle(const LogMessage& lm)
{
    if (lm.type() == LogMessage::Type::UNKNOW_ERROR)
    {
        throw std::runtime_error("UNKNOW_ERROR: Message isn't handled\n");
    }
    else
    {
        return LogMessageHandler::handle(lm);
    }
}