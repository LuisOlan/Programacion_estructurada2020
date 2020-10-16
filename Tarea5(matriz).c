#include <stdio.h>
#include <stdlib.h>

int main()
{ int dimension = 5;
  int m_uno [dimension][dimension], m_dos [dimension][dimension];
  int m_res [dimension][dimension];
  int i,j;

  for (j=0;j<dimension;j++)
     {
       for(i=0;i<dimension;i++)
          {
            m_uno[j][i]=i+j;
            m_dos [j][i]=i+j+100;
            m_res[j][i]=
            m_uno[j][i]+m_dos[j][i];
          }
     }
  printf("La primera matriz es: \n" );
  for(j=0;j<dimension;j++)
     {
       for (i=0;i<dimension;i++)
          {
            printf("%d, ", m_uno[j][i]);
          }
       printf("\n");
     }
     printf("La segunda matriz es: \n" );
     for (j=0;j<dimension;j++)
        {
          for(i=0;i<dimension;i++)
             {
               printf("%d,",m_dos[j][i]);
             }
          printf("\n");
        }
        printf("La matriz resultante es: \n" );
        for(j=0;j<dimension;j++)
           {
             for (i=0;i<dimension;i++)
                {
                  printf("%d, ",m_res[j][i]);
                }
             printf("\n");
           }
           return 0;                
}
