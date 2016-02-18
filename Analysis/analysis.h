#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <QWidget>
#include <QList>
#include <QVector>
#include <QColor>
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>
#include <QSplashScreen>
#include <cmath>
#include <QDebug>

#include "database.h"
#include "qcustomplot.h"
#include "action.h"
#include "dialogselectsession.h"
#include "statistics.h"
#include "viewtablestats.h"
#include "dialogconfigstats.h"
#include "graph.h"
#include "plotwindow.h"
#include "phylogenetic.h"
#include "viewphylogenetics.h"

#include "analysis_global.h"


namespace Ui {
class Analysis;
}
/*!
 * \brief A class to control the Analysis window.
 * This class is resposible for control th Analysis window.
 * In this window the user can select session and apply statistical methods.
 */
class ANALYSISSHARED_EXPORT AnalysisWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit AnalysisWindow(QMdiArea *mdi, unsigned int nwin, QWidget *parent = 0);
    ~AnalysisWindow();
    
private:
    Ui::Analysis *ui;
    unsigned int nwin;
    QMdiArea *mdi;
    QList<QListWidget*> sequences;
    /*!
     * \brief List of all events presents in the selected sessions.
     */
    QSet<QString> events;
    /*!
     * \brief List of all QTableWidget created for select the sequence.
     */
    QList<QTableWidget*> table_op;
    /*!
     * \brief Connect the signals and slots.
     */
    void createConnection();
    /*!
     * \brief Checks if a session was already selected.
     * \param id of the session
     * \return Return true if the session was already selected, else return false.
     */
    bool checkDuplicated(int id);
    /*!
     * \brief Fills a specific page (QTableWidget) with the events.
     * \param page The number of the specific page.
     */
    void fillPagesSeq(int page);
    /*!
     * \brief Fills all pages with the events.
     */
    void fillPagesSeq();
    /*!
     * \brief Fills the set of events.
     * Fills the set of events with all events of the selected sessions.
     */
    void fillSetEvents();
    PlotWindow* showHistogram(QVector<double> data, QVector<double> ticks, QPair<double, double> variances,
                      QVector<QString> labels, QString labX, QString labY, QString title, QColor color);
    PlotWindow *showStackHistogram(QVector<double> lower, QVector<double> upper, QVector<double> ticks,
                      QVector<QString> labels, QString labX, QString labY, QString title, QColor lColor, QColor uColor);
    PlotWindow *showFrequenceStats(QVariantList data, QString xlabel, QString title, QString legend, bool sorted);
    void permutation(QStringList ev, QList<int> list, int i, int n);
    void preparePhylogenetic(Phylogenetic *module);

    QList<QVariantList> permutation_list;
    QList< QVariantList > bootstrap_list;
    Statistics* statsModule;
    Phylogenetic* phyloModule;

//subwindow control
    QMdiSubWindow* phyloSW;

//statistics configuration
    DialogConfigStats* config;
    bool hasData;
    bool hasPhyloData;
    bool showMean;
    bool showVariance;
    bool showLegend;
    bool withZeros;
    bool filterPvalue;
    unsigned int showtype;
    unsigned int testType;
    int tailed;
    int nPermutations;
    double alfa;
    QColor colorFrequence;
    QColor colorObserved;
    QColor colorExpected;
    QColor colorResidue;
    QColor colorLower;
    QColor colorUpper;
    QColor colorMean;
    QColor colorVar;

    QList<QList<double> > calc_statistics(list_behavior set_us, list_behavior behaivors);

private slots:
    void hideSubWindow(QMdiSubWindow* w);
    /*!
     * \brief Shows the DialogSelectSession and include the selected sessions.
     */
    void addSession();
    /*!
     * \brief Removes a session from the analysis.
     */
    void removeSession();
    /*!
     * \brief Shows the sequence of events from a specific session.
     */
    void loadSequence();
    /*!
     * \brief Checks the conditions for initiate a analysis.
     */
    void checkConditions();
    /*!
     * \brief Creates a new page.
     * \param size Represents the size of the sequence.
     */
    void createPagesSeq(int size);
    /*!
     * \brief Add the events selected for compose the matrix.
     */
    void addSelectedSeq();
    /*!
     * \brief Generate the events selected for compose the matrix.
     */
    void genSelectedSeq();
    /*!
     * \brief Removes a set of events selected previously.
     */
    void delSelectedSeq(int index);
    /*!
     * \brief Plot stats about all sessions included in the analysis.
     * Actualy this method plots the absolut frequency of the events.
     */
    void genRandomSequence();
    void showSessionStats();
    void showSequenceStats();
    void showPermutationStats();
    void showData(QList<double> tmp_E, QList<double> tmp_O, QList<double> tmp_Rs,
                  QMap<int, QPair<double, double> > VE,
                  QMap<int, QPair<double, double> > VO,
                  QMap<int, QPair<double, double> > VR,
                  QVector<QString> tmp_sessionsLabels, QVector<QString> tmp_infos, int s,
                  QList< QPair<double,double> > Ps = QList< QPair<double,double> >());
    void showGraphicStats(QList<double> E, QList<double> O, QList<double> R,
                          QVector<QString> sessionsLabels, QVector<QString> infos,
                          QVector<double> sessionsTicks,
                          QList<double> pvalues = QList<double>());
    void saveCsvStats(QList<double> E, QList<double> O, QList<double> R,
                      QVector<QString> sessionsLabels, QVector<QString> infos,
                      QList<double> pvalues = QList<double>());
    void showTableStats(QList<double> E, QList<double> O, QList<double> R,
                        QMap<int, QPair<double,double> > VE,
                        QMap<int, QPair<double,double> > VO,
                        QMap<int, QPair<double,double> > VR,
                        QVector<QString> sessionsLabels, QVector<QString> infos, int n,
                        QList<double> pvalues = QList<double>());
    void showNetStats(QList<double> E, QList<double> O, QList<double> R,
                      QVector<QString> sessionsLabels, QVector<QString> infos,
                      QList<double> pvalues = QList<double>());
    void setConfig();
    void refreshConfig();
    void drawSessionGraph();
    void statisticsTests();
    void showProcessedDataPermutation();
    void cancelProcessPermutation();
    void updateProgressPemutation(double p);
    void refreshTableEvents();

    void showProcessedDataPhylo();
    void cancelProcessPhylo();
    void updateProgressPhylo(double p);

    void refreshSpeciesList();
    void upSpecie();
    void downSpecie();
    void showPhyloMtx();

};

#endif // ANALYSIS_H
