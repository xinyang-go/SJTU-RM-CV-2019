#!/bin/bash

echo "#!/bin/bash" > $2/startup-run
echo "$1/tools/auto-pull.sh" >> $2/startup-run
echo "gnome-terminal -- bash -c \"echo sjturm | sudo -S $1/tools/monitor.sh \\\"$2/run --run-with-camera --save-video --wait-uart\\\"\"" >> $2/startup-run
chmod +x $2/startup-run
