include_directories(${EliteQuantCpp_SOURCE_DIR}/EliteQuant)
set(EQSERVER_SRC
  main.cpp
  )
add_executable(eqserver ${EQSERVER_SRC})
TARGET_LINK_LIBRARIES(eqserver libelitequant ${Boost_LIBRARIES} ${NANOMSG_LIBRARY_SHARED} thosttraderapi thostmduserapi zmq yaml-cpp sandbox_vs_dll)
