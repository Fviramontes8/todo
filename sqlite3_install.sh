#/bin/bash
wget https://www.sqlite.org/2022/sqlite-autoconf-3390300.tar.gz
tar xvfz sqlite-autoconf-3390300.tar.gz
cd sqlite-autoconf-3390300/
./configure --prefix=/usr/local
make
make install
rm -rf sqlite-autoconf-3390300*
