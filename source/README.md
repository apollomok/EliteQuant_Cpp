Set up development environment

```bash
sudo apt-get update				# update the list of available packages
sudo apt-get upgrade			# upgrade to latest version of packages
sudo apt-get install libtool		# script support
sudo apt-get install build-essential     # gcc/g++ compilers
sudo apt-get install pkg-config		# compiler helper
sudo apt-get install autoconf		# support m4 macro script
sudo apt-get install automake		# support makefile
sudo apt-get install cmake			# install cmake

# (optional) upgrade cmake
whereis cmake						# check cmake path
cmake --version						# check cmake version
sudo apt-get remove cmake           # remove old version
wget https://cmake.org/files/v3.10/cmake-3.10.1.tar.gz		# go to cmake.org for link to latest version; might be higher than 3.10.1
tar xf cmake-3.10.1.tar.gz		# unzip
cd cmake-3.10.1.tar.gz			# enter folder
./boostrap						# preparation
make							# make cmake
sudo make install				# install cmake
cmake --version					# check cmake version

# install boost
sudo apt-get install libboost-all-dev		# boost c++
whereis boost					# typically in /usr/include and /usr/lib
dpkg -s libboost-dev | grep 'Version'		# get boost version

# get EliteQuant
git clone https://github.com/EliteQuant/EliteQuant_Cpp			# pull from Github
cd EliteQuant_Cpp/source						# enter source folder

# compile zeromq from source
# https://tuananh.org/2015/06/16/how-to-install-zeromq-on-ubuntu/
sudo apt-get install libzmq-dev
git clone git://github.com/jedisct1/libsodium.git		# download libsodium in source folder
pushd libsodium						# enter folder libsodium
./autogen.sh						# run autogen
./configure	&& make check			# make libsodium
sudo make install					# install libsodium, typically in /usr/local/include and /usr/local/lib
sudo ldconfig						# unknown
popd								# go back to source folder
rm -r libsodium						# delete libsodium source file

wget https://archive.org/download/zeromq_4.1.4/zeromq-4.1.4.tar.gz		# get latest version; might be higher than 4.1.4
tar -xvf zeromq-4.1.4.tar.gz		# unzip
rm zeromq-4.1.4.tar.gz				# delete zip file
pushd zeromq-4.1.4		# enter zeromq folder
./autogen.sh						# run autogen
./configure	&& make check			# make zeromq
sudo make install					# install zeromq, typically in /usr/local/include and /usr/local/lib
sudo ldconfig						# unknown
popd								# go back to source folder
rm -r zeromq-4.1.4					# delete zeromq source file
whereis zmq							# locate zmq


# nanomsg
# https://github.com/nanomsg/nanomsg
pushd ThirdParty/nanomsg			# enter nanomsg
mkdir build							# create build folder
cd build							# enter build
cmake ..							# cmake
cmake -- build .					# build cmake
ctest .								# test
sudo cmake --build . --target install	# /to usr/local/include/nanomsg and /usr/local/lib
sudo ldconfig						# if on Linux
popd								# back to source folder

# seasocks
# https://github.com/mattgodbolt/seasocks
pushd ThirdParty/seasocks			# enter seasocks
mkdir build							# create build folder
cd build							# enter build
export CXXFLAGS="$CXXFLAGS -fPIC"	# position independent code
cmake ..							# cmake
make								# build cmake
cd ..								# out of build dir
sudo cp -f build/src/main/c/libseasocks.a /usr/lib/x86_64-linux-gnu/		# copy lib
sudo cp -fr src/main/c/seasocks/ /usr/include		# copy headers
popd								# go back to EliteQuant/source/

# yaml_cpp
# https://github.com/jbeder/yaml-cpp
pushd ThirdParty/yaml-cpp			# enter yaml-cpp
mkdir build							# create build folder
cd build							# enter build
cmake ..							# cmake
make								# build cmake
sudo cp -f libyaml-cpp.a /usr/lib/x86_64-linux-gnu/		# copy lib
sudo cp -fr ../include/yaml-cpp/ /usr/include/			# copy headers
popd								# go back to EliteQuant/source/

# EliteQuant

```