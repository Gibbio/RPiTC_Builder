#include "rpitc.h"
#include "ui_rpitc.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QProcess>

QString ica_pkgs = "not_present";
QString vmware_pkgs = "not_present";
QString nxc_pkgs = "not_present";
QString thinlinc_pkgs = "not_present";
QString twox_pkgs = "not_present";
QString browser_pkgs = "not_present";

QString x2go_pkgs = "not_present";
QString spice_pkgs = "not_present";
QString tn5250_pkgs = "not_present";
QString x3270_pkgs = "not_present";
QString xephyr_pkgs = "not_present";

QString rdesktop_pkgs = "not_present";
QString xfreerdp_pkgs = "not_present";
QString xfreerdpgit_pkgs = "not_present";
QString dfreerdp_pkgs = "not_present";

QString cups_pkgs = "not_present";
QString x11vnc_pkgs = "not_present";
QString ssh_pkgs = "not_present";
QString docky_pkgs = "not_present";
QString conky_pkgs = "not_present";
QString virtualhere_pkgs = "not_present";
QString openconnect_pkgs = "not_present";
QString openvpn_pkgs = "not_present";
QString vpnc_pkgs = "not_present";

QString overclock_pkgs = "not_present";
QString custom1_pkgs = "not_present";

RPiTC::RPiTC(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RPiTC)
{
    ui->setupUi(this);
    RPiTC::on_rescan_pushButton_clicked();
}

RPiTC::~RPiTC()
{
    delete ui;
}

