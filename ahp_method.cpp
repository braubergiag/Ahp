#include "ahp_method.h"


ahp_method::ahp_method(QVector<CriteriaMatrix*> *alternative_vec, CriteriaMatrix *criteria_matrix)
{
    m_alternative_vec = alternative_vec;
    m_criteria_matrix = criteria_matrix;
}

Decision ahp_method::gm_method()
{
    const int alter_num = m_alternative_vec->at(0)->getRows();
    const int criter_num = m_criteria_matrix->getRows();
    MatrixXd matrix_weights,matrix_powers,matrix_norm_weights;
    VectorXd crit_vector = VectorXd::Ones(criter_num);
    VectorXd final_weights= VectorXd::Ones(alter_num);


    matrix_weights.setZero(alter_num,criter_num);
    matrix_powers.setZero(alter_num,criter_num);
      matrix_norm_weights.setZero(alter_num,criter_num);

      for (int i = 0; i < criter_num; ++i) {
         crit_vector(i) =  pow(m_criteria_matrix->getMatrix().row(i).prod(), 1./criter_num);
          for (int j =0; j < alter_num; ++j){
               matrix_weights(j,i) = pow(m_alternative_vec->at(i)->getMatrix().row(j).prod(),1./alter_num);
          }


      }
      double critVectorSum = crit_vector.sum();
      for (int i = 0; i < criter_num; ++i) {
          crit_vector(i) = crit_vector(i) / critVectorSum;
          for (int j = 0; j < alter_num; ++j) {
              matrix_norm_weights(j, i) = matrix_weights(j, i) / matrix_weights.col(i).sum();

          }
      }

      for (int i = 0; i < criter_num; ++i){
          for (int j = 0; j < alter_num; ++j) {
          matrix_powers(j,i) = pow(matrix_weights(j,i),crit_vector(i));
          }
      }
      for (int i =0; i < criter_num; ++i){
          for (int j =0; j < alter_num; ++j)
            final_weights(j) *= matrix_powers(j,i);
      }
      double finalVectorSum = final_weights.sum();
      for (int i =0; i < final_weights.size();++i)
          final_weights(i) /= finalVectorSum;

      Decision d(matrix_weights,final_weights);
      return d;


}

Decision ahp_method::simpleSum_method()
{
    const int alter_num = m_alternative_vec->at(0)->getRows();
    const int criter_num = m_criteria_matrix->getRows();
    MatrixXd matrix_weights,matrix_norm_weights,matrixCriterWeighted;
    VectorXd crit_vector = VectorXd::Ones(criter_num);
    VectorXd final_weights= VectorXd::Ones(alter_num);
    MatrixXd tempMatrix;
    tempMatrix.setZero(alter_num,alter_num);
    matrix_weights.setZero(alter_num,criter_num);
    matrix_norm_weights.setZero(alter_num,criter_num);
    matrixCriterWeighted.setZero(criter_num,criter_num);

    for (int i = 0; i < criter_num; ++i) {
        double sumCriteriaWeights = m_criteria_matrix->getMatrix().col(i).sum();

        for (int j =0; j < alter_num; ++j){
            double sumAlternativeColWeight = m_alternative_vec->at(i)->getMatrix().col(j).sum();
            for (int k = 0; k < alter_num; ++k){
                tempMatrix(j,k) =  m_alternative_vec->at(i)->getMatrix().col(j)(k) / sumAlternativeColWeight;
            }
            matrixCriterWeighted(j,i) /= sumCriteriaWeights;
        }
        for (int k = 0; k < alter_num; ++k)
            matrix_weights(i,k)
                = tempMatrix.row(k).sum();



    }
    for (int i =0 ; i < criter_num; ++i)
        crit_vector(i) = matrixCriterWeighted.row(i).sum();
        for (int j =0; j < alter_num; ++j){

            for (int k = 0; k < alter_num; ++k){
                matr
        }


    }



}

Decision ahp_method::weightetSum_method()
{

}



MatrixXd ahp_method::gm_method_matrix_test()
{
    // Cтраница 166
    const int alter_num = 4;
    const int criter_num = 2;
    MatrixXd matrixA_1(alter_num,alter_num),matrixA_2(alter_num,alter_num);
MatrixXd matrix_weights,matrix_norm_weights;
matrix_weights.setZero(alter_num,criter_num);
  matrix_norm_weights.setZero(alter_num,criter_num);

     matrixA_1 << 1, 3, 7, 9,
                  1./3 ,1 ,6, 7,
                  1./7, 1./6, 1, 3,
                  1./9 ,1./7, 1./3, 1;
     matrixA_2 << 1 ,1./5, 1./6, 1./4,
                  5, 1, 2 ,4,
                  6 ,1./2 ,1, 6,
                  4 ,1./4, 1./6 ,1;
     QVector<MatrixXd> vec;
     vec.push_back(matrixA_1);
     vec.push_back(matrixA_2);


       for (int i = 0; i < criter_num; ++i) {
           //cout << pow(matrixA.row(i).prod(), 0.25) << endl;
           for (int j =0; j < alter_num; ++j){
                matrix_weights(j,i) = pow(vec.at(i).row(j).prod(),1./alter_num);
           }


       }
//       for (int i = 0; i < criter_num; ++i) {
//           for (int j = 0; j < alter_num; ++j) {
//               matrix_norm_weights(j, i) = matrix_weights(j, i) / matrix_weights.col(i).sum();

//           }
//       }
       return matrix_weights;
}

Decision ahp_method::perform_ahp()
{
    const int alter_num = m_alternative_vec->at(0)->getRows();
    const int criter_num = m_criteria_matrix->getRows();
    MatrixXd matrix_weights,matrix_norm_weights;

    VectorXd crit_vector = VectorXd::Ones(criter_num);
    VectorXd final_weights = VectorXd::Ones(alter_num);
    EigenSolver<MatrixXd> critEigSolver(m_criteria_matrix->getMatrix());
    matrix_weights.setZero(alter_num,criter_num);
      matrix_norm_weights.setZero(alter_num,criter_num);
    double lambda = 0;
    QVector<EigenSolver< MatrixXd >>  VEC;
    for (int i = 0; i < criter_num; ++i) {
           crit_vector(i) = abs(real(critEigSolver.eigenvectors().col(0)(i, 0)));

           VEC.push_back(EigenSolver<MatrixXd>(m_alternative_vec->at(i)->getMatrix()));
           for (int j = 0; j < alter_num; ++j) {
               matrix_weights(j,i) = abs(real(VECat(i).eigenvectors().col(0)(j, 0)));
           }
       }
       double critVectSum = crit_vector.sum();
       for (int i = 0; i < criter_num; ++i) {
           crit_vector(i) /= critVectSum;
           for (int j = 0; j < alter_num; ++j) {
               matrix_norm_weights(j, i) = matrix_weights(j, i) / matrix_weights.col(i).sum();

           }
       }
       final_weights = matrix_norm_weights * crit_vector;
       Decision d(matrix_norm_weights,final_weights);
       return d;





}


