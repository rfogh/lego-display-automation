echo "Initial setup of scripts on a prepared Raspberry Pi"

DIR=$(dirname "$(readlink -f "$0")")

sudo ln -sf ${DIR}/facedetection/facedetection.service /lib/systemd/system
sudo chmod 644 /lib/systemd/system/facedetection.service
chmod +x ${DIR}/facedetection/mqtt_face_detection.py
sudo systemctl daemon-reload
sudo systemctl enable facedetection.service
sudo systemctl start facedetection.service

sudo ln -sf ${DIR}/processmanager/processmanager.service /lib/systemd/system
sudo chmod 644 /lib/systemd/system/processmanager.service
chmod +x ${DIR}/processmanager/processmanager.py 
sudo systemctl daemon-reload
sudo systemctl enable processmanager.service
sudo systemctl start processmanager.service

echo "You must restart for all changes to take effect"
