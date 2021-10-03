// OpenMP header
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// int partition (int *arr, int low, int high, int C){
//     int i, j;
//     double pivot,swap;
    
//     // pivot (Element to be placed at right position)
//     pivot = arr[high*C];  
 
//     i = (low - 1);  // Index of smaller element

//     for (j = low; j <= high-1; j++)
//     {
//         // If current element is smaller than or
//         // equal to pivot
//         if (arr[j*C] <= pivot)
//         {
//             i++;    // increment index of smaller element
            
//             // swap arr[i] and arr[j]
//             swap = arr[i*C];
// 	    arr[i*C] = arr[j*C];
// 	    arr[j*C] = swap;
//         }
//     }
    
//     //swap arr[i + 1] and arr[high]
//     swap = arr[(i + 1)*C];
//     arr[(i + 1)*C] = arr[high*C];
//     arr[high*C] = swap;
    
//     return (i + 1);
  
// } // fim partition

// void quicksort(int *arr, int low, int high, int C){
//     int pi;
    
//     if (low < high)  {
//         /* pi is partitioning index, arr[pi] is now
//            at right place *//* */
//         pi = partition(arr, low, high, C);

//         quicksort(arr, low, pi - 1, C);  // Before pi
//         quicksort(arr, pi + 1, high, C); // After pi
//     }
    
// }



int main(int argc, char* argv[])
{
	FILE * file;
	int lin, col;
	file = fopen("matriz.txt", "r");


	fscanf(file, "%d %d", &lin, &col);


	int matriz[lin][col], transposta[col][lin];
	double soma, media_ar_vec [col], media_har_vec [col]; //vetores de métricas
	int num_threads, freqs[99];
	
	// Ler matriz
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(file, "%i ", &matriz[i][j]);
		}
	}

	// Transpor matriz
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < lin; j++) {
			transposta[i][j] = matriz[j][i];
		}	
	}


	#pragma omp parallel num_threads(8) firstprivate(transposta)
	{
	
		#pragma omp single 
		{
			// Calcular média aritmética
			#pragma omp task
			{
				for (int i = 0; i < col; i++) {
					soma = 0;
					for (int j = 0; j < lin; j++) {
							soma += transposta[i][j];
					}
					media_ar_vec[i] = soma / lin;
				}
			}
			
			// Calcular média harmônica
			#pragma omp task 
			{	
				for (int i = 0; i < col; i++) {
					soma = 0;
					for (int j = 0; j < lin; j++) {
							soma += 1.0/(transposta[i][j]);
					}
					media_har_vec[i] = lin / soma;
				}
			}

			// Calcular a mediana
			#pragma omp task 
			{
				for (int i = 0;  i < col; i++) {
					// quicksort(transposta[i], 0, lin-1, col);
				}	
			}

			// Calcular a moda
			#pragma omp task 
			{
				for (int i = 0; i < col; i++) {
					for (int j = 0; j < lin; j++) {
						freqs[transposta[i][j]]++;
					}
				}
			}

			// Calcular a variância (depende do resultado do desvio padrão)

			// Calcular o desvio padrão

			// Calcular o coeficiente de variação


			#pragma omp taskwait
			{
				printf("Média: ");
				for (int i = 0; i < col; i++) {
					 printf("%.1f ", media_ar_vec[i]);	 
				}

				printf("\n");

				printf("Média Harmônica: ");	
				for (int i = 0; i < col; i++) {
					 printf("%.1f ", media_har_vec[i]);
				}

				printf("\n");

				printf("Moda: ");
				for (int i = 0; i < 99; i++) {
					 printf("%i ", freqs[i]);
				}

				printf("\n");
			}

		}
	} // Fim da região paralela

	fclose(file);


	// // gcc -o hello -fopenmp hello.c

	return 0;
}
