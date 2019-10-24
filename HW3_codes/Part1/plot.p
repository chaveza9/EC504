# Set linestyle 1 to blue (#0060ad)
set term png
set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.5

plot 'nodeHeight.dat' with linespoints linestyle 1
# set term postscript color
set output "treeheight.png"
replot
set term x11
