#!/bin/sh
# Este script roda um unico job em SGE
# Ele pode ser executado pelo comando SGE abaixo:
# qsub um_job.sh

# A linha abaixo nao e' um comentario. Ela especifica que o que vem
# apos ela sera invocado com o /bin/sh shell
#$ -S /bin/sh

# Coloca os arquivos de saida e de erro do seu job no diretorio .
#$ -cwd
#--------------------------------
# exemplo: (altere a partir daqui)

time ./pi

# Fim do script
