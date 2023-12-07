from matplotlib import pyplot
from matplotlib.ticker import FormatStrFormatter
from matplotlib.ticker import AutoMinorLocator
import sys
import numpy

def main():
  if(len(sys.argv) < 2):
    sys.stderr.write("Miss file to plot \n")
    return 0
  sys.stdout.write("Graphs of speed up, time per process, gflops, and efficiency \n")
  
  fig1, ax1 = pyplot.subplots()
  fig2, ax2 = pyplot.subplots()
  fig3, ax3 = pyplot.subplots()
  fig4, ax4 = pyplot.subplots()
    
  for arg in sys.argv:
    if(arg == sys.argv[0]):
      continue 
    file_name = arg
    data_file = open(file_name, "rt")
    
    file_name = file_name.split(sep="_")
    dimension_n = int(file_name[1])
    dimension_m = int(file_name[2].split(sep=".")[0])
    nb_proc=[]
    time=[]
    gflops=[]
    k = 0
    line = data_file.readline()
    while True:
      line = data_file.readline()
      if not line:
        break
      line = line.strip()
      line = line.replace('\n', '')
      line = line.split(sep=" ")
      line = list(filter(None, line))
      nb_proc.append(int(line[0]))
      time.append(float(line[1]))
      gflops.append(float(line[2]))
      k += 1
    data_file.close()
    
    speedUp=[]
    efficiency=[]
    for t in time:
      speedUp.append(time[0]/t)
    for acc,p in zip(speedUp,nb_proc):
      efficiency.append(acc/p)
    
    
    ax1.plot(nb_proc,time, marker="s", label=f"n = {dimension_n} ")#\n m = {dimension_m}")
    ax2.plot(nb_proc,speedUp, marker="s", label=f"n = {dimension_n} ")#\n m = {dimension_m}")
    ax3.plot(nb_proc,efficiency, marker="s", label=f"n = {dimension_n} ")#\n m = {dimension_m}")
    ax4.plot(nb_proc,gflops, marker="s", label=f"n = {dimension_n} ")#\n m = {dimension_m}")
    
  ax1.legend(loc='upper right')
  ax2.legend(loc='upper left')
  ax3.legend(loc='upper right')
  ax4.legend(loc='upper left')
      
  ax3.set_yticks(numpy.arange(0,1.1,0.1))
  ax1.set_yscale("log")
  ax1.tick_params(axis='y', which='both', bottom=True)
  #ax1.yaxis.set_minor_formatter(FormatStrFormatter("%g"))
    
  ax1.grid(True, axis="y", which="both")
  ax2.grid(axis='y')
  ax3.grid(axis='y')
  ax4.grid(axis='y')
    
  ax1.set_title("Temps")
  ax2.set_title("Accélération")
  ax3.set_title("Efficacité")
  ax4.set_title("Gflops")
    
  ax1.set_xlabel("Nombre de threads")
  ax2.set_xlabel("Nombre de threads")
  ax3.set_xlabel("Nombre de threads")
  ax4.set_xlabel("Nombre de threads")
    
  ax1.set_ylabel("Temps (secondes)")
  ax2.set_ylabel("Accélération")
  ax3.set_ylabel("Efficacité")
  ax4.set_ylabel("Gflops")
  
  fig1.tight_layout()
  fig2.tight_layout()
  fig3.tight_layout()
  fig4.tight_layout()
  
  fig1.savefig("Time",dpi=250)
  fig2.savefig("SpeedUp",dpi=250)
  fig3.savefig("Efficiency",dpi=250)
  fig4.savefig("Gflops",dpi=250)
  
  return 0


if __name__ == "__main__":
  main()
  
  
