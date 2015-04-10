TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    hmm.cpp \
    forwardbackward.cpp \
    helpers.cpp \
    viterbi.cpp \
    testing.cpp

HEADERS += \
    hmm.h \
    forwardbackward.h \
    helpers.h \
    viterbi.h \
    testing.h

