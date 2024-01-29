#!/bin/bash
#SBATCH --job-name=lanczos
#SBATCH --output=%x.o%j
#SBATCH --error=errorJob.txt
#SBATCH --time=00:50:00
#SBATCH --cpus-per-task=1
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
.././lanczos -n 1000 -b 2.5 -B 2

