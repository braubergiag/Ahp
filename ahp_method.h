#ifndef AHP_METHOD_H
#define AHP_METHOD_H

#include <QVector>
#include <QDebug>
#include "criteria.h"
#include "decision.h"
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
class ahp_method
{
    QVector<CriteriaMatrix*> * m_alternative_vec;
     CriteriaMatrix * m_criteria_matrix;
public:
     ahp_method(QVector<CriteriaMatrix*> * alternative_vec, CriteriaMatrix * criteria_matrix);
     ahp_method(){};
     Decision gm_method();
     Decision simpleSum_method();
     Decision weightetSum_method();
     VectorXd gm_method_test();
     MatrixXd gm_method_matrix_test();
     Decision perform_ahp();
     MatrixXd perform_test();
};

#endif // AHP_METHOD_H
