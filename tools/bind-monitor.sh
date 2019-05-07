#!/bin/bash

echo "#!/bin/bash" > $2/monitor-run
echo "$1/tools/monitor.sh \"$2/run --run-with-camera\"" >> $2/monitor-run
chmod +x $2/monitor-run
