#!/bin/bash
if [ -z "$1" ]; then
	echo 'Please specify group name.'
	exit 1
fi
if ! grep -q "^$1:" /etc/group; then
	echo "Invalid group: $1"
	exit 2
fi

outfile=/var/run/qstat.$1

qstat=/usr/local/bin/qstat
mktemp="mktemp qbg.XXX"

qfile=$($mktemp)
mfile=$($mktemp)
rnfile=$($mktemp)
sfile=$($mktemp)

# Get list of group members
members=$(grep "^$1:" /etc/group | cut -d: -f4 | tr "," " ")
# Get list of all running jobs and jobs from qstat -rn output
$qstat | grep -F " R " > $qfile
$qstat -rn > $rnfile
# Get running jobs from members concerned
for uid in $members; do
	grep $uid $qfile >> $mfile
done
rm $qfile
# Get job entries of members from qstat -rn output
cat $mfile | cut -d. -f1 | xargs -I %jid grep -P0 -A1 %jid $rnfile | sed '$!N;s/\n/ /' >> $sfile
rm $mfile
rm $rnfile
# Output
echo "                                                                                  Req'd    Re'd       Elap" > $outfile
echo 'Job ID                  Username    Queue    Jobname          SessID  NDS   TSK   Memory   Time    S   Time' >> $outfile
echo '----------------------- ----------- -------- ---------------- ------ ----- ------ ------ --------- - ---------' >> $outfile
sort $sfile >> $outfile
rm $sfile
chmod 640 $outfile
chown root:$1 $outfile
