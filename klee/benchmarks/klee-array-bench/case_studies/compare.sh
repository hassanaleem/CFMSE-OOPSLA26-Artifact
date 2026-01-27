echo "----------------------------------$3----------------------------------------"

gzip -lv $1/instructions.txt.gz | tail -n1 | cut -d ' ' -f2
gzip -lv $2/instructions.txt.gz | tail -n1 | cut -d ' ' -f2

echo "--------------------------------------------------------------------------"

tail -n1 $1/run.stats | cut -d ',' -f11
tail -n1 $2/run.stats | cut -d ',' -f11

echo "--------------------------------------------------------------------------"

tail -n10 $1/info | head -n1
tail -n10 $2/info | head -n1

tail -n9 $1/info | head -n1
tail -n9 $2/info | head -n1

tail -n8 $1/info | head -n1
tail -n8 $2/info | head -n1

tail -n7 $1/info | head -n1
tail -n7 $2/info | head -n1

tail -n6 $1/info | head -n1
tail -n6 $2/info | head -n1

tail -n5 $1/info | head -n1
tail -n5 $2/info | head -n1

tail -n3 $1/info | head -n1
tail -n3 $2/info | head -n1

tail -n2 $1/info | head -n1
tail -n2 $2/info | head -n1

tail -n1 $1/info
tail -n1 $2/info
