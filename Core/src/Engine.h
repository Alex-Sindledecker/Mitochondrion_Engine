#pragma once

/// Includes all nececary files that an external application would need
/// Not for use by [REDACTED]

#include "Debug/Debug.h"
#include "Application/App.h"

#include "Application/EntryPoint.h"

#include "Core/Time.h"

static Engine::DebugLogger& Logger = Engine::DebugLogger::getInstance();