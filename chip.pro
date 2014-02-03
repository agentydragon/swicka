HEADERS += mainwindow.h view.h candle.h grid.h
HEADERS += ohlc.h
HEADERS += ohlc_random_generator.h ohlc_shrinker.h ohlc_provider.h ohlc_standardizer.h ohlc_memory_provider.h
HEADERS += yahoo_loader.h csv_reader.h

SOURCES += main.cpp
SOURCES += mainwindow.cpp view.cpp candle.cpp grid.cpp
SOURCES += ohlc.cpp
SOURCES += ohlc_random_generator.cpp ohlc_shrinker.cpp ohlc_standardizer.cpp ohlc_memory_provider.cpp
SOURCES += yahoo_loader.cpp csv_reader.cpp

QT += widgets xml network
qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}
