#pragma once
#ifndef OUTPUT_H
#define OUTPUT_H
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/core.h>
#include <iostream>
#include <string>
#include "../func/func.h"

void test_output(){
    spdlog::error("error");
    spdlog::warn("warn");
    spdlog::info("info");
    spdlog::debug("debug");   
    //spdlog::critical("critical");
    string nowTime = getSystemTime("%Y&%m&%d-%H:%M:%S");
    //auto logger = spdlog::default_logger(nowTime + "_log");
    //logger->set_level(spdlog::level::info);
    //logger->info("info: {}", "Fuck you!!!");
}


#endif  // !OUTPUT_H