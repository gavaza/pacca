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

typedef  QList<QVariantList> list_behavior;

typedef QMap<int,list_behavior> StatisticMap;

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
    void setPermutationList(QList<QVariantList> permutation_list);
    void setPermutationSize(int nPermutations);
    void setEvents(QList<QVariantList> events);
    void setIndexes(QList< QList<int> > indexes);
    void setTailedAlpha(int tailed, double alpha);
    void setFilterPvalue(bool filter);

    QVector<QString> getLabels();
    QVector<QString> getInfos();
    QVector<double> getTicks();
    QList<double> getE();
    QList<double> getO();
    QList<double> getR();
    QList< QPair<double,double> > getP();
    bool getFilterPvalue();
    bool getStopThreadStatus();
    void setStopThreadStatus(bool stop);


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
    double R_unnamed(list_behavior u, list_behavior behavior);

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
    QPair<double, double> V(list_behavior u,
             list_behavior behavior,
             enum types_of_variances type);



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
    QList< QVariantList > bootstrap(QVariantList events, QList<int> indexes, int nsamples);

    double P_all(list_behavior u, list_behavior behavior);


private:
    void calcPermutation();
    unsigned int elements(int size_u, int size_behavior);
    char typeRun;
    list_behavior sessions;
    QList<list_behavior> sequences;
    QList<QVariantList> permutation_list;
    int nPermutations;
    QList< QVariantList > events;
    QList< QList<int> > indexes;
    QVector<QString> sessionsLabels;
    QVector<QString> infos;
    QVector<double> sessionsTicks;
    QList<int> sessionsSubjects;
    QList<double> dataE;
    QList<double> dataO;
    QList<double> dataR;
    QList< QPair<double,double> > dataP;
    int stepSize;
    int stepStart;
    bool absolute;
    bool dynamic;
    int tailed;
    double alpha;
    bool filterPvalue;
    bool stopThread;


signals:
    void dataProcessed();
    void statusProcess(double);
    void threadStopped();

};

#endif // STATISTICS_H
