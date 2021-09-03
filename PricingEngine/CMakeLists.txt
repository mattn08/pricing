
include_directories(inc)

add_executable(PricingEngine 

    inc/Black_scholes.h
    inc/StatsUtil.h
    inc/VanillaOption.h

    src/main.cpp
    src/Black_scholes.cpp
    src/StatsUtil.cpp
    src/VanillaOption.cpp
)