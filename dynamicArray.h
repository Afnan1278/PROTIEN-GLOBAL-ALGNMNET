#include <iostream>
#include <cstdlib>

using namespace std;

class dynamicArray{
	private:
		int ncols;
		int nrows;
		int **arr;
	public:
		dynamicArray(){
			nrows=0;
			ncols=0;
			arr=0;
		}

		dynamicArray(int row, int col){
			nrows=row;
			ncols=col;
			arr = new int*[nrows];
			for( int i = 0 ; i < nrows ; i++ ){
				arr[i] = new int[ncols];
			}
		}
	
		~dynamicArray(){
			if (arr != 0){
				for (int i=nrows-1; i>=0; i--){
					if (arr[i] != 0)
						delete arr[i];
					arr[i] = 0;
				}
				delete [] arr;
			}
			arr = 0;
		}
		
		void fillArray(int value,int i,int j){
					arr[i][j] = value;
		}
		
		int get_rows () {
			return nrows;
		}
		
		int get_cols () {
			return ncols;
		}
		
		int &operator ()(int i, int j){
			if(i<0 || i> nrows-1 || j<0 || j> ncols-1 ) {
				cout << "Boundary Error\n";
				exit(1);
			}
			return arr[i][j];
		}
		
		dynamicArray(const dynamicArray& rhs){
			nrows = rhs.nrows;
			ncols = rhs.ncols;
			arr = new int*[nrows];
			for( int i = 0 ; i < nrows ; i++ ){
				arr[i] = new int [ncols];
				memcpy(arr[i],rhs.arr[i],sizeof(int)*ncols);
			}
		}
		
		dynamicArray& operator=(const dynamicArray& rhs){
			if (this == &rhs){
				return *this;
			}
			nrows = rhs.nrows;
			ncols = rhs.ncols;
			arr = new int*[nrows];
			for( int i = 0 ; i < nrows ; i++ ){
				arr[i] = new int [ncols];
				memcpy(arr[i],rhs.arr[i],sizeof(int)*ncols);
			}
			return *this;
		}
		void set_size(int r,int c)
		{
			nrows=r;
			ncols=c;
			arr = new int*[nrows];
			for( int i = 0 ; i < nrows ; i++ ){
				arr[i] = new int[ncols];
			}
			
		}
	
};

