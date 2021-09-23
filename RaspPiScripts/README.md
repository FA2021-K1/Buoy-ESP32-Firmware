# README

Put all the files in this Directory in /buoy/scripts

## Set file permission

sudo chmod 744 /code/scripts/myapp.sh
sudo chmod 664 /etc/systemd/system/esp_com.service

## Enable Service

sudo systemctl daemon-reload
sudo systemctl enable esp_com.service

## Test Service

sudo systemctl start esp_com.service

## Check Status

sudo systemctl status esp_com.service


## Stop Service

sudo systemctl stop esp_com.service

## Restart server to test if the service started on reboot

sudo reboot
