sudo fallocate -l 50M lofs.img
ULOOP=$(sudo losetup -f)
sudo losetup ${ULOOP} lofs.img
mkdir lofsdisk
sudo mkfs.ext4 ${ULOOP}
sudo mount ${ULOOP} lofsdisk/

# File system created and mounted