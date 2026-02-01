#!/bin/bash

rm -rf *.csv 


libosip="./../fig7-coverage/chopper-experiments/libosip"
libtasn="./../fig7-coverage/chopper-experiments/libtasn"
coreutils="./../fig7-coverage/coreutils-6.11"
json="./../fig7-coverage/json"
protobuf="./../fig7-coverage/protobuf-c"
utf8="./../fig7-coverage/utf8.h"
regex="./../fig10-11-bug-detection-and-killed-states/regex"
libyaml="./../fig10-11-bug-detection-and-killed-states/libyaml"


for lib in libosip libtasn json protobuf utf8; do
  cp ${!lib}/cfm_driver_output/*/*.txt .
  python3 extract_data.py *.txt
  mv *.txt.csv "$lib.csv"
  rm -f *.txt
done

for prog in chcon mkdir chown mkfifo; do
  cp $coreutils/cfm_driver_output/$prog/*.txt .
  python3 extract_data.py *.txt
  mv *.txt.csv "$prog.csv"
  rm -f *.txt
done

# regex special case
cp $regex/logs/logs_1/log_9.txt regex.txt
python3 extract_data.py regex.txt
mv regex.txt.csv regex.csv
rm -f regex.txt

# libyaml special case
cp $libyaml/logs/logs_1/log_7.txt libyaml.txt
python3 extract_data.py libyaml.txt
mv libyaml.txt.csv libyaml.csv
rm -f libyaml.txt

# Now we combine all these csv files into one final csv file
python3 combine_table.py
find . -maxdepth 1 -name "*.csv" ! -name "overhead.csv" -delete


