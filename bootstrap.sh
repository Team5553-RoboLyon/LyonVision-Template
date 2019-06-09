#!/bin/sh

# Enable password-less sudo for everyone
echo "%sudo ALL=(ALL) NOPASSWD:ALL" | sudo tee -a /etc/sudoers

# Install required packages
sudo apt-get update
sudo apt-get install -y avahi-daemon libnss-mdns v4l-utils imagemagick

# Add vision user and password (5553)
sudo adduser vision --disabled-password --gecos ""
sudo adduser vision sudo
echo "vision:5553" | sudo chpasswd

# Set hostname, user and password
echo pi5553 | sudo tee /etc/hostname

# Reboot to commit changes
sudo reboot