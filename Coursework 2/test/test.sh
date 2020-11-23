for i in {1..1000}
do
    echo "$i";
    ../dependencyDiscoverer *.y *.l *.c | diff - output;
done