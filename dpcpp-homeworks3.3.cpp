#include <iostream>
#include "LogMessage.h"

int main()
{
	auto wh = std::make_shared<WarningHandler>();
	auto eh = std::make_shared<ErrorHandler>("ErrorLog.txt");
	auto feh = std::make_shared<FatalErrorHandler>();
	auto ueh = std::make_shared<UnknowErrorHandler>();
	feh->setNext(eh)->setNext(wh)->setNext(ueh);

	LogMessage WLM(LogMessage::Type::WARNING, "Warning message");
	LogMessage ELM(LogMessage::Type::ERROR, "Error message");
	LogMessage ELM2(LogMessage::Type::ERROR, "Error2 message");
	LogMessage FELM(LogMessage::Type::FATAL_ERROR, "Fatal error message");
	LogMessage UELM(LogMessage::Type::UNKNOW_ERROR, "Unknow error message");
	std::vector<LogMessage> LMvector = { ELM2, WLM, ELM, FELM, UELM };

	for (const LogMessage& lm : LMvector) {
		try
		{
			feh->handle(lm);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}