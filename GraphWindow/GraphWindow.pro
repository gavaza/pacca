TEMPLATE = subdirs

SUBDIRS += QGVCore \
           GraphWindowCore

GraphWindowCore.depends = QGVCore
