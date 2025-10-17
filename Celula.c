#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <omp.h> 

#define STRING_LEN 256

struct stLattice{
    unsigned char *buff0;
    unsigned char *buff1;
    int width;
    int height;
    int steps;
};
typedef struct stLattice tpLattice;

/**
 * \brief 
 **/
void help(){
    fprintf(stdout, "\nGOL algorithm (Parallels)\n");
    fprintf(stdout, "Usage: ./gol.exec [OPTIONS]\n");
    fprintf(stdout, "**Parameter options:**\n");
    fprintf(stdout, "\t'-h', '--help': Show this help message\n");
    fprintf(stdout, "\t'-v', '--verbose': Explain what is being done\n");
    fprintf(stdout, "\t'-a', '--answer': Binary file which contain the last state of GOL, answer problem.\n");
    fprintf(stdout, "\t'-p', '--probability': Probability of a cell is not live.\n");
    fprintf(stdout, "\t'-x', '--width': Lattice width.\n");
    fprintf(stdout, "\t'-y', '--height': Lattice height.\n");
    fprintf(stdout, "\t'-s', '--steps': time steps of simulation.\n");
    fprintf(stdout, "\t'-t', '--threads': Number of OpenMP threads to use (1 for serial).\n"); 

    exit(EXIT_FAILURE);
}

void InitRandness(tpLattice *mLattice, float p);
void GameOfLife(tpLattice *mLattice);
void print2File(char *filename, tpLattice *mLattice);

int main(int ac, char**av)
{
    tpLattice mLattice;
    int flagSave = 0;
    float prob   = 0.25f;
    char file_name_template[STRING_LEN] ;
    int verbose_flag = 0;
    int option_index = 0;
    int input_opt = 0;
    int num_threads = 1;
    double t_start, t_end; 
    file_name_template[0] = 0;

    mLattice.width  = 1024;
    mLattice.height = 1024;
    mLattice.steps  = 1000;
    
    if (ac == 1)
      help();
      
    struct option long_options[] =
    {
        {"verbose", no_argument,     0, 'v'},
        {"help",    no_argument,     0, 'h'},
        {"answer",        required_argument, 0, 'a'},
        {"probability", required_argument, 0, 'p'},
        {"width",         required_argument, 0, 'x'},
        {"height",      required_argument, 0, 'y'},
        {"steps",         required_argument, 0, 's'},
        {"threads",       required_argument, 0, 't'}, // Adicionado threads
        {0, 0, 0, 0}
    };
    
    while ((input_opt = getopt_long (ac, av, "hva:p:x:y:s:t:", long_options, &option_index)) != EOF){
        switch (input_opt)
        {
            case 'h': help(); break;
            case 'v': verbose_flag = 1; break;
            case 'a': strcpy(file_name_template, optarg); break;
            case 'p': prob = atof(optarg); break;
            case 'x': mLattice.width = atoi(optarg); break;
            case 'y': mLattice.height = atoi(optarg); break;
            case 's': mLattice.steps = atoi(optarg); break;
            case 't': num_threads = atoi(optarg); break; // Captura o número de threads
            default: help(); break;
        }
    };

    if (num_threads > 0) {
        omp_set_num_threads(num_threads);
    }
    
    if (verbose_flag){
      fprintf(stdout, "\nGame of life");
      fprintf(stdout, " - Dominio(%d, %d, %d)\n", mLattice.width, mLattice.height, mLattice.steps);
      fprintf(stdout, " - Probabilidade de estar viva = %5.3f\n", prob);
      fprintf(stdout, " - Arquivo resposta [%s]\n", file_name_template);
      fprintf(stdout, " - Numero de Threads = %d\n", num_threads);
      fflush(stdout);
    }
    
    mLattice.buff0 = (unsigned char*) malloc (mLattice.width * mLattice.height * sizeof(unsigned char));
    mLattice.buff1 = (unsigned char*) malloc (mLattice.width * mLattice.height * sizeof(unsigned char));
    

    assert(mLattice.buff0 != NULL && mLattice.buff1 != NULL);
    
    InitRandness(&mLattice, prob);

    t_start = omp_get_wtime();

    for (int t = 0; t < mLattice.steps; t++)
    {
      GameOfLife(&mLattice);
      unsigned char *swap = mLattice.buff0;
      mLattice.buff0 = mLattice.buff1;
      mLattice.buff1 = swap;
    }

    t_end = omp_get_wtime();
    double T_execucao = t_end - t_start;

    if (verbose_flag){
        fprintf(stdout, "\n------------------------------------------------------\n");
        fprintf(stdout, "Tempo de execucao total (Steps: %d): %f segundos\n", mLattice.steps, T_execucao);
        fprintf(stdout, "------------------------------------------------------\n");
    }

    if (strlen(file_name_template) > 0){
      if (verbose_flag) fprintf(stdout, " - Salvando o arquivo: [%s]", file_name_template);
      print2File(file_name_template, &mLattice);
      if (verbose_flag) fprintf(stdout, " [OK]\n");
    }
      
    free(mLattice.buff0);
    free(mLattice.buff1);
    
    return EXIT_SUCCESS;
}