void RPiTC::on_pushButton_clicked()
{
    QString bash_me = "#!/bin/bash\n####### RPi-TC Builder #######\n\n";
    if (ui->aptcache_checkBox->isChecked()) {
        bash_me = bash_me + "####### Update apt cache:\n"
                            "apt-get update\n";
    }
    QString bash_me_filename = "/opt/bashme.sh";

    //######################START MAIN CLIENTS INSTALL/REMOVE ROUTINES######################ßß
    if (true) {
        // CITRIX RECEIVER:
        if (ui->ica_checkBox->isChecked() && ica_pkgs == "not_present") { qDebug() << "I have to install Citrix Receiver!";
        bash_me = bash_me + "\n####### CITRIX RECEIVER Install cmds:\n"
                            "apt-get install -y icaclient ctxusb libcurl4-gnutls-dev\nsystemctl enable ctxusbd\n"
                            "ln -s /usr/share/ca-certificates/mozilla/* /opt/Citrix/ICAClient/keystore/cacerts/\n"
                            "c_rehash /opt/Citrix/ICAClient/keystore/cacerts/\n"
                            "# Add ICA icon to docky menu:\n/opt/scripts/dockyadd.sh selfservice.desktop\n";
        }
        if (!ui->ica_checkBox->isChecked() && ica_pkgs == "installed") { qDebug() << "I have to remove Citrix Receiver!";
        bash_me = bash_me + "\n####### CITRIX RECEIVER Remove cmds:\n"
                            "apt-get remove --purge -y icaclient ctxusb\napt-get autoremove --purge -y\nsystemctl disable ctxusbd\n"
                            "# Remove ICA icon from docky menu:\n/opt/scripts/dockyrm.sh selfservice.desktop\n";
        }
        // PARALLELS 2X:
        if (ui->twox_checkBox->isChecked() && twox_pkgs == "not_present") { qDebug() << "I have to install Parallel 2X!";
        bash_me = bash_me + "\n####### PARALLELS 2X Install cmds:\n"
                            "apt-get install -y 2xclient libqtdbus4 libqt4-network\n"
                            "# Add 2X icon to docky menu:\n/opt/scripts/dockyadd.sh 2xclient.desktop\n";
        }
        if (!ui->twox_checkBox->isChecked() && twox_pkgs == "installed") { qDebug() << "I have to remove Parallel 2X!";
        bash_me = bash_me + "\n####### PARALLELS 2X Remove cmds:\n"
                            "apt-get remove --purge -y 2xclient\n"
                            "# Remove 2X icon from docky menu:\n/opt/scripts/dockyrm.sh 2xclient.desktop\n";
        }
        // NOMACHINE NX
        if (ui->nomachine_checkBox->isChecked() && nxc_pkgs == "not_present") { qDebug() << "I have to install NoMachine!";
        bash_me = bash_me + "\n####### NOMACHINE NX Install cmds:\n"
                            "apt-get install -y xdg-user-dirs\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/nxplayer.tar.gz -O /tmp/nxplayer.tar.gz\ntar xf /tmp/nxplayer.tar.gz -C /usr/\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/nxclient.tar.gz -O /tmp/nxclient.tar.gz\ntar xf /tmp/nxclient.tar.gz -C /usr/\n"
                            "ln -s /usr/NX/share/applnk/client/network/nxplayer.desktop /usr/share/applications/nxplayer.desktop\n"
                            "# Add NX icon to docky menu:\n/opt/scripts/dockyadd.sh nxplayer.desktop\n";
        }
        if (!ui->nomachine_checkBox->isChecked() && nxc_pkgs == "installed") { qDebug() << "I have to remove NoMachine!";
        bash_me = bash_me + "\n####### NOMACHINE NX Remove cmds:\n"
                            "apt-get remove --purge -y xdg-user-dirs\n"
                            "rm -fr /usr/NX/ /usr/share/applications/nxplayer.desktop\n"
                            "# Remove NX icon from docky menu:\n/opt/scripts/dockyrm.sh nxplayer.desktop\n";
        }
        // VMWARE HORIZON
        if (ui->vmware_checkBox->isChecked() && vmware_pkgs == "not_present") { qDebug() << "I have to install VMWare Horizon!";
        bash_me = bash_me + "\n####### VMWARE HORIZON Install cmds:\n"
                            "apt-get install libudev1\n"
                            "ln -s /lib/arm-linux-gnueabihf/libudev.so.1 /lib/arm-linux-gnueabihf/libudev.so.0\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/vmwh350.tar.gz -O /tmp/vmwh350.tar.gz\ntar xf /tmp/vmwh350.tar.gz -C /\n"
                            "systemctl enable vmwareusbd\nsystemctl start vmwareusbd\n"
                            "# Add Horizon icon to docky menu:\n/opt/scripts/dockyadd.sh vmware-horizon.desktop\n";
        }
        if (!ui->vmware_checkBox->isChecked() && vmware_pkgs == "installed") { qDebug() << "I have to remove VMWare Horizon!";
        bash_me = bash_me + "\n####### VMWARE HORIZON Remove cmds:\n"
                            "rm -rf /lib/arm-linux-gnueabihf/libudev.so.0\n"
                            "systemctl disable vmwareusbd\n"
                            "find /etc/|grep -i vmware |xargs rm -fr;find /lib/|grep -i vmware |xargs rm -fr;find /usr/|grep -i vmware |xargs rm -fr;find /|grep -i pcoip |xargs rm -fr\n"
                            "# Remove Horizon icon from docky menu:\n/opt/scripts/dockyrm.sh vmware-horizon.desktop\n";
        }
        // THINLINC
        if (ui->thinlinc_checkBox->isChecked() && thinlinc_pkgs == "not_present") { qDebug() << "I have to install ThinLinc!";
        bash_me = bash_me + "\n####### THINLINC Install cmds:\n"
                            "apt-get install -y thinlinc-client\n"
                            "# Add Thinlinc icon to docky menu:\n/opt/scripts/dockyadd.sh thinlinc-client.desktop\n";
        }
        if (!ui->thinlinc_checkBox->isChecked() && thinlinc_pkgs == "installed") { qDebug() << "I have to remove ThinLinc!";
        bash_me = bash_me + "\n####### THINLINC Remove cmds:\n"
                            "apt-get remove --purge -y thinlinc-client\n"
                            "# Remove Thinlinc icon from docky menu:\n/opt/scripts/dockyrm.sh thinlinc-client.desktop\n";
        }
        // BROWSER
        if (ui->browser_checkBox->isChecked() && browser_pkgs == "not_present") { qDebug() << "I have to install Iceweasel/Firefox!";
        bash_me = bash_me + "\n####### BROWSER Install cmds:\n"
                            "apt-get install -y iceweasel\n"
                            "# Add Iceweasel icon to docky menu:\n/opt/scripts/dockyadd.sh iceweasel.desktop\n";
        }
        if (!ui->browser_checkBox->isChecked() && browser_pkgs == "installed") { qDebug() << "I have to remove Iceweasel/Firefox!";
        bash_me = bash_me + "\n####### BROWSER Remove cmds:\n"
                            "apt-get remove --purge -y iceweasel\n"
                            "# Remove Iceweasel icon from docky menu:\n/opt/scripts/dockyrm.sh iceweasel.desktop\n";
        }
    }
    //######################START RDP CLIENTS INSTALLATION/REMOVE ROUTINES##################ßß
    if (true) {
        // RDESKTOP
        if (ui->rdesktop_checkBox->isChecked() && rdesktop_pkgs == "not_present") { qDebug() << "I have to install RDesktop!";
        bash_me = bash_me + "\n####### RDESKTOP Install cmds:\n"
                            "apt-get install -y rdesktop pcscd\n"
                            "ln -s /opt/config/RDesktop.desktop /usr/share/applications/RDesktop.desktop\n"
                            "# Add RDesktop icon to docky menu:\n/opt/scripts/dockyadd.sh RDesktop.desktop\n";
        }
        if (!ui->rdesktop_checkBox->isChecked() && rdesktop_pkgs == "installed") { qDebug() << "I have to remove RDesktop!";
        bash_me = bash_me + "\n####### RDESKTOP Remove cmds:\n"
                            "apt-get remove --purge -y rdesktop pcscd\n"
                            "rm -fr /usr/share/applications/RDesktop.desktop\n"
                            "# Remove RDesktop icon from docky menu:\n/opt/scripts/dockyrm.sh RDesktop.desktop\n";
        }
        // XFREERDP DEB
        if (ui->xfreerdp_checkBox->isChecked() && xfreerdp_pkgs == "not_present") { qDebug() << "I have to install xFreeRDP DEB!";
        bash_me = bash_me + "\n####### XFREERDP DEB Install cmds:\n"
                            "apt-get install -y freerdp-x11 libfreerdp-plugins-standard gstreamer0.10-plugins-base\n"
                            "ln -s /opt/config/xFreeRDP.desktop /usr/share/applications/xFreeRDP.desktop\n"
                            "# Add xFreeRDP_DEB icon to docky menu:\n/opt/scripts/dockyadd.sh xFreeRDP.desktop\n";
        }
        if (!ui->xfreerdp_checkBox->isChecked() && xfreerdp_pkgs == "installed") { qDebug() << "I have to remove xFreeRDP DEB!";
        bash_me = bash_me + "\n####### XFREERDP DEB Remove cmds:\n"
                            "apt-get remove --purge -y freerdp-x11 libfreerdp-plugins-standard\n"
                            "rm -fr /usr/share/applications/xFreeRDP.desktop\n"
                            "# Remove xFreeRDP_DEB icon from docky menu:\n/opt/scripts/dockyrm.sh xFreeRDP.desktop\n";
        }
        // XFREERDP GIT
        if (ui->xfreerdpgit_checkBox->isChecked() && xfreerdpgit_pkgs == "not_present") { qDebug() << "I have to install xFreeRDP GIT!";
        bash_me = bash_me + "\n####### XFREERDP GIT Install cmds:\n"
                            "apt-get install -y libssl1.0.0\n"
                            "wget http://dl.armtc.net/RPi-TC/packages/xfreerdp -O /usr/bin/xfreerdp_git\nchmod +x /usr/bin/xfreerdp_git\n"
                            "ln -s /opt/config/xFreeRDP_GIT.desktop /usr/share/applications/xFreeRDP_GIT.desktop\n"
                            "# Add xFreeRDP_GIT icon to docky menu:\n/opt/scripts/dockyadd.sh xFreeRDP_GIT.desktop\n";
        }
        if (!ui->xfreerdpgit_checkBox->isChecked() && xfreerdpgit_pkgs == "installed") { qDebug() << "I have to remove xFreeRDP GIT!";
        bash_me = bash_me + "\n####### XFREERDP GIT Remove cmds:\n"
                            "apt-get remove --purge -y libssl1.0.0\n"
                            "rm -fr /usr/share/applications/xFreeRDP_GIT.desktop /usr/bin/xfreerdp_git\n"
                            "# Remove xFreeRDP_GIT icon from docky menu:\n/opt/scripts/dockyrm.sh xFreeRDP_GIT.desktop\n";
        }
        // DFREERDP
        if (ui->dfreerdp_checkBox->isChecked() && dfreerdp_pkgs == "not_present") { qDebug() << "I have to install dFreeRDP!";
        bash_me = bash_me + "\n####### DFREERDP Install cmds:\n"
                            "apt-get install -y dfreerdp\n"
                            "ln -s /opt/config/dFreeRDP.desktop /usr/share/applications/dFreeRDP.desktop\n"
                            "# Add dFreeRDP icon to docky menu:\n/opt/scripts/dockyadd.sh dFreeRDP.desktop\n";
        }
        if (!ui->dfreerdp_checkBox->isChecked() && dfreerdp_pkgs == "installed") { qDebug() << "I have to remove dFreeRDP!";
        bash_me = bash_me + "\n####### DFREERDP Remove cmds:\n"
                            "apt-get remove --purge -y dfreerdp\n"
                            "rm -fr /usr/share/applications/dFreeRDP.desktop\n"
                            "# Remove dFreeRDP icon from docky menu:\n/opt/scripts/dockyrm.sh dFreeRDP.desktop\n";
        }
    }
    //######################START OTHER CLIENTS INSTALLATION/REMOVE ROUTINES################ßß
    if (true) {
        // X2GO CLIENT:
        if (ui->x2go_checkBox->isChecked() && x2go_pkgs == "not_present") { qDebug() << "I have to install x2go client!";
        bash_me = bash_me + "\n####### X2GO CLIENT Install cmds:\n"
                            "apt-get install -y x2goclient\n"
                            "# Add X2GO icon to docky menu:\n/opt/scripts/dockyadd.sh x2goclient.desktop\n";
        }
        if (!ui->x2go_checkBox->isChecked() && x2go_pkgs == "installed") { qDebug() << "I have to remove x2go client!";
        bash_me = bash_me + "\n####### X2GO CLIENT Remove cmds:\n"
                            "apt-get remove --purge -y x2goclient\n"
                            "# Remove X2GO icon from docky menu:\n/opt/scripts/dockyrm.sh x2goclient.desktop\n";
        }
        // SPICE
        if (ui->spice_checkBox->isChecked() && spice_pkgs == "not_present") { qDebug() << "I have to install spice client!";
        bash_me = bash_me + "\n####### SPICE CLIENT Install cmds:\n"
                            "apt-get install -y spice-client-gtk\n"
                            "ln -s /opt/config/spicy.desktop /usr/share/applications/spicy.desktop\n"
                            "# Add SPICE icon to docky menu:\n/opt/scripts/dockyadd.sh spicy.desktop\n";
        }
        if (!ui->spice_checkBox->isChecked() && spice_pkgs == "installed") { qDebug() << "I have to remove spice client!";
        bash_me = bash_me + "\n####### SPICE CLIENT Remove cmds:\n"
                            "apt-get remove --purge -y spice-client-gtk\n"
                            "rm -fr /usr/share/applications/spicy.desktop\n"
                            "# Remove SPICE icon from docky menu:\n/opt/scripts/dockyrm.sh spicy.desktop\n";
        }
        // TN5250
        if (ui->tn5250_checkBox->isChecked() && tn5250_pkgs == "not_present") { qDebug() << "I have to install TN5250!";
        bash_me = bash_me + "\n####### TN5250 Install cmds:\n"
                            "apt-get install -y tn5250\n"
                            "ln -s /opt/config/tn5250.desktop /usr/share/applications/tn5250.desktop\n"
                            "# Add TN5250 icon to docky menu:\n/opt/scripts/dockyadd.sh tn5250.desktop\n";
        }
        if (!ui->tn5250_checkBox->isChecked() && tn5250_pkgs == "installed") { qDebug() << "I have to remove TN5250!";
        bash_me = bash_me + "\n####### TN5250 Remove cmds:\n"
                            "apt-get remove --purge -y tn5250\n"
                            "rm -fr /usr/share/applications/tn5250.desktop\n"
                            "# Remove TN5250 icon from docky menu:\n/opt/scripts/dockyrm.sh tn5250.desktop\n";
        }
        // x3270
        if (ui->x3270_checkBox->isChecked() && x3270_pkgs == "not_present") { qDebug() << "I have to install x3270!";
        bash_me = bash_me + "\n####### x3270 Install cmds:\n"
                            "apt-get install -y suite3270\n"
                            "ln -s /opt/config/x3270.desktop /usr/share/applications/x3270.desktop\n"
                            "# Add x3270 icon to docky menu:\n/opt/scripts/dockyadd.sh x3270.desktop\n";
        }
        if (!ui->x3270_checkBox->isChecked() && x3270_pkgs == "installed") { qDebug() << "I have to remove x3270!";
        bash_me = bash_me + "\n####### x3270 Remove cmds:\n"
                            "apt-get remove --purge -y suite3270\n"
                            "rm -fr /usr/share/applications/x3270.desktop\n"
                            "# Remove x3270 icon from docky menu:\n/opt/scripts/dockyrm.sh x3270.desktop\n";
        }
        // XEPHYR
        if (ui->xephyr_checkBox->isChecked() && xephyr_pkgs == "not_present") { qDebug() << "I have to install Xephyr!";
        bash_me = bash_me + "\n####### XEPHYR Install cmds:\n"
                            "apt-get install -y xserver-xephyr\n"
                            "ln -s /opt/config/Xephyr.desktop /usr/share/applications/Xephyr.desktop\n"
                            "# Add Xephyr icon to docky menu:\n/opt/scripts/dockyadd.sh Xephyr.desktop\n";
        }
        if (!ui->xephyr_checkBox->isChecked() && xephyr_pkgs == "installed") { qDebug() << "I have to remove Xephyr!";
        bash_me = bash_me + "\n####### XEPHYR Remove cmds:\n"
                            "apt-get remove --purge -y xserver-xephyr\n"
                            "rm -fr /usr/share/applications/Xephyr.desktop\n"
                            "# Remove Xephyr icon from docky menu:\n/opt/scripts/dockyrm.sh Xephyr.desktop\n";
        }
    }
    //######################START OS SERVICES INSTALLATION/REMOVE ROUTINES##################ßß
    if (true) {
        // CUPS
        if (ui->cups_checkBox->isChecked() && cups_pkgs == "not_present") { qDebug() << "I have to install CUPS!";
        bash_me = bash_me + "\n####### CUPS Install cmds:\n"
                            "apt-get install -y cups cups-browsed printer-driver-gutenprint\n";
        }
        if (!ui->cups_checkBox->isChecked() && cups_pkgs == "installed") { qDebug() << "I have to remove CUPS!";
        bash_me = bash_me + "\n####### CUPS Remove cmds:\n"
                            "apt-get remove --purge -y cups cups-common cups-browsed printer-driver-gutenprint\n";
        }
        // X11VNC
        if (ui->vnc_checkBox->isChecked() && x11vnc_pkgs == "not_present") { qDebug() << "I have to install X11VNC Server!";
        bash_me = bash_me + "\n####### X11VNC Install cmds:\n"
                            "apt-get install -y x11vnc\n"
                            "\n# set vnc server default password to rpitc:\n"
                            "x11vnc -storepasswd rpitc /home/rpitc/.x11vnc/passwd";
        }
        if (!ui->vnc_checkBox->isChecked() && x11vnc_pkgs == "installed") { qDebug() << "I have to remove X11VNC Server!";
        bash_me = bash_me + "\n####### X11VNC Remove cmds:\n"
                            "apt-get remove --purge -y x11vnc\n";
        }
        // SSH
        if (ui->ssh_checkBox->isChecked() && ssh_pkgs == "not_present") { qDebug() << "I have to install SSH Server!";
        bash_me = bash_me + "\n####### SSH Install cmds:\n"
                            "apt-get install -y openssh-server\n";
        }
        if (!ui->ssh_checkBox->isChecked() && ssh_pkgs == "installed") { qDebug() << "I have to remove SSH Server!";
        bash_me = bash_me + "\n####### SSH Remove cmds:\n"
                            "apt-get remove --purge -y openssh-server\n";
        }
        // DOCKY
        if (ui->docky_checkBox->isChecked() && docky_pkgs == "not_present") { qDebug() << "I have to install Docky!";
        bash_me = bash_me + "\n####### DOCKY Install cmds:\n"
                            "apt-get install -y docky\n";
        }
        if (!ui->docky_checkBox->isChecked() && docky_pkgs == "installed") { qDebug() << "I have to remove Docky!";
        bash_me = bash_me + "\n####### DOCKY Remove cmds:\n"
                            "apt-get remove --purge -y docky\n";
        }
        // CONKY
        if (ui->conky_checkBox->isChecked() && conky_pkgs == "not_present") { qDebug() << "I have to install Conky!";
        bash_me = bash_me + "\n####### CONKY Install cmds:\n"
                            "apt-get install -y conky\n"
                            "cp /opt/config/Conky.autostart /home/rpitc/.config/autostart/\n";
        }
        if (!ui->conky_checkBox->isChecked() && conky_pkgs == "installed") { qDebug() << "I have to remove Conky!";
        bash_me = bash_me + "\n####### CONKY Remove cmds:\n"
                            "apt-get remove --purge -y conky\n";
        }
        // VIRTUALHERE
        if (ui->virtualhere_checkBox->isChecked() && virtualhere_pkgs == "not_present") { qDebug() << "I have to install VirtualHere USB Server!";
        bash_me = bash_me + "\n####### VIRTUALHERE Install cmds:\n"
                            "wget https://www.virtualhere.com/sites/default/files/usbserver/vhusbdarmpi2 -O /usr/bin/vhusbdarmpi2\nchmod +x /usr/bin/vhusbdarmpi2\n"
                            "cp /opt/scripts/vhusbdarmpi2 /etc/init.d/\nsystemctl enable vhusbdarmpi2;systemctl start vhusbdarmpi2\n";
        }
        if (!ui->virtualhere_checkBox->isChecked() && virtualhere_pkgs == "installed") { qDebug() << "I have to remove VirtualHere USB Server!";
        bash_me = bash_me + "\n####### VIRTUALHERE Remove cmds:\n"
                            "systemctl stop vhusbdarmpi2;systemctl disable vhusbdarmpi2;rm -fr /usr/bin/vhusbdarmpi2 /etc/init.d/vhusbdarmpi2\n";
        }
        // OPENCONNECT
        if (ui->openconnect_checkBox->isChecked() && openconnect_pkgs == "not_present") { qDebug() << "I have to install Openconnect VPN!";
        bash_me = bash_me + "\n####### OPENCONNECT Install cmds:\n"
                            "apt-get install -y openconnect network-manager-openconnect network-manager-openconnect-gnome\n";
        }
        if (!ui->openconnect_checkBox->isChecked() && openconnect_pkgs == "installed") { qDebug() << "I have to remove Openconnect VPN!";
        bash_me = bash_me + "\n####### OPENCONNECT Remove cmds:\n"
                            "apt-get remove --purge -y openconnect network-manager-openconnect network-manager-openconnect-gnome\n";
        }
        // OPENVPN
        if (ui->openvpn_checkBox->isChecked() && openvpn_pkgs == "not_present") { qDebug() << "I have to install OpenVPN!";
        bash_me = bash_me + "\n####### OPENVPN Install cmds:\n"
                            "apt-get install -y openvpn network-manager-openvpn network-manager-openvpn-gnome\n";
        }
        if (!ui->openvpn_checkBox->isChecked() && openvpn_pkgs == "installed") { qDebug() << "I have to remove OpenVPN!";
        bash_me = bash_me + "\n####### OPENVPN Remove cmds:\n"
                            "apt-get remove --purge -y openvpn network-manager-openvpn network-manager-openvpn-gnome\n";
        }
        // VPNC
        if (ui->vpnc_checkBox->isChecked() && vpnc_pkgs == "not_present") { qDebug() << "I have to install VPNC!";
        bash_me = bash_me + "\n####### VPNC Install cmds:\n"
                            "apt-get install -y vpnc network-manager-vpnc network-manager-vpnc-gnome\n";
        }
        if (!ui->vpnc_checkBox->isChecked() && vpnc_pkgs == "installed") { qDebug() << "I have to remove VPNC!";
        bash_me = bash_me + "\n####### VPNC Remove cmds:\n"
                            "apt-get remove --purge -y network-manager-vpnc network-manager-vpnc-gnome\n";
        }
    }
    //######################START CUSTOM/OTHER SERVICES INSTALLATION/REMOVE ROUTINES##################ßß
    if (true) {
        // OVERCLOCK
        if (ui->overclock_checkBox->isChecked() && overclock_pkgs == "not_present") { qDebug() << "I have to enable the overclock!";
        bash_me = bash_me + "\n####### Enabling OVERCLOCK: \n"
                            "sed -i '/^#arm_freq/{s/^#//}' /boot/config.txt\n"
                            "sed -i '/^#sdram_freq/{s/^#//}' /boot/config.txt\n"
                            "sed -i '/^#core_freq/{s/^#//}' /boot/config.txt\n"
                            "sed -i '/^#over_voltage/{s/^#//}' /boot/config.txt\n"
                            "sed -i '/^#initial_turbo/{s/^#//}' /boot/config.txt\n";
        }
        if (!ui->overclock_checkBox->isChecked() && overclock_pkgs == "installed") { qDebug() << "I have to remove the overclock!";
        bash_me = bash_me + "\n####### Disabling OVERCLOCK: \n"
                            "sed -i '/^arm_freq/{s/^/#/}' /boot/config.txt\n"
                            "sed -i '/^sdram_freq/{s/^/#/}' /boot/config.txt\n"
                            "sed -i '/^core_freq/{s/^/#/}' /boot/config.txt\n"
                            "sed -i '/^over_voltage/{s/^/#/}' /boot/config.txt\n"
                            "sed -i '/^initial_turbo/{s/^/#/}' /boot/config.txt\n";
        }
        // CUSTOM
        if (ui->custom_checkBox->isChecked() && custom1_pkgs == "not_present") { qDebug() << "I have to install CUSTOM1!";
        bash_me = bash_me + "\n\n####### Customscript: \n" + ui->custom_textEdit->toPlainText();
        }
        if (!ui->custom_checkBox->isChecked() && custom1_pkgs == "installed") { qDebug() << "I have to remove CUSTOM1!";
        bash_me = bash_me + "\n\n####### Customscript: \n" + ui->custom_textEdit->toPlainText();
        }
    }

    //#### default commands to execute at the end:
    if (ui->aptcache_checkBox->isChecked()) {
        bash_me = bash_me + "\n\n####### clean up all the unecessary package and the apt-get cache:\n"
                            "apt-get autoremove --purge -y\napt-get clean\n";
    }
    bash_me = bash_me + "\n\n####### Send sync to flush the file system buffers\n"
                        "sync";

    //finalizing bash me and putting it to file:
    QFile file(bash_me_filename);
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream WriteOut(&file);
    WriteOut << bash_me+"\n";
    file.close();
    system(qPrintable("chmod +x "+bash_me_filename));
    bash_me = "";
    HelperWindow bashmenow;
    bashmenow.exec();
}

