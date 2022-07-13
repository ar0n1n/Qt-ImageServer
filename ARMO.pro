
TEMPLATE = app
QT += core network gui widgets
CONFIG += console debug

server {
    TARGET = server
    SOURCES += server_main.cpp \
               src/Runnable.cpp \
               src/Server.cpp
    HEADERS += includes/Runnable.hpp \
               includes/Server.hpp
}

client {
    TARGET = client
    SOURCES += client_main.cpp \
               src/Client.cpp
    HEADERS += includes/Client.hpp
}