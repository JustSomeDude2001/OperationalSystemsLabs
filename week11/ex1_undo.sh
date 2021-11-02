ULOOP=$(sudo losetup | grep lofs.img | head -c 11)
sudo umount -A ${ULOOP}
sudo losetup -d ${ULOOP}

sudo rm lofs.img
sudo rm -rf lofsdisk

# filesystem 'safely' removed