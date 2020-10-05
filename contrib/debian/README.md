
Debian
====================
This directory contains files used to package kuberbitcoind/kuberbitcoin-qt
for Debian-based Linux systems. If you compile kuberbitcoind/kuberbitcoin-qt yourself, there are some useful files here.

## kuberbitcoin: URI support ##


kuberbitcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install kuberbitcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your kuberbitcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/kuberbitcoin128.png` to `/usr/share/pixmaps`

kuberbitcoin-qt.protocol (KDE)

