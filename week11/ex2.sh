sudo fallocate -l 128M lofs.img
ULOOP=$(sudo losetup -f)
sudo losetup ${ULOOP} lofs.img
mkdir lofsdisk
sudo mkfs.ext4 ${ULOOP}
sudo mount ${ULOOP} lofsdisk/

sudo chmod 777 lofsdisk

sudo cp -ar /lib/x86_64-linux-gnu lofsdisk/lib
sudo cp -ar /lib64 lofsdisk
sudo cp -ar /bin/bash lofsdisk/bin
sudo cp ex2 lofsdisk
sudo chroot lofsdisk
ex2 > ex2.txt