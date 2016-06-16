# RPiTC_Builder
RPiTC packages installer/remover

prerequisite: libqt5-core libqt5-network

compile without qtcreator:
apt-get install git-core qt5-qmake qt5-default make g++
git clone https://github.com/Gibbio/RPiTC_Builder/
cd RPiTC_Builder/
make
