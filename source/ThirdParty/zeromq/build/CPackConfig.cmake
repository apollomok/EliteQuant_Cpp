# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_7Z "")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_FREEBSD "")
SET(CPACK_BINARY_IFW "")
SET(CPACK_BINARY_NSIS "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_PRODUCTBUILD "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TXZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_BUILD_SOURCE_DIRS "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq;D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build")
SET(CPACK_CMAKE_GENERATOR "Visual Studio 15 2017")
SET(CPACK_COMPONENTS_ALL "PerfTools;Runtime;SDK;SourceCode;Unspecified")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_GENERATOR "NSIS")
SET(CPACK_INSTALL_CMAKE_PROJECTS "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build;ZeroMQ;ALL;/")
SET(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/ZeroMQ")
SET(CPACK_MODULE_PATH "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build")
SET(CPACK_NSIS_COMPRESSOR "/SOLID lzma")
SET(CPACK_NSIS_CONTACT "Steven McCoy <Steven.McCoy@miru.hk>")
SET(CPACK_NSIS_DISPLAY_NAME "ZeroMQ 4.1.6(x86)")
SET(CPACK_NSIS_DISPLAY_NAME_SET "TRUE")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_MUI_ICON "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq\\installer.ico")
SET(CPACK_NSIS_MUI_UNIICON "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq\\installer.ico")
SET(CPACK_NSIS_PACKAGE_NAME "ZeroMQ 4.1.6(x86)")
SET(CPACK_OUTPUT_CONFIG_FILE "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/CPackConfig.cmake")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files/CMake/share/cmake-3.10/Templates/CPack.GenericDescription.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ZeroMQ lightweight messaging kernel")
SET(CPACK_PACKAGE_FILE_NAME "ZeroMQ-4.1.6-x86")
SET(CPACK_PACKAGE_ICON "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq\\branding.bmp")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "ZeroMQ 4.1.6")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "ZeroMQ 4.1.6")
SET(CPACK_PACKAGE_NAME "ZeroMQ")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Miru")
SET(CPACK_PACKAGE_VERSION "4.1.6")
SET(CPACK_PACKAGE_VERSION_MAJOR "4")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "6")
SET(CPACK_RESOURCE_FILE_LICENSE "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build\\COPYING.txt")
SET(CPACK_RESOURCE_FILE_README "C:/Program Files/CMake/share/cmake-3.10/Templates/CPack.GenericDescription.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files/CMake/share/cmake-3.10/Templates/CPack.GenericWelcome.txt")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "ON")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "7Z;ZIP")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_RPM "")
SET(CPACK_SOURCE_TBZ2 "")
SET(CPACK_SOURCE_TGZ "")
SET(CPACK_SOURCE_TXZ "")
SET(CPACK_SOURCE_TZ "")
SET(CPACK_SOURCE_ZIP "ON")
SET(CPACK_SYSTEM_NAME "win32")
SET(CPACK_TOPLEVEL_TAG "win32")
SET(CPACK_WIX_SIZEOF_VOID_P "4")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "D:/Workspace/EliteQuant_Cpp/source/ThirdParty/zeromq/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()

# Configuration for component group "Development"
set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DISPLAY_NAME "ZeroMQ software development kit")
set(CPACK_COMPONENT_GROUP_DEVELOPMENT_EXPANDED TRUE)

# Configuration for component "PerfTools"

SET(CPACK_COMPONENTS_ALL PerfTools Runtime SDK SourceCode Unspecified)
set(CPACK_COMPONENT_PERFTOOLS_DISPLAY_NAME "ZeroMQ performance tools")
set(CPACK_COMPONENT_PERFTOOLS_INSTALL_TYPES FullInstall DevInstall)

# Configuration for component "SourceCode"

SET(CPACK_COMPONENTS_ALL PerfTools Runtime SDK SourceCode Unspecified)
set(CPACK_COMPONENT_SOURCECODE_DISPLAY_NAME "ZeroMQ source code")
set(CPACK_COMPONENT_SOURCECODE_INSTALL_TYPES FullInstall)
set(CPACK_COMPONENT_SOURCECODE_DISABLED TRUE)

# Configuration for component "SDK"

SET(CPACK_COMPONENTS_ALL PerfTools Runtime SDK SourceCode Unspecified)
set(CPACK_COMPONENT_SDK_DISPLAY_NAME "ZeroMQ headers and libraries")
set(CPACK_COMPONENT_SDK_GROUP Development)
set(CPACK_COMPONENT_SDK_INSTALL_TYPES FullInstall DevInstall)

# Configuration for component "Runtime"

SET(CPACK_COMPONENTS_ALL PerfTools Runtime SDK SourceCode Unspecified)
set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "ZeroMQ runtime files")
set(CPACK_COMPONENT_RUNTIME_INSTALL_TYPES FullInstall DevInstall MinInstall)
set(CPACK_COMPONENT_RUNTIME_REQUIRED TRUE)

# Configuration for installation type "FullInstall"
list(APPEND CPACK_ALL_INSTALL_TYPES FullInstall)
set(CPACK_INSTALL_TYPE_FULLINSTALL_DISPLAY_NAME "Full install, including source code")

# Configuration for installation type "DevInstall"
list(APPEND CPACK_ALL_INSTALL_TYPES DevInstall)
set(CPACK_INSTALL_TYPE_DEVINSTALL_DISPLAY_NAME "Developer install, headers and libraries")

# Configuration for installation type "MinInstall"
list(APPEND CPACK_ALL_INSTALL_TYPES MinInstall)
set(CPACK_INSTALL_TYPE_MININSTALL_DISPLAY_NAME "Minimal install, runtime only")
