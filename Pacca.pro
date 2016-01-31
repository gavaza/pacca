TEMPLATE = subdirs

SUBDIRS += Text \
           GraphWindow \
           Statistics \
           Phylogenetic \
           Database \
           DatabaseControl \
           Video \
           PlotWindow \
           Application \           
           Analysis

Application.depends = Text
Application.depends = Analysis
Application.depends = DatabaseControl
Application.depends = Video

#Application.depends = GraphWindow
#Application.depends = Statistics
#Application.depends = Phylogenetic
#Application.depends = PlotWindow

Analysis.depends = GraphWindow
Analysis.depends = Phylogenetic
Analysis.depends = Statistics
Analysis.depends = DatabaseControl
Analysis.depends = Database

#GraphWindow.depends = QGVCore

DatabaseControl.depends = Database

Video.depends = Database
