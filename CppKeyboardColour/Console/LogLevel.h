// Created by DeviceIoControl
#pragma once

enum class LogLevel : uint16_t
{
	None,
	Debug, /* Output message containing detailed internal information about the current execution status. Each message is usually prefixed with '{__FUNCTION__} - '. */
	Info, // Standard output message for general information about current progress.
	Warning, // Output message for possible errors that may have later consequences on in execution.
	Error, // Output message for non-fatal errors that have occurred. ClickDFIR will continue to run, but may be unstable.
	Fatal // Output message for FATAL errors. ClickDFIR cannot continue and will halt execution and exit after displaying the message (Point of no return).
};