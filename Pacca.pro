TEMPLATE = subdirs

SUBDIRS += QGVCore \
           GraphWindow \
           Statistics \
           Phylogenetic \
           Database \
           DatabaseControl \
           Video \
           PlotWindow \
           Application

Application.depends = GraphWindow
Application.depends = Statistics
Application.depends = Phylogenetic
Application.depends = Video
Application.depends = DatabaseControl
Application.depends = PlotWindow
GraphWindow.depends = QGVCore
DatabaseControl.depends = Database
Video.depends = Database
