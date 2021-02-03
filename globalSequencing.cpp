#include <iostream>
#include <cstring>
#include <fstream>
#include "dynamicArray.h"
#include "Stack.h"

using namespace std;

class sequences {
	private:
		string sequence_A;
		string sequence_B;
	public:
		
		sequences () {
			
		}
		
		sequences (string a,string b) {
			sequence_A=a;
			sequence_B=b;
		}
		
		sequences (const sequences &rhs) {
			sequence_A=rhs.sequence_A;
			sequence_B=rhs.sequence_B;
		}
		
		sequences& operator = (const sequences &rhs) {
			if (this==&rhs) {
				return (*this);
			}
			else {
				sequence_A=rhs.sequence_A;
				sequence_B=rhs.sequence_B;
				return (*this);
			}
		}
		
		void set_sequence_A (string a) {
			sequence_A=a;
		}
		
		void set_sequence_B (string a) {
			sequence_B=a;
		}
		
		string get_sequence_A () {
			return sequence_A;
		}
		
		string get_sequence_B () {
			return sequence_B;
		}
		int get_lenth_A()
		{
			return sequence_A.size();
		}
		int get_lenth_B()
		{
			return sequence_B.size();
		}
		
		friend ostream& operator << (const ostream &obj,const sequences &rhs);
		
};
      ostream& operator << (const ostream &obj,const sequences &rhs) {
			cout << "Sequence A: " << rhs.sequence_A << endl << "Sequence B: " << rhs.sequence_B << endl;
		}

class globalSequencing {
	private:
		int n, m;
		int match_score, mismatch_score, gap_score;
		string A, B,retC;
		dynamicArray  s_matrix;
		int match_count;
	public:
		
		globalSequencing () {
			match_score = 2;
			mismatch_score = 1;
			gap_score = 1;
			match_count = 0;
		}
		
		void set_data (sequences obj) {
			A=obj.get_sequence_A();
			B=obj.get_sequence_B();
			n=A.length();
			m=B.length();
			s_matrix.set_size(n+1,m+1);
		}
		int get_match()
		{
			return match_count;
		}
		
		int similarity_score ()
		{
			for (int i=0;i<=n;i++) {
				s_matrix(i,0)  = -i * gap_score;
			}
			for (int i=0;i<=m;i++) {
				s_matrix(0,i)  = -i * gap_score;
			}
			for (int i=1;i<=n;i++) {
			    for (int j=1;j<=m;j++) {
			        int S;
					if (A[i-1] == B[j-1]) {
						S=match_score;
					}
					else {
						S=-mismatch_score;
					}
			        s_matrix(i,j) = max(s_matrix(i-1,j-1) + S, max(s_matrix(i-1,j) - gap_score, s_matrix(i,j-1) - gap_score));
			    }
			}
			return s_matrix(n,m);
		}
			
		sequences optimal_alignment()
		{
			n = A.length(), m = B.length();
			string retA, retB;
			stack <char> SA, SB,SC;
			int i = n, j = m;
			while (i != 0 || j != 0) {
			    if (i == 0) {
			        SA.push('-');
			        SB.push(B[j-1]);
			        SC.push(' ');
			        j--;
			    }
			    else if (j == 0) {
			        SA.push(A[i-1]);
			        SB.push('-');
			        SC.push(' ');
			        i--;
			    }
			    else {
			        int S,S1=0;
					if (A[i-1] == B[j-1]) {
						S=match_score;
						match_count++;
					}
					else {
						S1=-mismatch_score;
						S=0;
					} 
			        if (s_matrix(i,j) == s_matrix(i-1,j-1) + S) {
			            SA.push(A[i-1]);
			            SB.push(B[j-1]);
			            SC.push('|');
			            i--;
						j--;
			        }
			        else if(s_matrix(i,j) == s_matrix(i-1,j-1) + S1) {
			            SA.push(A[i-1]);
			            SB.push(B[j-1]);
			            SC.push('.');
			            i--;
						j--;
			        }
			        else if (s_matrix(i-1,j) > s_matrix(i,j-1)) {
			            SA.push(A[i-1]);
			            SB.push('-');
			            SC.push(' ');
			            i--;
			        }
			        else {
			            SA.push('-');
			            SB.push(B[j-1]);
			            SC.push(' ');
			            j--;
			        }
			    }
			}
			while (!SA.isEmpty()) {
			    retA += SA.pop();
			    retB += SB.pop();
			    retC += SC.pop();
			}
			sequences obj(retA,retB);
			return obj;
		}
		string get_dashes()
		{
			return retC;
		}
		
};

int main()
{
	int lenth_A,lenth_B,match_count;
	sequences obj1;
	globalSequencing obj;
	fstream input("input.txt");
	string seq1,seq2;
	input>>seq1;
	input>>seq2;
	obj1.set_sequence_A(seq1);
	obj1.set_sequence_B(seq2);
	obj.set_data(obj1);
	cout << obj1 << endl;
	int a=obj.similarity_score();
    cout << "Similarity Score: " << a << endl;
    sequences alignment = obj.optimal_alignment();
    cout << "Alignment of Sequence A: " << alignment.get_sequence_A() << endl;
    cout << "                         " << obj.get_dashes() << endl;
    cout << "Alignment of Sequence B: " << alignment.get_sequence_B() << endl;
    lenth_A=obj1.get_lenth_A();
    lenth_B=obj1.get_lenth_B();
    match_count=obj.get_match();
    cout << endl << "Similarity percentage is " << (match_count*100/max(lenth_A,lenth_B)) << "%" <<endl;
    cout << endl << " PREDICTION:" << endl;
    if((match_count*100/max(lenth_A,lenth_B))>=60)
    {
    	cout<<"sequences shares common evolutionary origin (does the same function)";
	}
	else 
	cout<<"does not show homology";
}
