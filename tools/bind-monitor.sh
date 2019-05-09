#!/bin/bash

echo "#!/bin/bash" > $2/monitor-run
echo "echo \"sjturm\" | sudo -S $1/tools/monitor.sh \"$2/run --run-with-camera --show-armor-box --wait-uart\"" >> $2/monitor-run
chmod +x $2/monitor-run
