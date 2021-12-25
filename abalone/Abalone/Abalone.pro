TEMPLATE = subdirs
SUBDIRS += \
    src/abalone \
    src/tui \
    src/gui \
    tests


src-tui.depends = src/abalone
src-gui.depends = src/abalone
tests.depends = src/abalone

OTHER_FILES += config.pri \
    Doxyfile \
    ../../README.MD \
    ../../.gitignore
