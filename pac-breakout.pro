QT += widgets
TARGET = pac-breakout
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/ball.cpp \
    src/breakout_window.cpp \
    src/paddle.cpp \
    src/breakout_item.cpp \
    src/wall.cpp \
    src/brick.cpp \
    src/controller.cpp

HEADERS += \
    src/ball.hpp \
    src/breakout_window.hpp \
    src/paddle.hpp \
    src/breakout_item.hpp \
    src/wall.hpp \
    src/brick.hpp \
    src/controller.hpp

FORMS += \
    src/breakout_window.ui