void RPiTC::on_rescan_pushButton_clicked()
{
    //######################START MAIN CLIENTS CHECK#####################ßß
    if (true) {
        // CITRIX RECEIVER:
        if (QFile("/opt/Citrix/ICAClient/wfica").exists()) {
            qDebug() << "Citrix Receiver is installed"; ui->ica_checkBox->setChecked(true); ica_pkgs = "installed";
        } else {
            qDebug() << "Citrix Receiver missing"; ui->ica_checkBox->setChecked(false); ica_pkgs = "not_present";
        }
        // VMWARE HORIZON:
        if (QFile("/usr/bin/vmware-view").exists()) {
            qDebug() << "VMWare Horizon is installed"; ui->vmware_checkBox->setChecked(true); vmware_pkgs = "installed";
        } else {
            qDebug() << "VMWare Horizon missing"; ui->vmware_checkBox->setChecked(false); vmware_pkgs = "not_present";
        }
        // NOMACHINENX:
        if (QFile("/usr/NX/bin/nxplayer.bin").exists()) {
            qDebug() << "NoMachine NX is installed"; ui->nomachine_checkBox->setChecked(true); nxc_pkgs = "installed";
        } else {
            qDebug() << "NoMachine NX missing"; ui->nomachine_checkBox->setChecked(false); nxc_pkgs = "not_present";
        }
        // THINLINC:
        if (QFile("/opt/thinlinc/bin/tlclient").exists()) {
            qDebug() << "Thinlinc is installed"; ui->thinlinc_checkBox->setChecked(true); thinlinc_pkgs = "installed";
        } else {
            qDebug() << "Thinlinc missing"; ui->thinlinc_checkBox->setChecked(false); thinlinc_pkgs = "not_present";
        }
        // PARALLELS 2X:
        if (QFile("/opt/2X/Client/bin/appserverclient").exists()) {
            qDebug() << "Parallels 2X is installed"; ui->twox_checkBox->setChecked(true); twox_pkgs = "installed";
        } else {
            qDebug() << "Parallels 2X missing"; ui->twox_checkBox->setChecked(false); twox_pkgs = "not_present";
        }
        // ICEWEASEL:
        if (QFile("/usr/bin/firefox").exists()) {
            qDebug() << "Iceweasel is installed"; ui->browser_checkBox->setChecked(true); browser_pkgs = "installed";
        } else {
            qDebug() << "Iceweasel missing"; ui->browser_checkBox->setChecked(false); browser_pkgs = "not_present";
        }
    }
    //######################START OTHER CLIENTS CHECK####################ßß
    if (true) {
        // X2GO CLIENT:
        if (QFile("/usr/bin/x2goclient").exists()) {
            qDebug() << "X2GO Client is installed"; ui->x2go_checkBox->setChecked(true); x2go_pkgs = "installed";
        } else {
            qDebug() << "X2GO Client Receiver missing"; ui->x2go_checkBox->setChecked(false); x2go_pkgs = "not_present";
        }
        // SPICE
        if (QFile("/usr/bin/spicy").exists()) {
            qDebug() << "SPICE is installed"; ui->spice_checkBox->setChecked(true); spice_pkgs = "installed";
        } else {
            qDebug() << "SPICE missing"; ui->spice_checkBox->setChecked(false); spice_pkgs = "not_present";
        }
        // TN5250
        if (QFile("/usr/bin/tn5250").exists()) {
            qDebug() << "TN5250 is installed"; ui->tn5250_checkBox->setChecked(true); tn5250_pkgs = "installed";
        } else {
            qDebug() << "TN5250 missing"; ui->tn5250_checkBox->setChecked(false); tn5250_pkgs = "not_present";
        }
        // x3270
        if (QFile("/usr/bin/x3270").exists()) {
            qDebug() << "x3270 is installed"; ui->x3270_checkBox->setChecked(true); x3270_pkgs = "installed";
        } else {
            qDebug() << "x3270 missing"; ui->x3270_checkBox->setChecked(false); x3270_pkgs = "not_present";
        }
        // XEPHYR
        if (QFile("/usr/bin/Xephyr").exists()) {
            qDebug() << "Xephyr is installed"; ui->xephyr_checkBox->setChecked(true); xephyr_pkgs = "installed";
        } else {
            qDebug() << "Xephyr missing"; ui->xephyr_checkBox->setChecked(false); xephyr_pkgs = "not_present";
        }
    }
    //######################START RDP CLIENTS CHECK######################ßß
    if (true) {
        // RDESKTOP
        if (QFile("/usr/bin/rdesktop").exists()) {
            qDebug() << "RDesktop is installed"; ui->rdesktop_checkBox->setChecked(true); rdesktop_pkgs = "installed";
        } else {
            qDebug() << "RDesktop missing"; ui->rdesktop_checkBox->setChecked(false); rdesktop_pkgs = "not_present";
        }
        // XFREERDP DEB
        if (QFile("/usr/bin/xfreerdp").exists()) {
            qDebug() << "xFreeRDP is installed"; ui->xfreerdp_checkBox->setChecked(true); xfreerdp_pkgs = "installed";
        } else {
            qDebug() << "xFreeRDP missing"; ui->xfreerdp_checkBox->setChecked(false); xfreerdp_pkgs = "not_present";
        }
        // XFREERDP GIT
        if (QFile("/usr/bin/xfreerdp_git").exists()) {
            qDebug() << "xFreeRDP GIT is installed"; ui->xfreerdpgit_checkBox->setChecked(true); xfreerdpgit_pkgs = "installed";
        } else {
            qDebug() << "xFreeRDP GIT missing"; ui->xfreerdpgit_checkBox->setChecked(false); xfreerdpgit_pkgs = "not_present";
        }
        // DFREERDP
        if (QFile("/opt/dfreerdp/bin/dfreerdp").exists()) {
            qDebug() << "dFreeRDP is installed"; ui->dfreerdp_checkBox->setChecked(true); dfreerdp_pkgs = "installed";
        } else {
            qDebug() << "dFreeRDP missing"; ui->dfreerdp_checkBox->setChecked(false); dfreerdp_pkgs = "not_present";
        }
    }
    //######################START OS SERVICES CHECK######################ßß
    if (true) {
        // CUPS
        if (QFile("/usr/sbin/cupsd").exists()) {
            qDebug() << "CUPS is installed"; ui->cups_checkBox->setChecked(true); cups_pkgs = "installed";
        } else {
            qDebug() << "CUPS missing"; ui->cups_checkBox->setChecked(false); cups_pkgs = "not_present";
        }
        // X11VNC
        if (QFile("/usr/bin/x11vnc").exists()) {
            qDebug() << "X11VNC Server is installed"; ui->vnc_checkBox->setChecked(true); x11vnc_pkgs = "installed";
        } else {
            qDebug() << "X11VNC Server missing"; ui->vnc_checkBox->setChecked(false); x11vnc_pkgs = "not_present";
        }
        // SSH
        if (QFile("/usr/sbin/sshd").exists()) {
            qDebug() << "SSH Server is installed"; ui->ssh_checkBox->setChecked(true); ssh_pkgs = "installed";
        } else {
            qDebug() << "SSH Server missing"; ui->ssh_checkBox->setChecked(false); ssh_pkgs = "not_present";
        }
        // DOCKY
        if (QFile("/usr/lib/docky/Docky.exe").exists()) {
            qDebug() << "Docky is installed"; ui->docky_checkBox->setChecked(true); docky_pkgs = "installed";
        } else {
            qDebug() << "Docky missing"; ui->docky_checkBox->setChecked(false); docky_pkgs = "not_present";
        }
        // CONKY
        if (QFile("/usr/bin/conky").exists()) {
            qDebug() << "Conky is installed"; ui->conky_checkBox->setChecked(true); conky_pkgs = "installed";
        } else {
            qDebug() << "Conky missing"; ui->conky_checkBox->setChecked(false); conky_pkgs = "not_present";
        }
        // VIRTUALHERE
        if (QFile("/usr/bin/vhusbdarmpi2").exists()) {
            qDebug() << "VirtualHere USB Server is installed"; ui->virtualhere_checkBox->setChecked(true); virtualhere_pkgs = "installed";
        } else {
            qDebug() << "VirtualHere USB Server missing"; ui->virtualhere_checkBox->setChecked(false); virtualhere_pkgs = "not_present";
        }
        // OPENCONNECT
        if (QFile("/usr/lib/NetworkManager/nm-openconnect-service").exists()) {
            qDebug() << "Openconnect VPN is installed"; ui->openconnect_checkBox->setChecked(true); openconnect_pkgs = "installed";
        } else {
            qDebug() << "Openconnect VPN missing"; ui->openconnect_checkBox->setChecked(false); openconnect_pkgs = "not_present";
        }
        // OPENVPN
        if (QFile("/usr/lib/NetworkManager/nm-openvpn-service").exists()) {
            qDebug() << "OpenVPN is installed"; ui->openvpn_checkBox->setChecked(true); openvpn_pkgs = "installed";
        } else {
            qDebug() << "OpenVPN missing"; ui->openvpn_checkBox->setChecked(false); openvpn_pkgs = "not_present";
        }
        // VPNC
        if (QFile("/usr/lib/NetworkManager/nm-vpnc-service").exists()) {
            qDebug() << "VPNc is installed"; ui->vpnc_checkBox->setChecked(true); vpnc_pkgs = "installed";
        } else {
            qDebug() << "VPNc missing"; ui->vpnc_checkBox->setChecked(false); vpnc_pkgs = "not_present";
        }
    }
    //######################START CUSTOM/OTHER SERVICES CHECK######################ßß
    if (true) {
        // OVERCLOCK
        QProcess overclock_check;
        overclock_check.start("cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq");
        overclock_check.waitForFinished(-1);
        QString overclock_stdout = overclock_check.readAllStandardOutput();
        //just check if cpu max frequency is
        if (overclock_stdout.toInt() > 900000) {
            qDebug() << "OVERCLOCK enable"; ui->overclock_checkBox->setChecked(true); overclock_pkgs = "installed";
        } else {
            qDebug() << "OVERCLOCK disable"; ui->overclock_checkBox->setChecked(false); overclock_pkgs = "not_present";
        }
        // CUSTOM1
        if (QFile(ui->customfile_lineEdit->text()).exists()) {
            qDebug() << "CUSTOM is installed"; ui->custom_checkBox->setChecked(true); custom1_pkgs = "installed";
        } else {
            qDebug() << "CUSTOM missing"; ui->custom_checkBox->setChecked(false); custom1_pkgs = "not_present";
        }
    }
}

void RPiTC::on_searchfile_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
    "",
    tr("File to check (*.*)"));
    ui->customfile_lineEdit->setText(fileName);
}
