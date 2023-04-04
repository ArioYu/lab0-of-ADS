#include <fstream>
#include <stdexcept>
#include <iostream>
#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(const std::string input_file) {
  /* TODO: Your code here. */
  std::ifstream infile(input_file,std::ios::in);
  infile>>_row;
  infile>>_col;
  int a,b,c;
  int tmp=0;
  Ap.push_back(0);
  while(!infile.eof()&&infile>>a&&infile>>b&&infile>>c){
  Ax.push_back(c);
  Aj.push_back(b);
  _num++;
  
  if(a!=tmp){
    for(int i=tmp+1;i<a+1;++i) {
    Ap.push_back(_num-1);
}
    
  }
  tmp=a;
  }
  Ap.push_back(_num);
  for(int i=tmp+1;i<_row;++i) {
    Ap.push_back(_num);
}
  return;
}

void SparseMatrix::to_file(const std::string output_file) {
  /* TODO: Your code here. */
  std::ofstream outfile(output_file,std::ios::out);
  outfile<<_row<<" "<<_col<<std::endl;
  Triple tri;
  int num=0;
  //std::cout<<Ap.size();
  for(int i=0;i<Ap.size()-1;++i){
    int k=Ap.at(i+1)-Ap.at(i);
    while(k>0){
      outfile<<i<<" "<<Aj[num]<<" "<<Ax[num]<<std::endl;
      num++;
      k--;
    }
  }
  return;

}

SparseMatrix SparseMatrix::operator*(const SparseMatrix &right) {
 /* TODO: Your code here. */
  int row,col;//生成矩阵的行数列数
  
  SparseMatrix rs;
  rs._row=_row;
  rs._col=right._col;

  std::vector<int>Bp=right.Ap;
  std::vector<int>Bx=right.Ax;
  std::vector<int>Bj=right.Aj;
  std::vector<int> next(rs._col,-1);
  std::vector<int> sums(rs._col, 0);
    int nnz = 0;

    rs.Ap.push_back(0);

    for(int i = 0; i < rs._row; i++){
        int head   = -2;
        int length =  0;

        int jj_start = Ap.at(i);
        int jj_end   = Ap[i+1];
        for(int jj = jj_start; jj < jj_end; jj++){
            int j = Aj[jj];
            int v = Ax[jj];
            int kk_start = Bp[j];
            int kk_end   = Bp[j+1];
            for(int kk = kk_start; kk < kk_end; kk++){
                int k = Bj[kk];

                sums[k] += v*Bx[kk];

                if(next[k] == -1){
                    next[k] = head;
                    head  = k;
                    length++;
                }
            }
        }
        std::vector<int> array,array1;
        for(int jj = 0; jj < length; jj++){

            if(sums[head] != 0){
                //rs.Aj.push_back(head);
                array.push_back(head);
                //rs.Ax.push_back( sums.at(head));
                //std::cout<<head<<std::endl;
                array1.push_back(sums.at(head));
                nnz++;
            }

            int temp = head;
            head = next[head];

            next[temp] = -1; //clear arrays
            sums[temp] =  0;
        }
        
        while(array.size()!=0){
          int m=0;
          int num=array[0];
          for(int n=0;n<array.size();++n){
            if(array[n]<num){
            num=array[n];
            m=n;}}
          //std::cout<<num;
          rs.Aj.push_back(array.at(m));
          rs.Ax.push_back(array1.at(m));
          array.erase(array.begin()+m);
          array1.erase(array1.begin()+m);}
        
  rs.Ap.push_back(nnz);
  //std::cout<<nnz<<std::endl;
  }
  return rs;
}