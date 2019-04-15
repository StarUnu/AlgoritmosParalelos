#include <iostream>
#include<stdlib.h>
#include<time.h>
#include <ctime>

using namespace std;



void matriz_randon(int ** & matriz_a, int fil, int col){
	
	for(int i=0;i<fil;i++)
	{
		for(int j=0;j<col;j++){
			int num=1+rand()%(101-1);
			matriz_a[i][j]=num;

		}
	}
}

void mostrar_matris(int ** & matriz_a,int fil,int col){
	for(int i=0;i<fil;i++)
	{
		for(int j=0;j<col;j++){
			cout<<matriz_a[i][j]<<" ";
		}
		cout<<endl;
	}	
}


void multiplicacion(int ** & matriz_result,int ** matriz_a,int ** matriz_b,int fil,int col){
	for(int i=0;i<fil;i++){
		for(int j=0;j<col;j++){
			for(int k=0;k<col;k++){
				matriz_result[i][j]+=matriz_a[i][k]*matriz_b[k][j];
			}
			//cout<<"multiplicacion sub deveras"<<matriz_result[i][j]<<endl;
		}
	}
}

void multiplicacionbloques(int ** A,int ** B,int **C, int n)
    {
    	//cout<<"el tamano ="<<n<<endl;
        const int BLOCK = 10;
        for (int I = 0; I < n; I += BLOCK) {///completa las filas a llenar
            for (int J = 0; J < n; J += BLOCK) {//completa la columna en llenar
                for (int K = 0; K < n; K += BLOCK) {//es para multiplicar con los cuadros pequeños
                	//aqui completa la multiplicacion de la fila con la columna
                    
                    for (int i = I; i < I + BLOCK && i < n; ++i) {
                        for (int j = J; j < J + BLOCK &&  j< n; ++j) {
                        	int suma=0;
                            //if (k == 0)
                            //    c[(i + ib) * n + (j + jb)] = 0.0;

                            for (int k= K; k <K+BLOCK && k<n ; ++k) {
                                suma=suma+A[i][k]*B[k][j];
                            }
                            //cout<<"esto es el resultado"<<suma<<endl;	
                            C[i][j] = C[i][j] + suma;
                        }
                    }
                }
            }
        }
    }

void primera_pregunta(){
	
	
	///Esto es primera pregunta
	
	int fil, col;
	fil=1000;
	col=1000;
	unsigned t0,t1;
	srand(time(NULL));
	int **matriz_a=new int*[fil];
	for(int i=0;i<fil;i++){
		matriz_a[i]=new int [col];
	}

	matriz_randon(matriz_a,fil,col);
	mostrar_matris(matriz_a,fil,col);

	int x[fil];
	int y[col];
	int num;
	
	for(int j=0;j<col;j++){
		
		num=1+rand()%(101-1);
		x[j]=num;
	}
	
	for(int j=0;j<col;j++){
		num=1+rand()%(101-1);
		y[j]=num;
	}
	
	t0=clock();
	//mejor
	for(int i=0;i<fil;i++){
		for(int j=0;j<col;j++){
			y[i]+=matriz_a[i][j]*x[j];
		}
	}
	t1=clock();

	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Execution Time del primer for: " << time << endl;

	

	//esto es el peor caso por
	//cache de espacial y temporal
	t0=clock();
	for(int j=0;j<fil;j++){
		for(int i=0;i<col;i++){
			y[i]+=matriz_a[i][j]*x[j];
		}
	}
	t1=clock();

	time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Execution Time del segundo for : " << time << endl;
}

int main(){
	//primera_pregunta();
	//Esto es la segunda pregunta
	unsigned t0,t1;
	int fil, col;
	fil=1000;
	col=1000;
	

	int **matriz_a=new int*[fil];
	for(int i=0;i<fil;i++){
		matriz_a[i]=new int [col];
	}

	int **matriz_b=new int*[fil];
	for(int i=0;i<fil;i++){
		matriz_b[i]=new int [col];
	}


	int **resultado=new int*[fil];
	for(int i=0;i<fil;i++){
		resultado[i]=new int [col];
	}

	for(int i=0;i<fil;i++){
		for(int j=0;j<col;j++){
			resultado[i][j]=0;
		}
	}

	matriz_randon(matriz_a,fil,col);
	matriz_randon(matriz_b,fil,col);
	cout<<"Mostrando la matriz A"<<endl;
	mostrar_matris(matriz_a,fil,col);
	cout<<"Mostrando la matriz B"<<endl;
	mostrar_matris(matriz_b,fil,col);

	t0=clock();
	multiplicacionbloques(matriz_a,matriz_b,resultado,fil);
	t1=clock();
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Ejecucion mediante multiplicacion por bloques " << time << endl;

	//mostrar_matris(resultado,fil,col);
	for(int i=0;i<fil;i++){
		for(int j=0;j<col;j++){
			resultado[i][j]=0;
		}
	}
	//cout<<"Mostrando la resultado"<<endl;
	//mostrar_matris(resultado,fil,col);
	t0=clock();
	multiplicacion(resultado,matriz_a,matriz_b,fil,col);
	t1=clock();
	time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Ejecucion mediante multiplicacion tipica " << time << endl;

	//mostrar_matris(resultado,fil,col);
	
	//cout<<"resultado"<<endl;
	return 0;	
}
