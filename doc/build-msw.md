WINDOWS BUILD NOTES
===================


Compilers Supported
-------------------
Compilation under Windows is supported using MinGW (http://www.mingw.org/)


Dependencies
------------
To build Kuberbitcoin for Windows, there are number of libraries you need to download
separately and build. Note that, for those used to a Linux/UNIX background, the search
paths for include files is not the conventional UNIX directories, see
http://www.mingw.org/wiki/IncludePathHOWTO for more details. Library files can be placed
in the more conventional /usr/local/lib directory, but see
http://www.mingw.org/wiki/HOWTO_Specify_the_Location_of_Libraries_for_use_with_MinGW in
case of difficulties.

In both cases, include and library files will need to be placed in the relevant directories
for the build process to succeed.

	name            default path               download
	--------------------------------------------------------------------------------------------------------------------
	OpenSSL         \openssl-1.0.1l-mgw        http://www.openssl.org/source/
	Berkeley DB     \db-5.1.29.NC-mgw          http://www.oracle.com/technology/software/products/berkeley-db/index.html
	Boost           \boost-1.55.0-mgw          http://www.boost.org/users/download/
	miniupnpc       \miniupnpc-1.6-mgw         http://miniupnp.tuxfamily.org/files/
    qt                                         http://download.qt-project.org/official_releases/qt/5.2/5.2.1/
    protobuf                                   http://protobuf.googlecode.com/files/protobuf-2.5.0.zip
    libpng                                     http://prdownloads.sourceforge.net/libpng/libpng-1.6.9.tar.gz?download
    libqrencode                                http://fukuchi.org/works/qrencode/qrencode-3.4.3.tar.gz

Their licenses:

	OpenSSL        Old BSD license with the problematic advertising requirement
	Berkeley DB    New BSD license with additional requirement that linked software must be free open source
	Boost          MIT-like license
	miniupnpc      New (3-clause) BSD license
    qt             
    protobuf       
    libpng         
    libqrencode    

Versions used in this release:

	OpenSSL      1.0.1l
	Berkeley DB  5.1.29.NC
	Boost        1.55.0
	miniupnpc    1.6
    qt           4.8.3
    protobuf     2.5.0
    libpng       1.6.9
    libqrencode  3.2.0


OpenSSL
-------
MSYS shell:

un-tar sources with MSYS 'tar xfz' to avoid issue with symlinks (OpenSSL ticket 2377)
change 'MAKE' env. variable from 'C:\MinGW32\bin\mingw32-make.exe' to '/c/MinGW32/bin/mingw32-make.exe'

	cd /c/openssl-1.0.1l-mgw
	./config
	make

Berkeley DB (see end of document for important info regarding BDB)
-----------
MSYS shell:

	cd /c/db-5.1.29.NC-mgw/build_unix
	sh ../dist/configure --enable-mingw --enable-cxx
	make

Include and library files files should then be placed into MinGW search paths, for example:

Include: C:\MinGW\lib\gcc\mingw32\4.8.1\include\c++
Library: C:\MinGW\lib
    
Boost
-----
MSYS shell:

	cd boost_1_55_0/tools/build/v2/engine
    ./build.sh mingw
    cp bin.ntx86/bjam.exe ../../../../
    cd ../../../../
    bjam --toolset=gcc
    
In case of problems, http://stackoverflow.com/questions/13256788/building-boost-1-52-with-mingw may be useful

MiniUPnPc
---------
UPnP support is optional, make with `USE_UPNP=` to disable it.

MSYS shell:

	cd /c/miniupnpc-1.6-mgw
	make -f Makefile.mingw
	mkdir miniupnpc
	cp *.h miniupnpc/

Kuberbitcoin
-------
MSYS shell:

	kuberbitcoin
	./autogen.sh
	BOOST_ROOT=../boost_1_55_0 ./configure --disable-tests
	mingw32-make
	strip kuberbitcoind.exe


Berkeley DB
-----------
# Installing libdb5.1 onto a system with libdb4.8 already installed. 
From https://bitcointalk.org/index.php?topic=1432608.msg15382962#msg15382962

BITCOIN_ROOT=$(pwd)

- Pick some path to install BDB to, here we create a directory within the kuberbitcoin directory  
> BDB_PREFIX="${BITCOIN_ROOT}/db5" mkdir -p $BDB_PREFIX

- Fetch the source and verify that it is not tampered with  
> wget 'http://download.oracle.com/berkeley-db/db-5.1.29.NC.tar.gz'
echo '08238e59736d1aacdd47cfb8e68684c695516c37f4fbe1b8267dde58dc3a576c  db-5.1.29.NC.tar.gz' | sha256sum -c  
tar -xzvf db-5.1.29.NC.tar.gz

- Build the library and install to our prefix  
> cd db-5.1.29.NC/build_unix/

-  Note: Do a static build so that it can be embedded into the exectuable, instead of having to find a .so at runtime
> ../dist/configure --enable-cxx --disable-shared --with-pic --prefix=$BDB_PREFIX
make install

- Configure Kuberbitcoin Core to use our own-built instance of BDB  
> cd $BITCOIN_ROOT
./autogen.sh
./configure LDFLAGS="-L${BDB_PREFIX}/lib/" CPPFLAGS="-I${BDB_PREFIX}/include/"
make