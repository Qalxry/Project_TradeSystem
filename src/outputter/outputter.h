#pragma once
#ifndef OUTPUTTER_H
#define OUTPUTTER_H
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/core.h>
#include <iostream>
#include <string>

void test_outputter(){
    spdlog::error("error");
    spdlog::warn("warn");
    spdlog::info("info");
    spdlog::debug("debug");
    spdlog::trace("trace");
    spdlog::critical("critical");
    spdlog::log(spdlog::level::level_enum::info, "log");
}


#endif  // !OUTPUTTER_H