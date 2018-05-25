# Install script for directory: D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/ZeroMQ")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/libzmq.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xPerfToolsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Debug/local_lat.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Release/local_lat.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/MinSizeRel/local_lat.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/RelWithDebInfo/local_lat.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xPerfToolsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Debug/remote_lat.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Release/remote_lat.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/MinSizeRel/remote_lat.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/RelWithDebInfo/remote_lat.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xPerfToolsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Debug/local_thr.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Release/local_thr.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/MinSizeRel/local_thr.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/RelWithDebInfo/local_thr.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xPerfToolsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Debug/remote_thr.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Release/remote_thr.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/MinSizeRel/remote_thr.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/RelWithDebInfo/remote_thr.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xPerfToolsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Debug/inproc_lat.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Release/inproc_lat.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/MinSizeRel/inproc_lat.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/RelWithDebInfo/inproc_lat.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xPerfToolsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Debug/inproc_thr.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Release/inproc_thr.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/MinSizeRel/inproc_thr.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/RelWithDebInfo/inproc_thr.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/lib/Debug/libzmq-v141-mt-gd-4_1_6.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/lib/Release/libzmq-v141-mt-4_1_6.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/lib/MinSizeRel/libzmq.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/lib/RelWithDebInfo/libzmq-v141-mt-4_1_6.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xSDKx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/include/zmq.h"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/include/zmq_utils.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/lib/Debug/libzmq-v141-mt-sgd-4_1_6.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/lib/Release/libzmq-v141-mt-s-4_1_6.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/lib/MinSizeRel/libzmq.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/lib/RelWithDebInfo/libzmq-v141-mt-s-4_1_6.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xSDKx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/include/zmq.h"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/include/zmq_utils.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Debug/libzmq-v141-mt-gd-4_1_6.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/Release/libzmq-v141-mt-4_1_6.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/MinSizeRel/libzmq.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/bin/RelWithDebInfo/libzmq-v141-mt-4_1_6.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/include/zmq.h"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/include/zmq_utils.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xSourceCodex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/src/zmq" TYPE FILE FILES
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/address.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/clock.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ctx.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/curve_client.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/curve_server.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/dealer.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/devpoll.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/dist.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/epoll.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/err.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/fq.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/io_object.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/io_thread.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ip.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ipc_address.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ipc_connecter.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ipc_listener.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/kqueue.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/lb.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/mailbox.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/mechanism.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/metadata.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/msg.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/mtrie.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/object.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/options.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/own.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/null_mechanism.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pair.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pgm_receiver.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pgm_sender.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pgm_socket.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pipe.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/plain_client.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/plain_server.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/poll.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/poller_base.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/precompiled.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/proxy.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pub.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pull.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/push.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/random.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/raw_encoder.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/raw_decoder.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/reaper.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/rep.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/req.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/router.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/select.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/session_base.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/signaler.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/socket_base.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/socks.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/socks_connecter.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/stream.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/stream_engine.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/sub.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tcp.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tcp_address.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tcp_connecter.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tcp_listener.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/thread.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/trie.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/v1_decoder.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/v1_encoder.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/v2_decoder.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/v2_encoder.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/xpub.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/xsub.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/zmq.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/zmq_utils.cpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/config.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/tweetnacl/src/tweetnacl.c"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/tweetnacl/contrib/randombytes/winrandom.c"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/version.rc"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/platform.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/address.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/array.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/atomic_counter.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/atomic_ptr.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/blob.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/clock.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/command.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/config.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ctx.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/curve_client.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/curve_server.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/dbuffer.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/dealer.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/decoder.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/devpoll.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/dist.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/encoder.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/epoll.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/err.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/fd.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/fq.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/gssapi_client.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/gssapi_mechanism_base.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/gssapi_server.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/i_decoder.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/i_encoder.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/i_engine.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/i_poll_events.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/io_object.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/io_thread.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ip.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ipc_address.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ipc_connecter.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ipc_listener.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/kqueue.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/lb.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/likely.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/mailbox.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/mechanism.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/metadata.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/msg.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/mtrie.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/mutex.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/norm_engine.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/null_mechanism.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/object.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/options.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/own.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pair.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pgm_receiver.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pgm_sender.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pgm_socket.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pipe.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/plain_client.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/plain_server.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/poll.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/poller.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/poller_base.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/precompiled.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/proxy.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pub.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/pull.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/push.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/random.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/raw_decoder.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/raw_encoder.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/reaper.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/rep.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/req.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/router.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/select.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/session_base.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/signaler.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/socket_base.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/socks.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/socks_connecter.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/stdint.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/stream.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/stream_engine.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/sub.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tcp.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tcp_address.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tcp_connecter.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tcp_listener.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/thread.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tipc_address.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tipc_connecter.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/tipc_listener.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/trie.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/v1_decoder.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/v1_encoder.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/v2_decoder.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/v2_encoder.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/v2_protocol.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/windows.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/wire.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/xpub.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/xsub.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ypipe.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ypipe_base.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/ypipe_conflate.hpp"
    "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/src/yqueue.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/AUTHORS.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/COPYING.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/COPYING.LESSER.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/MAINTAINERS.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/NEWS.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES
    "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Redist/MSVC/14.12.25810/x86/Microsoft.VC141.CRT/msvcp140.dll"
    "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Redist/MSVC/14.12.25810/x86/Microsoft.VC141.CRT/vcruntime140.dll"
    "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Redist/MSVC/14.12.25810/x86/Microsoft.VC141.CRT/concrt140.dll"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE DIRECTORY FILES "")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/tests/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
