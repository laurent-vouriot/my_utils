set style data histograms
set datafile separator ','
set style fill solid
set xlabel 'functions'
set ylabel 'time in s'
set xtic rotate
set yrange[0: 8]
set terminal png size 400, 400
set output 'demo_session.png'
plot 'profile.data' using 2:xtic(1) title 'demo_session'
