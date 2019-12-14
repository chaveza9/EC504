# png
set terminal pngcairo size 350,262 enhanced font 'Verdana,10'
set output 'plot.png'
# Set linestyle 1 to blue (#0060ad)

unset key
set xlabel 'Time'
set ylabel 'Max Value'
set tics scale 0.75

set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.5

plot 'out.dat' with linespoints linestyle 1