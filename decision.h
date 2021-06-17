#ifndef DECISION_H
#define DECISION_H
#include <QVector>
#include <QDebug>
#include "criteria.h"
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

class Decision
{
    MatrixXd m_weights;
    VectorXd m_critWeights;
public:
    Decision(MatrixXd weights,VectorXd critWeights):
        m_weights(weights),m_critWeights(critWeights){};
    MatrixXd getMatrix() const {return m_weights;};
    VectorXd getWeights() const {return m_critWeights;};
    VectorXd sortWeights() const;
   QMap<QStringList,VectorXd> sortAlternatives(QStringList alternatives);
};

#endif // DECISION_H
