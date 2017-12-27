include_directories(${EliteQuantCpp_SOURCE_DIR}/EliteQuant)
set(EQSERVER_SRC
  main.cpp
  )
add_executable(eqserver ${EQSERVER_SRC})
TARGET_LINK_LIBRARIES(eqserver elitequant)
