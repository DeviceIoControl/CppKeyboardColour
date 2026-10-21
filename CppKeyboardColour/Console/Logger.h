// Created by DeviceIoControl

// Created by DeviceIoControl

#pragma once
#include "ConsoleUtils.h"

#define KB_LOG_WRITE(level, msg, ...) AppConsole().Log(level, msg, __VA_ARGS__)

// Output message containing detailed internal information about the current execution status.
// Each message is typically prefixed with '{__FUNCTIONW__} - '.
#define KB_DEBUG(msg, ...) KB_LOG_WRITE(LogLevel::Debug, L"{%s} - " msg, __FUNCTIONW__, __VA_ARGS__)

// Standard output message for general information about current progress.
#define KB_INFO(msg, ...) KB_LOG_WRITE(LogLevel::Info, msg, __VA_ARGS__)

// Output message for possible issues which may have consequences in later program execution.
// CLEVO Keyboard Colour will continue to run, but this could be a symptom of upcoming failures later on.
#define KB_WARN(msg, ...) KB_LOG_WRITE(LogLevel::Warning, msg, __VA_ARGS__)

// Output message for non-fatal isolated errors that have occurred in an operation.
// CLEVO Keyboard Colour will continue to run, but this failure could have severe consequences later in program execution.
#define KB_ERROR(msg, ...) KB_LOG_WRITE(LogLevel::Error, msg, __VA_ARGS__)

// Output message for errors that affect the entire program execution. 
// CLEVO Keyboard Colour cannot continue and will halt execution and exit after displaying the message (point of no return).
#define KB_FATAL(msg, ...) KB_LOG_WRITE(LogLevel::Fatal, msg, __VA_ARGS__)

// Output a debug message displaying the corresponding function name and returned error code.
#define KB_ERROR_STATUS(fnName, errorCode) KB_DEBUG(L"%s failed with error status: 0x%08x.", fnName, errorCode)

// Sets the error code to return on a fatal log message.
#define KB_SET_FATAL_ERROR(errCode) SetLastError(errCode)