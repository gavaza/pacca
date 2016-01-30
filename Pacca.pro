TEMPLATE = subdirs

SUBDIRS += QGVCore \
           GraphWindow \
           Statistics \
           Phylogenetic \
           Database \
           DatabaseControl \
           Video \
           PlotWindow \
           Application \
           Text

Application.depends = GraphWindow
Application.depends = Statistics
Application.depends = Phylogenetic
Application.depends = Video
Application.depends = DatabaseControl
Application.depends = PlotWindow
Application.depends = Text
GraphWindow.depends = QGVCore
DatabaseControl.depends = Database
Video.depends = Database
