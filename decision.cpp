#include "decision.h"

  QMap<QStringList,VectorXd> Decision::sortAlternatives(QStringList alternatives){
    QMap<QStringList,VectorXd> decision;

for (int i = 0; i < m_critWeights.size(); ++i)
{
    double crit_weight = m_critWeights[i];
    QString altern =  alternatives[i];
    int j = i - 1;
    while (j >= 0 and crit_weight >m_critWeights[j])
    {
       m_critWeights[j + 1] = m_critWeights[j];
       alternatives[j + 1] = alternatives[j];
        j -= 1;
    }
   m_critWeights[j + 1] = crit_weight;
   alternatives[j + 1] = altern;
}
    decision.insert(alternatives,m_critWeights);
    return decision;
}
