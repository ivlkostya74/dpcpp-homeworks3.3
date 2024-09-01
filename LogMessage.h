#pragma once
#include <iostream>
#include <vector>
#include <fstream>

class LogMessage
{
public:
	enum class Type
	{
		WARNING,
		ERROR,
		FATAL_ERROR,
		UNKNOW_ERROR
	};
	LogMessage(Type type, const std::string& message);
	Type type() const;
	const std::string& message() const;
private:
	Type mType_;
	std::string message_;
};

class LogMessageHandler
{
public:
	virtual ~LogMessageHandler() {};
	std::shared_ptr<LogMessageHandler> setNext(std::shared_ptr<LogMessageHandler> nextHandler);
	virtual void handle(const LogMessage& lm);
private:
	std::shared_ptr<LogMessageHandler> nextHandler_ = nullptr;
};

class WarningHandler : public LogMessageHandler
{
public:
	void handle(const LogMessage& lm) override;
};

class ErrorHandler : public LogMessageHandler
{
public:
	ErrorHandler(const std::string& fileName);
	void handle(const LogMessage& lm) override;
	~ErrorHandler();
private:
	std::ofstream fout;
};

class FatalErrorHandler : public LogMessageHandler
{
public:
	void handle(const LogMessage& lm) override;
};

class UnknowErrorHandler : public LogMessageHandler
{
public:
	void handle(const LogMessage& lm) override;
};