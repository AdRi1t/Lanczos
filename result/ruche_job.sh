#!/bin/bash
#SBATCH --job-name=lanzcos
#SBATCH --output=%x.o%j
#SBATCH --error=errorJob.txt
#SBATCH --time=00:30:00
#SBATCH --nodes=4
#SBATCH --cpus-per-task=160
#SBATCH --mem=25G
#SBATCH --partition=cpu_short       # (see available partitions)

# echo of commands
set -x

# To compute in the submission directory
cd ${SLURM_SUBMIT_DIR}

# number of OpenMP threads
export OMP_NUM_THREADS=${SLURM_CPUS_PER_TASK} 

# Binding OpenMP threads on core
export OMP_PLACES=cores

# execution with 'OMP_NUM_THREADS' OpenMP threads
.././lanczos -n 30000 -m 30 -b 2.5