/*
 * Função utilizada para iniciar a matriz. Não mudar o valor constante do seed do rand
 */
void InitRandness(tpLattice *mLattice, float p){
  memset(mLattice->buff0, 0x00,  mLattice->width * mLattice->height * sizeof(unsigned char));
  memset(mLattice->buff1, 0x00,  mLattice->width * mLattice->height * sizeof(unsigned char));
  srand (42);
  
  for (int j = 1; j < mLattice->height - 1; j++){
      for (int i = 1; i < mLattice->width - 1; i++){
          int k = j * mLattice->width  +  i;
          float r = (rand() / (float)RAND_MAX);
          if (r <= p)
            mLattice->buff0[k] = 1;
      }
  }
}

/*
 * Função que resolve o GOL. Paralelizada com OpenMP.
 * buff0 (leitura - estado atual) -> buff1 (escrita - próximo estado)
 */
void GameOfLife(tpLattice *mLattice){
    int nw = -1, n = -1, ne = -1, w = -1, e = -1, sw = -1, s = -1, se = -1, c = -1, sum;
    int i, j; 

    #pragma omp parallel for private(i, j, nw, n, ne, w, e, sw, s, se, c, sum)
    for (j = 1; j < mLattice->height - 1; j++){
        for (i = 1; i < mLattice->width - 1; i++){

            nw = mLattice->buff0[(j - 1) * mLattice->width  +  (i - 1)];
            n  = mLattice->buff0[(j - 1) * mLattice->width  +  i];
            ne = mLattice->buff0[(j - 1) * mLattice->width  +  (i + 1)];
            w  = mLattice->buff0[j * mLattice->width  +  (i - 1)];
            c  = mLattice->buff0[j * mLattice->width  +  i];
            e  = mLattice->buff0[j * mLattice->width  +  (i + 1)];
            sw = mLattice->buff0[(j + 1) * mLattice->width  +  (i - 1)];
            s  = mLattice->buff0[(j + 1) * mLattice->width  +  i];
            se = mLattice->buff0[(j + 1) * mLattice->width  +  i+1];

            sum = nw + n + ne + w + e + sw + s + se;

            if ((sum == 3) && (c == 0))
                mLattice->buff1[j  * mLattice->width  +  i] = 1;
            else if ((sum >= 2) && (sum <= 3) && (c == 1))
                mLattice->buff1[j  * mLattice->width  +  i] = 1;
            else
                mLattice->buff1[j  * mLattice->width  +  i] = 0;
        }
    }
}

/*
 * Função para imprimir para arquivo. Formato do arquivo .txt
 */
void print2File(char *filename, tpLattice *mLattice)
{
  
  FILE *ptr = fopen(filename, "w+");
  assert(ptr  != NULL);

  for (int j = 1; j < mLattice->height - 1; j++){
      for (int i = 1; i < mLattice->width - 1; i++){
          int k = j * mLattice->width  +  i;
          if (mLattice->buff0[k] == 1)
            fputc('#', ptr);
          else
            fputc(' ', ptr);
      }
      fputc('\n', ptr);
  }

  fclose(ptr);
    
}