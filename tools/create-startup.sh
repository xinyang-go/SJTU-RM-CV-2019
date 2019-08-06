#!/bin/bash

echo "#!/bin/bash" > $2/startup-run
echo "echo sjturm | sudo -S cpufreq-set -g performance" >> $2/startup-run
echo "mkdir $1/Mark" >> $2/startup-run
echo "mkdir $1/gimbal_video" >> $2/startup-run
echo "mkdir $1/armor_box_photo" >> $2/startup-run
echo "gnome-terminal -- bash -c \"echo sjturm | sudo -S $1/tools/monitor.sh \\\"$2/run --run-with-camera --save-video --wait-uart --save-labelled-boxes --show-armor-box\\\"\"" >> $2/startup-run
chmod +x $2/startup-run
