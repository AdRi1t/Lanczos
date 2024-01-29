from matplotlib import pyplot
from matplotlib.ticker import FormatStrFormatter
from matplotlib.ticker import AutoMinorLocator
import sys
import numpy

def main():
  if(len(sys.argv) < 2):
    sys.stderr.write("Miss file to plot \n")
    return 0
  sys.stdout.write("Graphs of time per process and gflops \n")
  
  fig1, ax1 = pyplot.subplots()
  fig2, ax2 = pyplot.subplots()
    
  for arg in sys.argv:
    if(arg == sys.argv[0]):
      continue 
    file_name = arg
    data_file = open(file_name, "rt")
    
    file_name = file_name.split(sep="_")
    dimension_n = int(file_name[1].split(sep=".")[0])
    dimension_m=[]
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
      dimension_m.append(int(line[0]))
      time.append(float(line[1]))
      gflops.append(float(line[2]))
      k += 1
    data_file.close()
    
    ax1.plot(dimension_m,time, marker="s", label=f"n = {dimension_n} ")#\n m = {dimension_m}")
    ax2.plot(dimension_m,gflops, marker="s", label=f"n = {dimension_n} ")#\n m = {dimension_m}")
    
  ax1.legend(loc='upper right')
  ax2.legend(loc='upper left')
  
  ax1.set_yscale("log")
  ax1.tick_params(axis='y', which='both', bottom=True)
  #ax1.yaxis.set_minor_formatter(FormatStrFormatter("%g"))
    
  ax1.grid(True, axis="y", which="both")
  ax2.grid(axis='y')
    
  ax1.set_title("Temps")
  ax2.set_title("Gflops")
    
  ax1.set_xlabel("Dimension m")
  ax2.set_xlabel("Dimension m")
    
  ax1.set_ylabel("Temps (secondes)")
  ax2.set_ylabel("Gflops")
  
  fig1.tight_layout()
  fig2.tight_layout()
  
  fig1.savefig("m_Time",dpi=250)
  fig2.savefig("m_Gflops",dpi=250)
  
  return 0


if __name__ == "__main__":
  main()
  
  
