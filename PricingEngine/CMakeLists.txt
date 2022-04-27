
include_directories(inc)

set(SOURCES ${SOURCES})


# add_executable(PricingEngine 

#     inc/Black_scholes.h
#     inc/StatsUtil.h
#     inc/VanillaOption.h

#     src/main.cpp
#     src/Black_scholes.cpp
#     src/StatsUtil.cpp
#     src/VanillaOption.cpp
# )


add_library(PricingEngine_lib STATIC

    inc/Black_scholes.h
    inc/StatsUtil.h
    inc/VanillaOption.h

    src/main.cpp
    src/Black_scholes.cpp
    src/StatsUtil.cpp
    src/VanillaOption.cpp
)

target_include_directories(PricingEngine_lib PUBLIC inc)
