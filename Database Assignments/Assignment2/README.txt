
There were some issues getting the files to run on vagrant so I used:
**************************************************************************************************
scp -P 2222 pvalovcscript4.txt vagrant@127.0.0.1:/home/vagrant
scp -P 2222 vagrant@127.0.0.1:/home/vagrant/pvalovcoutputscript1.txt ./
**************************************************************************************************
to transfer files between my local and virtual machine.


This means in script2 when I am loading an infile, it is referencing where I copied my files to:
**************************************************************************************************
load data infile '/home/vagrant/fall2015data.txt' into table Movie fields terminated by ',';
**************************************************************************************************
which means you may need to modify the infile loading argument.