TEMPLATE = subdirs

SUBDIRS += Text \
           GraphWindow \
           Statistics \
           Phylogenetic \
           Database \
           DatabaseControl \
           Video \
           PlotWindow \
           Audio \
           Analysis \
           Application \

Application.depends = Text
Application.depends = Analysis
Application.depends = DatabaseControl
Application.depends = Video
Application.depends = Audio
Application.depends = Analysis

Analysis.depends = GraphWindow
Analysis.depends = Phylogenetic
Analysis.depends = Statistics
Analysis.depends = DatabaseControl
Analysis.depends = Database

Text.depends = Database
DatabaseControl.depends = Database
Video.depends = Database
