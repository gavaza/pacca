TEMPLATE = subdirs

SUBDIRS += QGVCore \
           GraphWindowCore \
           Graph

Graph.depends = GraphWindowCore
GraphWindowCore.depends = QGVCore
