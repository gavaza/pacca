#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include <QThread>
#include <QSettings>
#include <QTime>
#include <QString>
#include <QList>
#include <QVariantList>
#include <QVariant>
#include <QDebug>
#include <QRegExp>
#include <QtCore/qmath.h>
#include <QLinkedListIterator>
#include <QQueue>
#include <QMap>
#include <QMultiMap>

#ifndef STATISTICS_VARIABLES
const char SEPARATE_REGEX=';';
#define STATISTICS_VARIABLES
#endif // STATISTICS_VARIABLES

typedef QList<QVariantList> list_behavior;
typedef QList<QVariantList> behaviors;
typedef QMap<int,QVariantList> StatisticMap;

enum types_of_variances{
    Residue,
    Observed,
    Expected,
    Probability
};

Q_DECLARE_METATYPE(list_behavior)

class Statistics : public QThread
{
    Q_OBJECT
public:
    Statistics(bool dynamic=false, bool absolute=false, int step=1, int start=1);
    ~Statistics();
    void run();
    void setTypeRun(char typeRun);
    void setSessions(list_behavior sessions, QList<int> sessionsSubjects);
    void setSequences(QList<list_behavior> sequences);
    void setPermutationList(QList<list_behavior> permutation_list);
    void setPermutationSize(int nPermutations);
    void setEvents(QList<QVariantList> events);
    void setIndexes(QList< QList<int> > indexes);
    void setTailedAlpha(int tailed, double alpha);
    void setFilterPvalue(bool filter);
    void setSessionsLabels(QVector<QString> labels);
    void setUS(QList<QString> us);
    void setSizeU(int size);

    QVector<QString> getLabels();
    QList<QVector<QString> > getInfos();
    QVector<QString> getInfos(int i);
    QVector<double> getTicks();
    QList<double> getE(int i);
    QList<double> getO(int i);
    QList<double> getR(int i);
    QMap<int, QPair<double,double> > getVE(int i);
    QMap<int, QPair<double,double> > getVO(int i);
    QMap<int, QPair<double,double> > getVR(int i);
    QList< QPair<double,double> > getP(int i);
    QList<QList<double> > getE();
    QList<QList<double> > getO();
    QList<QList<double> > getR();
    QList<QMap<int, QPair<double,double> > > getVE();
    QList<QMap<int, QPair<double,double> > > getVO();
    QList<QMap<int, QPair<double,double> > > getVR();
    QList<QList< QPair<double,double> > > getP();
    list_behavior getUs(int i);
    QList<list_behavior> getUs();
    bool getFilterPvalue();
    bool getStopThreadStatus();
    void setStopThreadStatus(bool stop);
    int getPermutationSize();
    void combinations(QList<QString> V, int depth, int expected_length,
                   QList<QString> combination = QList<QString>());

    /*!
     * \brief R
     * \param u
     * \param behavior
     * \param absolute
     * \return
     */
    double R(list_behavior u,
             QVariantList behavior);
    /*!
     * \brief R
     * \param u
     * \param behavior
     * \param absolute
     * \return
     */
    QList<double> R(list_behavior u,
                    list_behavior behavior);
    /*!
     * \brief R for all sessions
     * \param u
     * \param behavior
     * \param absolute
     * \return
     */

    double R_unnamed(list_behavior u, StatisticMap behavior);

    double R_all(list_behavior u,
                    list_behavior behavior);

    /*!
     * \brief V
     * \param u
     * \param behavior
     * \param absolute
     * \return
     */
    QMap<int, QPair<double, double> > V_Map(list_behavior u,
             StatisticMap behavior,
             enum types_of_variances type);

    /*!
     * \brief V
     * \param u
     * \param behavior
     * \param absolute
     * \return
     */
    QPair<double, double> V(list_behavior u,
             StatisticMap behavior,
             enum types_of_variances type);

    /*!
     * \brief V
     * \param u
     * \param behavior
     * \param absolute
     * \return
     */
    QPair<double, double> V(QMap<int, QPair<double, double> > M);

    /*!
     * \brief E calculate the expected value of u in behavior
     * \param u
     * \param behavior
     * \return
     */
    double E(list_behavior u,
             QVariantList behavior);

    QList<double> E(list_behavior u,
                    list_behavior behavior);

    double E_all(list_behavior u,
                 list_behavior behavior);

    /*!
     * \brief P calculate the probability of u in behavior (in revision)
     * \param u
     * \param behavior
     * \return
     */
    double P(QVariantList u,
             QVariantList behavior);

    double P(QVariantList u,
             list_behavior behavior);

    double P(list_behavior u,
             QVariantList behavior);

    QList<double> P(list_behavior u,
             list_behavior behavior);

    QMap<QVariant, int> frequence(QVariantList list);
    QMap<QVariant, int> frequence(QVariantList list, int nbars);
    QList<double> O(list_behavior u, list_behavior behavior);
    double O_all(list_behavior u, list_behavior behavior);
    double O(list_behavior u, QVariantList behavior);
    QPair<double, double> V(QList<double> list);
    QPair<double, double> V(QVariantList list);

    QPair<double,double> pvalue(double value, QList<double> distribution);
    QList< QPair<double,double> > pvalue(QList<double> values, QList<double> distribution);
    QList< QVariantList > bootstrap(QVariantList events, int nsamples);
    QList<QVariantList> bootstrap(QVariantList events, QList<int> indexes, int nsamples);

    double P_all(list_behavior u, list_behavior behavior);

    QList<list_behavior> getPermutation_us();
    QPair<bool,double> isSignificativePvalue(QPair<double,double> pv);
    QList< QPair<bool,double> > isSignificativePvalue(QList< QPair<double,double> > list_pv);

    QList<StatisticMap> randomize(StatisticMap sessions);
private:
    void calcPermutation();
    unsigned int elements(int size_u, int size_behavior);
    char typeRun;
    list_behavior sessions;
    QList<list_behavior> sequences;
    QList<list_behavior> permutation_list;
    int nPermutations;
    QList< QVariantList > events;
    QList< QList<int> > indexes;
    QVector<QString> sessionsLabels;
    QList<QVector<QString> > infos;
    QVector<double> sessionsTicks;
    QList<int> sessionsSubjects;
    QList<QList<double> > dataE;
    QList<QList<double> > dataO;
    QList<QList<double> > dataR;
    QList<list_behavior> set_us;
    QList<QMap<int, QPair<double,double> > > VE;
    QList<QMap<int, QPair<double,double> > > VO;
    QList<QMap<int, QPair<double,double> > > VR;

    QList<QList< QPair<double,double> > > dataP;
    QList<QString> us;
    int size_u;

    int stepSize;
    int stepStart;
    bool absolute;
    bool dynamic;
    int tailed;
    double alpha;
    bool filterPvalue;
    bool stopThread;
    int totalEventsPermutations;

public slots:
    void updateAbsolute(bool absolute);
    void updateDynamic(bool dynamic);
    void updateStepStart(int stepStart);
    void updateStepSize(int stepSize);
    void calcPermutationEvents();

signals:
    void dataProcessed();
    void statusProcess(double);
    void threadStopped();
    void dataEventsProcessed();
    void statusEventsProcess(double);

};
#endif // STATISTICS_H
