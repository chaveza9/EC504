n=100                      #number of intervals
max=n*(n-1)/2.             #max value
min=0.                     #min value
width=(max-min)/n          #interval width
                           #function used to map a value to the intervals
hist(x,width)=width*floor(x/width)+width/2.0
set boxwidth width*0.9
set style fill solid 0.5   # fill style
#count and plot
plot "printPerm.txt" u (hist($2,width)):(1.0) smooth freq w boxes lc rgb"blue" notitle
set term postscript color
set output "SwapHist.PNG"
replot
set term x11
