CONFIG += debug c++11

HEADERS += mainwindow.h view.h candle.h grid.h
HEADERS += ohlc.h
HEADERS += ohlc_random_generator.h ohlc_shrinker.h ohlc_provider.h ohlc_standardizer.h ohlc_memory_provider.h
HEADERS += yahoo_loader.h csv_reader.h
HEADERS += graph_event_controller.h

SOURCES += main.cpp
SOURCES += mainwindow.cpp view.cpp candle.cpp grid.cpp
SOURCES += ohlc.cpp
SOURCES += ohlc_random_generator.cpp ohlc_shrinker.cpp ohlc_standardizer.cpp ohlc_memory_provider.cpp ohlc_provider.cpp
SOURCES += yahoo_loader.cpp csv_reader.cpp
SOURCES += graph_event_controller.cpp

QT += widgets xml network
qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}
